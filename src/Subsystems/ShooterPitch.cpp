#include <PID/ShooterPitch.hpp>
#include <Ports/Motor.hpp>
#include <Subsystems/OI.hpp>
#include <Subsystems/Sensors.hpp>
#include <Subsystems/ShooterPitch.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace ShooterPitch
{
	const float SHOOTER_TO_TARGET_HEIGHT = 45.72; // cm
	const float MOTOR_SPEED = 1.0;
	const float ACCEPTABLE_ERROR = 0.5;
	
	const float ANGLE_PRESETS[] = {
		0.0,
		15.0,
		30.0,
		45.0,
		60.0,
		75.0
	};
	
	State state = State::WAITING;
	float target_angle = 0.0;
	
	ShooterPitchPID* pid_manager = ShooterPitchPID::getInstance();
	SpeedController* pitch_motor;
	
	void setState(State new_state);
	
	void initialize()
	{
		pitch_motor = Utils::constructMotor(MotorPorts::SHOOTER_PITCH_MOTOR);
	}

	void process()
	{
		if (getDirection() == Utils::VerticalDirection::DOWN && Sensors::isShooterLimitPressed()) {
			setSpeed(0.0);
		}
		
		switch (state) {
		case State::DISABLED:
			setSpeed(0.0);
			break;
		case State::WAITING:
			break;
		case State::MANUAL_CONTROL:
			pid_manager->enable(false);
			break;
		
		case State::REACHING_ANGLE:
			if (pid_manager->isEnabled()) {
				pid_manager->setTarget(target_angle); // in case pid is enabled while going to an angle
			}
			else {
				float error = target_angle - Sensors::getShooterAngle();
				if (fabs(error) < ACCEPTABLE_ERROR) {
					if (error > 0) {
						setDirection(Utils::VerticalDirection::UP);
					}
					else { // error < 0
						setDirection(Utils::VerticalDirection::DOWN);
					}
				}
				else {
					setDirection(Utils::VerticalDirection::V_STILL);
				}
			}
		}
	}

	void setSpeed(float speed)
	{
		if (speed < 0.0 && Sensors::isShooterLimitPressed()) {
			speed = 0.0;
		}
		if (state != State::DISABLED) {
			pitch_motor->Set(speed);
		}
	}

	void setDirection(Utils::VerticalDirection dir)
	{
		Utils::setDirection(&setSpeed, MOTOR_SPEED, MOTOR_SPEED, (int)dir);
	}

	float getSpeed()
	{
		return pitch_motor->Get();
	}

	Utils::VerticalDirection getDirection()
	{
		return (Utils::VerticalDirection)Utils::getDirection(&getSpeed);
	}
	
	void engageManualControl()
	{
		setState(State::MANUAL_CONTROL);
	}
	
	void goToAngle(float degrees)
	{
		setState(State::REACHING_ANGLE);
	}
	
	void interrupt()
	{
		setState(State::WAITING);
	}
	
	State getState()
	{
		return state;
	}
	
	int getPresetCount()
	{
		return sizeof(ANGLE_PRESETS) / sizeof(*ANGLE_PRESETS);
	}
	
	float getAnglePreset(int index)
	{
		int count = getPresetCount();
		if (index > count) {
			return ANGLE_PRESETS[count - 1];
		}
		if (index < 0) {
			return ANGLE_PRESETS[0];
		}
		
		return ANGLE_PRESETS[index];
	}
	
	void setState(State new_state)
	{
		if (new_state != state) {
			switch (state) {
			case State::DISABLED:
				return; // if the subsystem is disabled, do not allow a reenable
			case State::WAITING:
				break;
			
			case State::MANUAL_CONTROL:
			case State::REACHING_ANGLE:
				setDirection(Utils::VerticalDirection::V_STILL);
				break;
			}
			
			switch (new_state) {
			case State::DISABLED:
			case State::WAITING:
			case State::MANUAL_CONTROL:
				pid_manager->enable(false);
				break;
				
			case State::REACHING_ANGLE:
				pid_manager->enable(OI::isPIDEnabled());
				break;
			}
		}
	}
}
