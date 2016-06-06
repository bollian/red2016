#include <Coordination.hpp>
#include <Robot.hpp>
#include <Subsystems/HolderWheels.hpp>
#include <Subsystems/Mobility.hpp>
#include <Subsystems/ShooterPitch.hpp>
#include <Subsystems/ShooterWheels.hpp>

namespace Coordination
{
	const float AUTONOMOUS_SHOOTER_WHEELS_RATE = ShooterWheels::getRPMPreset(ShooterWheels::getPresetCount() - 1);
	const float SHOOT_SPEED_UP_TIME = 5.0;
	const float PUSH_BOULDER_TIMER = 2.0;
	
	State state = State::WAITING;
	
	Timer* shoot_timer;
	float shooter_rate = 0.0;
	bool shot_ball = false;
	
	void setState(State new_state);
	
	void initialize()
	{
		shoot_timer = new Timer();
	}
	
	void process()
	{
		switch (state) {
		case State::DISABLED:
		case State::WAITING:
			break;
		
		case State::SHOOTING_BALL:
			if (ShooterWheels::atRate() || shoot_timer->Get() > SHOOT_SPEED_UP_TIME) {
				if (shot_ball && HolderWheels::getState() == HolderWheels::WAITING) {
					setState(WAITING);
				}
				else {
					HolderWheels::shootBall();
					shot_ball = true;
				}
			}
			break;
		
		case State::AUTO_AIM:
			break;
		
		case State::AUTO_SHOOT:
			break;
		}
	}
	
	void shootBall(float rate)
	{
		shooter_rate = rate;
		setState(State::SHOOTING_BALL);
	}
	
	void autoAim()
	{
		setState(State::AUTO_AIM);
	}
	
	void autoShoot()
	{
		setState(State::AUTO_SHOOT);
	}
	
	void interrupt()
	{
		setState(State::WAITING);
	}
	
	State getState()
	{
		return state;
	}
	
	void setState(State new_state)
	{
		if (state != new_state) {
			switch (state) {
			case State::DISABLED:
				return;
			
			case State::WAITING:
				break;
			
			case State::SHOOTING_BALL:
				HolderWheels::interrupt();
				ShooterWheels::interrupt();
				break;
			
			case State::AUTO_AIM:
				Mobility::interrupt();
				ShooterPitch::interrupt();
				break;
			
			case State::AUTO_SHOOT:
				HolderWheels::interrupt();
				Mobility::interrupt();
				ShooterPitch::interrupt();
				ShooterWheels::interrupt();
				break;
			}
			
			switch (new_state) {
			case State::DISABLED:
				break;
			
			case State::WAITING:
				break;
			
			case State::SHOOTING_BALL:
				shot_ball = false;
				shoot_timer->Start();
				shoot_timer->Reset();
				
				if (ShooterWheels::getState() != ShooterWheels::State::MAINTAINING_RATE) {
					// don't set the rate if already maintaining a rate because then
					// the shooter wheels won't consider themselves as up-to-speed
					// and the drivers will have to wait another second
					ShooterWheels::setRate(shooter_rate);
				}
				break;
			
			case State::AUTO_AIM:
				break;
			
			case State::AUTO_SHOOT:
				break;
			}
			
			state = new_state;
		}
	}
}
