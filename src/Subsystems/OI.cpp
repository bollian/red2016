#include <Ports/OI.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/OI.h>
#include <WPILib.h>

namespace OI
{
	Joystick* left_joy;
	Joystick* right_joy;

	void initialize()
	{
		right_joy = new Joystick(OIPorts::RIGHT_JOYSTICK);
		left_joy = new Joystick(OIPorts::LEFT_JOYSTICK);
	}

	void process()
	{
		Mobility::setLeftSpeed(getLeftJoystickY());
		Mobility::setRightSpeed(getRightJoystickY());
	}

	float getLeftJoystickY()
	{
		return left_joy->GetY();
	}

	float getRightJoystickY()
	{
		return right_joy->GetY();
	}
}
