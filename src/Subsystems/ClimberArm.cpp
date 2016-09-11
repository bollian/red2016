#include <Ports/Motor.hpp>
#include <Subsystems/ClimberArm.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace ClimberArm
{
	const float UPWARD_SPEED = 0.4;
	const float DOWNWARD_SPEED = 0.6;

	SpeedController* arm_motor = Utils::constructMotor(MotorPorts::CLIMBER_ARM_MOTOR);

	void initialize()
	{

	}

	void process()
	{

	}

	void setSpeed(float speed)
	{
		arm_motor->Set(speed);
	}

	void setDirection(Utils::VerticalDirection dir)
	{
		switch (dir) {
		case Utils::VerticalDirection::UP:
			setSpeed(UPWARD_SPEED);
			break;
		case Utils::VerticalDirection::V_STILL:
			setSpeed(0.0);
			break;
		case Utils::VerticalDirection::DOWN:
			setSpeed(DOWNWARD_SPEED);
			break;
		}
	}

	float getSpeed()
	{
		return arm_motor->Get();
	}

	Utils::VerticalDirection getDirection()
	{
		float speed = getSpeed();
		if (speed < 0.0) {
			return Utils::VerticalDirection::DOWN;
		}
		else if (speed > 0.0) {
			return Utils::VerticalDirection::UP;
		}
		return Utils::VerticalDirection::V_STILL;
	}
}
