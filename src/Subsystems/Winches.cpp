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
		Utils::setDirection(&setFrontSpeed, WINCH_SPEED, WINCH_SPEED, (int)dir);
	}

	void setBackDirection(Utils::VerticalDirection dir)
	{
		Utils::setDirection(&setBackSpeed, WINCH_SPEED, WINCH_SPEED, (int)dir);
	}

	float getFrontSpeed()
	{
		return front_winch->Get();
	}

	float getBackSpeed()
	{
		return -back_winch->Get();
	}

	Utils::VerticalDirection getFrontDirection()
	{
		return (Utils::VerticalDirection)Utils::getDirection(&getFrontSpeed);
	}

	Utils::VerticalDirection getBackDirection()
	{
		return (Utils::VerticalDirection)Utils::getDirection(&getBackSpeed);
	}
}
