#include <Ports/Motor.hpp>
#include <Subsystems/IntakeAngle.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace IntakeAngle
{
	const float MOTOR_SPEED = 0.5;
	
	const float ANGLE_PRESETS[] = {
		-30.0,
		-15.0,
		3.0,
		30.0,
		60.0,
		90.0
	};

	SpeedController* angle_motor;

	void initialize()
	{
		angle_motor = Utils::constructMotor(MotorPorts::INTAKE_ANGLE_MOTOR);
	}

	void process()
	{

	}

	void setSpeed(float speed)
	{
		angle_motor->Set(speed);
	}

	void setDirection(Utils::VerticalDirection dir)
	{
		Utils::setDirection(&setSpeed, MOTOR_SPEED, MOTOR_SPEED, (int)dir);
	}

	float getSpeed()
	{
		return angle_motor->Get();
	}

	Utils::VerticalDirection getDirection()
	{
		return (Utils::VerticalDirection)Utils::getDirection(&getSpeed);
	}
	
	int getPresetCount()
	{
		return sizeof(ANGLE_PRESETS) / sizeof(*ANGLE_PRESETS);
	}
	
	float getAnglePreset(int index)
	{
		int count = getPresetCount();
		if (index >= count) {
			return ANGLE_PRESETS[count - 1];
		}
		if (index < 0) {
			return ANGLE_PRESETS[0];
		}
		return ANGLE_PRESETS[index];
	}
}
