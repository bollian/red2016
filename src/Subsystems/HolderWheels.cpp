#include <Ports/Motor.hpp>
#include <Subsystems/HolderWheels.hpp>
#include <Subsystems/Sensors.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace HolderWheels
{
	const float SHOOT_TIME = 2.0;
	const float MOTOR_SPEED = 1.0;
	
	State state = State::WAITING;
	
	SpeedController* wheels_motor = nullptr;
	Timer* shoot_timer = nullptr;

	void setState(State new_state);

	void initialize()
	{
		wheels_motor = Utils::constructMotor(MotorPorts::HOLDER_WHEELS_MOTOR);
		
		shoot_timer = new Timer();
		shoot_timer->Reset();
	}

	void process()
	{
		switch (state) {
		case State::DISABLED:
			wheels_motor->Set(0.0);
			break;
		
		case State::WAITING:
			break;
		
		case State::MANUAL_CONTROL:
			if (getDirection() == Utils::HorizontalDirection::IN && Sensors::isBallLimitPressed()) {
				setDirection(Utils::HorizontalDirection::H_STILL);
			}
			break;
		
		case State::SHOOTING_BALL:
			if (shoot_timer->Get() > SHOOT_TIME) {
				setState(State::WAITING);
			}
			break;
		}
	}

	void setSpeed(float speed)
	{
		if (state != State::DISABLED) {
			if (state == State::MANUAL_CONTROL && speed > 0.0 && Sensors::isBallLimitPressed()) {
				wheels_motor->Set(0.0);
			}
			else {
				wheels_motor->Set(speed);
			}
		}
	}

	void setDirection(Utils::HorizontalDirection dir)
	{
		Utils::setDirection(&setSpeed, MOTOR_SPEED, MOTOR_SPEED, (int)dir);
	}

	float getSpeed()
	{
		return wheels_motor->Get();
	}

	Utils::HorizontalDirection getDirection()
	{
		return (Utils::HorizontalDirection)Utils::getDirection(&getSpeed);
	}
	
	void engageManualControl()
	{
		setState(State::MANUAL_CONTROL);
	}
	
	void shootBall()
	{
		shoot_timer->Start();
		shoot_timer->Reset();
		setState(State::SHOOTING_BALL);
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
			case State::MANUAL_CONTROL:
				setSpeed(0.0);
				break;
			
			case State::SHOOTING_BALL:
				setSpeed(0.0);
				shoot_timer->Stop();
				break;
			}
			
			state = new_state;
		}
	}
}
