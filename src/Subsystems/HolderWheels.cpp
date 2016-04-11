#include <Ports/Motor.h>
#include <Subsystems/HolderWheels.h>
#include <Utils.h>
#include <WPILib.h>

namespace HolderWheels
{
	SpeedController* wheels_motor;
	const float MOTOR_SPEED = 1.0;

	void initialize()
	{
		wheels_motor = Utils::constructMotor(MotorPorts::HOLDER_WHEELS_MOTOR);
	}

	void process()
	{

	}

	void setSpeed(float speed)
	{
		wheels_motor->Set(speed);
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
}
