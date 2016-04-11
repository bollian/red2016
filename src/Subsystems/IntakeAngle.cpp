#include <Ports/Motor.hpp>
#include <Subsystems/IntakeAngle.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace IntakeAngle
{
	const float MOTOR_SPEED = 0.5;

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
}
