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
		Utils::setDirection(&setSpeed, UPWARD_SPEED, DOWNWARD_SPEED, (int)dir);
	}

	float getSpeed()
	{
		return arm_motor->Get();
	}

	Utils::VerticalDirection getDirection()
	{
		return (Utils::VerticalDirection)Utils::getDirection(&getSpeed);
	}
}
