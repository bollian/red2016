#include <Coordination.hpp>
#include <Robot.hpp>
#include <Subsystems/HolderWheels.hpp>
#include <Subsystems/Mobility.hpp>
#include <Subsystems/ShooterPitch.hpp>
#include <Subsystems/ShooterWheels.hpp>

namespace Coordination
{
	const float AUTONOMOUS_SHOOTER_WHEELS_RATE = ShooterWheels::getRPMPreset(ShooterWheels::getPresetCount() - 1);
	
	State state = State::WAITING;
	float shooter_rate = 0.0;
	
	void setState(State new_state);
	
	void initialize()
	{
		
	}
	
	void process()
	{
		switch (state) {
		case State::DISABLED:
		case State::WAITING:
			break;
		
		case State::SHOOTING_BALL:
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
				ShooterWheels::setRate(shooter_rate);
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
