#include <Ports/Motor.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/ShooterPitch.h>
#include <Utils.h>
#include <WPILib.h>

namespace ShooterPitch
{
	const float SHOOTER_TO_TARGET_HEIGHT = 45.72; // cm
	const float MOTOR_SPEED = 1.0;

	SpeedController* pitch_motor;

	void initialize()
	{
		pitch_motor = Utils::constructMotor(MotorPorts::SHOOTER_PITCH_MOTOR);
	}

	void process()
	{
		if (getDirection() == Utils::VerticalDirection::DOWN && Sensors::isShooterLimitPressed()) {
			setSpeed(0.0);
		}
	}

	void setSpeed(float speed)
	{
		if (speed < 0.0 && Sensors::isShooterLimitPressed()) {
			speed = 0.0;
		}
		pitch_motor->Set(speed);
	}

	void setDirection(Utils::VerticalDirection dir)
	{
		Utils::setDirection(&setSpeed, MOTOR_SPEED, MOTOR_SPEED, (int)dir);
	}

	float getSpeed()
	{
		return pitch_motor->Get();
	}

	Utils::VerticalDirection getDirection()
	{
		return (Utils::VerticalDirection)Utils::getDirection(&getSpeed);
	}
}
