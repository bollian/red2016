#include <Ports/Motor.h>
#include <Subsystems/IntakeRoller.h>
#include <Utils.h>
#include <WPILib.h>

namespace IntakeRoller
{
	const float MOTOR_SPEED = 1.0;

	SpeedController* roller_motor;

	void initialize()
	{
		roller_motor = Utils::constructMotor(MotorPorts::INTAKE_ROLLER_MOTOR);
	}

	void process()
	{

	}

	void setSpeed(float speed)
	{
		roller_motor->Set(speed);
	}

	void setDirection(Utils::HorizontalDirection dir)
	{
		Utils::setDirection(&setSpeed, MOTOR_SPEED, MOTOR_SPEED, (int)dir);
	}

	float getSpeed()
	{
		return roller_motor->Get();
	}

	Utils::HorizontalDirection getDirection()
	{
		return (Utils::HorizontalDirection)Utils::getDirection(&getSpeed);
	}
}
