#ifndef SRC_PORTS_OI_H_
#define SRC_PORTS_OI_H_

namespace OIPorts
{
	// joysticks
	extern const unsigned int LEFT_JOYSTICK;
	extern const unsigned int RIGHT_JOYSTICK;
	extern const unsigned int BUTTONS_JOYSTICK1;
	extern const unsigned int BUTTONS_JOYSTICK2;

	// drive joystick ports
	extern const unsigned int JOYSTICK_X_PORT;
	extern const unsigned int JOYSTICK_Y_PORT;
	extern const unsigned int JOYSTICK_Z_PORT;
	
	extern const unsigned int B_DRIVE_STRAIGHT_LEFT;
	extern const unsigned int B_DRIVE_STRAIGHT_RIGHT;

	extern const unsigned int B_TURN_X_AXIS_RIGHT;
	extern const unsigned int B_TURN_X_AXIS_LEFT;

	// buttons joystick 1, digital
	extern const unsigned int AUTO_AIM_BUTTON;
	extern const unsigned int SHOOT_BUTTON;
	extern const unsigned int MOVE_INTAKE_UP_BUTTON;
	extern const unsigned int MOVE_INTAKE_DOWN_BUTTON;
	extern const unsigned int PID_ENABLE_SWITCH;
	extern const unsigned int INTAKE_BELT_INWARD_SWITCH;
	extern const unsigned int INTAKE_BELT_OUTWARD_SWITCH;
	extern const unsigned int SENSOR_ENABLE_SWITCH;
	extern const unsigned int SHOOTER_WHEELS_SWITCH;

	// buttons joystick 1, analog
	extern const unsigned int SHOOTER_PITCH_DIAL; // X
	extern const unsigned int SHOOTER_SPEED_DIAL; // Y
	extern const unsigned int INTAKE_ANGLE_DIAL; // Z

	// buttons joystick 2, digital
	extern const unsigned int EXTEND_SCALING_ARM_BUTTON;
	extern const unsigned int RETRACT_SCALING_ARM_BUTTON;
	extern const unsigned int AUTO_CLIMBER_DEPLOY_BUTTON;
	extern const unsigned int AUTO_WINCH_BUTTON;
	extern const unsigned int MANUAL_WINCH_ENABLE_SWITCH;

	// buttons joystick 2, analog
	extern const unsigned int FRONT_WINCH_JOYSTICK; // X
	extern const unsigned int BACK_WINCH_JOYSTICK; // Y
}

#endif /* SRC_PORTS_OI_H_ */
