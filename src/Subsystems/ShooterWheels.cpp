#include <Ports/Motor.h>
#include <Subsystems/ShooterWheels.h>
#include <Utils.h>
#include <WPILib.h>

namespace ShooterWheels
{
	SpeedController* wheels_motor = Utils::constructMotor(MotorPorts::SHOOTER_WHEELS_MOTOR);

	void initialize()
	{

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
