#include <Ports/Motor.hpp>
#include <PID/ShooterWheels.hpp>
#include <Subsystems/ShooterWheels.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace ShooterWheels
{
	const float RPM_PRESETS[] = {
		2000.0,
		2600.0,
		3200.0,
		3800.0,
		4400.0,
		5000.0
	};
	
	const float SPEED_PRESETS[] = {
		0.5,
		0.6,
		0.7,
		0.8,
		0.9,
		1.0
	};
	
	State state = State::WAITING;
	
	ShooterWheelsPID* pid_manager = ShooterWheelsPID::getInstance();
	SpeedController* wheels_motor;
	
	void setState(State new_state);
	
	void initialize()
	{
		wheels_motor = Utils::constructMotor(MotorPorts::SHOOTER_WHEELS_MOTOR);
	}

	void process()
	{

	}

	void setSpeed(float speed)
	{
		wheels_motor->Set(speed);
	}
	
	void setRate(float rate)
	{
		pid_manager->enable(true);
		pid_manager->setTarget(rate);
		setState(State::MAINTAINING_RATE);
	}
	
	float getSpeed()
	{
		return wheels_motor->Get();
	}
	
	int getPresetCount()
	{
		return sizeof(SPEED_PRESETS) / sizeof(*SPEED_PRESETS);
	}
	
	float getSpeedPreset(int index)
	{
		int preset_count = getPresetCount();
		if (index >= preset_count) {
			return SPEED_PRESETS[preset_count - 1];
		}
		if (index < 0) {
			return SPEED_PRESETS[0];
		}
		return SPEED_PRESETS[index];
	}
	
	float getRPMPreset(int index)
	{
		int preset_count = getPresetCount();
		if (index >= preset_count) {
			return RPM_PRESETS[preset_count - 1];
		}
		if (index < 0) {
			return RPM_PRESETS[0];
		}
		return RPM_PRESETS[index];
	}
	
	void interrupt()
	{
		setState(State::WAITING);
	}
	
	void setState(State new_state)
	{
		if (state != new_state) {
			switch (state) {
			case State::DISABLED:
				return;
			
			case State::WAITING:
				break;
			
			case State::MAINTAINING_RATE:
				break;
			}
			
			switch (new_state) {
			case State::DISABLED:
				wheels_motor->Set(0.0);
				break;
			
			case State::WAITING:
				setSpeed(0.0);
				break;
			
			case State::MAINTAINING_RATE:
				break;
			}
			
			state = new_state;
		}
	}
}
