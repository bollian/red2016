#include <Ports/Motor.hpp>
#include <Subsystems/Winches.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace Winches
{
	const float WINCH_SPEED = 1.0;

	SpeedController* front_winch;
	SpeedController* back_winch;

	void initialize()
	{
		front_winch = Utils::constructMotor(MotorPorts::FRONT_WINCH_MOTOR);
		back_winch = Utils::constructMotor(MotorPorts::BACK_WINCH_MOTOR);
	}

	void process()
	{

	}

	void setFrontSpeed(float speed)
	{
		front_winch->Set(speed);
	}

	void setBackSpeed(float speed)
	{
		back_winch->Set(-speed);
	}

	void setFrontDirection(Utils::VerticalDirection dir)
	{
		switch (dir) {
		case Utils::VerticalDirection::UP:
			setFrontSpeed(WINCH_SPEED);
			break;
		case Utils::VerticalDirection::V_STILL:
			setFrontSpeed(0.0);
			break;
		case Utils::VerticalDirection::DOWN:
			setFrontSpeed(-WINCH_SPEED);
			break;
		}
	}

	void setBackDirection(Utils::VerticalDirection dir)
	{
		switch (dir) {
		case Utils::VerticalDirection::UP:
			setBackSpeed(WINCH_SPEED);
			break;
		case Utils::VerticalDirection::V_STILL:
			setBackSpeed(0.0);
			break;
		case Utils::VerticalDirection::DOWN:
			setBackSpeed(-WINCH_SPEED);
			break;
		}
	}

	float getFrontSpeed()
	{
		return front_winch->Get();
	}

	float getBackSpeed()
	{
		return -back_winch->Get();
	}

	Utils::VerticalDirection getDirection(float speed)
	{
		if (speed > 0.0) {
			return Utils::VerticalDirection::UP;
		}
		if (speed < 0.0) {
			return Utils::VerticalDirection::DOWN;
		}
		return Utils::VerticalDirection::V_STILL;
	}

	Utils::VerticalDirection getFrontDirection()
	{
		return getDirection(getFrontSpeed());
	}

	Utils::VerticalDirection getBackDirection()
	{
		return getDirection(getBackSpeed());
	}
}
