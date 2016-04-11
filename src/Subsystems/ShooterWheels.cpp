#include <Ports/Motor.hpp>
#include <Subsystems/ShooterWheels.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace ShooterWheels
{
	SpeedController* wheels_motor;

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

	float getSpeed()
	{
		return wheels_motor->Get();
	}
}
