#include <Ports/OI.hpp>

namespace OIPorts
{
	// joysticks
	const unsigned int LEFT_JOYSTICK = 0;
	const unsigned int RIGHT_JOYSTICK = 1;
	const unsigned int BUTTONS_JOYSTICK1 = 2;
	const unsigned int BUTTONS_JOYSTICK2 = 3;

	// drive joystick ports
	const unsigned int JOYSTICK_X_PORT = 0;
	const unsigned int JOYSTICK_Y_PORT = 1;
	const unsigned int JOYSTICK_Z_PORT = 2;
	
	const unsigned int B_DRIVE_STRAIGHT_LEFT = 1;
	const unsigned int B_DRIVE_STRAIGHT_RIGHT = 1;

	const unsigned int B_TURN_X_AXIS_RIGHT = 2;
	const unsigned int B_TURN_X_AXIS_LEFT = 2;

	// buttons joystick 1, digital
	const unsigned int AUTO_AIM_BUTTON = 1;
	const unsigned int SHOOT_BUTTON = 2;
	const unsigned int MOVE_INTAKE_UP_BUTTON = 3;
	const unsigned int MOVE_INTAKE_DOWN_BUTTON = 4;
	const unsigned int PID_ENABLE_SWITCH = 5;
	const unsigned int INTAKE_BELT_FORWARD_SWITCH = 6;
	const unsigned int INTAKE_BELT_BACKWARD_SWITCH = 7;
	const unsigned int SENSOR_ENABLE_SWITCH = 8;
	const unsigned int SHOOTER_WHEELS_SWITCH = 9;

	// buttons joystick 1, analog
	const unsigned int SHOOTER_PITCH_DIAL = JOYSTICK_X_PORT; // X
	const unsigned int SHOOTER_SPEED_DIAL = JOYSTICK_Y_PORT; // Y
	const unsigned int INTAKE_ANGLE_DIAL = JOYSTICK_Z_PORT; // Z

	// buttons joystick 2, digital
	const unsigned int EXTEND_SCALING_ARM_BUTTON = 1;
	const unsigned int RETRACT_SCALING_ARM_BUTTON = 2;
	const unsigned int AUTO_CLIMBER_DEPLOY_BUTTON = 3;
	const unsigned int AUTO_WINCH_BUTTON = 4;
	const unsigned int MANUAL_WINCH_ENABLE_SWITCH = 5;

	// buttons joystick 2, analog
	const unsigned int FRONT_WINCH_JOYSTICK = JOYSTICK_X_PORT; // X
	const unsigned int BACK_WINCH_JOYSTICK = JOYSTICK_Y_PORT; // Y
}
