#include <Ports/OI.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/OI.h>
#include <WPILib.h>

namespace OI
{
	Joystick* left_joy = new Joystick(OIPorts::LEFT_JOYSTICK);
	Joystick* right_joy = new Joystick(OIPorts::RIGHT_JOYSTICK);

	void initialize()
	{

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
