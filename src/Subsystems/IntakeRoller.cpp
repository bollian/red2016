#include <Ports/Motor.hpp>
#include <Subsystems/IntakeRoller.hpp>
#include <Utils.hpp>
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
		switch (dir) {
		case Utils::HorizontalDirection::IN:
			setSpeed(MOTOR_SPEED);
			break;
		case Utils::HorizontalDirection::H_STILL:
			setSpeed(0.0);
			break;
		case Utils::HorizontalDirection::OUT:
			setSpeed(MOTOR_SPEED);
			break;
		}
	}

	float getSpeed()
	{
		return roller_motor->Get();
	}

	Utils::HorizontalDirection getDirection()
	{
		float speed = getSpeed();
		if (speed > 0.0) {
			return Utils::HorizontalDirection::IN;
		}
		else if (speed < 0.0) {
			return Utils::HorizontalDirection::OUT;
		}
		return Utils::HorizontalDirection::H_STILL;
	}
}
