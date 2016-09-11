#include <ED/PIDManager.hpp>
#include <Ports/Motor.hpp>
#include <Subsystems/OI.hpp>
#include <Subsystems/Sensors.hpp>
#include <Subsystems/ShooterPitch.hpp>
#include <Utils.hpp>
#include <WPILib.h>

class ShooterPitchPID : public ED::PIDManager
{
public:
	ShooterPitchPID() : PIDManager(0.1, 0.0001, 0.0)
	{
		autoClearAccumulatedError(true);
	}

protected:
	float returnPIDInput()
	{
		return Sensors::getShooterAngle();
	}

	void usePIDOutput(float output, float feed_forward)
	{
		ShooterPitch::setSpeed(output);
	}
};

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
	
	ShooterPitchPID* pid_manager = nullptr;
	SpeedController* pitch_motor = nullptr;
	
	void setState(State new_state);
	
	void initialize()
	{
		pid_manager = new ShooterPitchPID();
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
			enablePID(false);
			break;
		
		case State::WAITING:
		case State::MANUAL_CONTROL:
			break;
		
		case State::REACHING_ANGLE:
			if (!pid_manager->isEnabled()) {
				float error = pid_manager->getTarget() - Sensors::getShooterAngle();
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

	void processPID()
	{
		pid_manager->process();
	}

	void enablePID(bool enable)
	{
		pid_manager->enable(enable);
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
		switch (dir) {
		case Utils::VerticalDirection::UP:
			setSpeed(MOTOR_SPEED);
			break;
		case Utils::VerticalDirection::V_STILL:
			setSpeed(0.0);
			break;
		case Utils::VerticalDirection::DOWN:
			setSpeed(-MOTOR_SPEED);
			break;
		}
	}

	float getSpeed()
	{
		return pitch_motor->Get();
	}

	Utils::VerticalDirection getDirection()
	{
		float speed = getSpeed();
		if (speed > 0.0) {
			return Utils::VerticalDirection::UP;
		}
		else if (speed < 0.0) {
			return Utils::VerticalDirection::DOWN;
		}
		return Utils::VerticalDirection::V_STILL;
	}
	
	void engageManualControl()
	{
		enablePID(false);
		setState(State::MANUAL_CONTROL);
	}
	
	void goToAngle(float degrees)
	{
		pid_manager->setTarget(degrees);
		enablePID(OI::isPIDEnabled());
		setState(State::REACHING_ANGLE);
	}
	
	void interrupt()
	{
		enablePID(false);
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
			
			state = new_state;
		}
	}
}
