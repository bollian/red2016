#include <Ports/Motor.h>
#include <Subsystems/IntakeAngle.h>
#include <Utils.h>
#include <WPILib.h>

namespace IntakeAngle
{
	const float MOTOR_SPEED = 0.5;

	SpeedController* angle_motor = Utils::constructMotor(MotorPorts::INTAKE_ANGLE_MOTOR);

	void initialize()
	{

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
