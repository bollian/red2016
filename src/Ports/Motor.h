#ifndef SRC_PORTS_MOTOR_H_
#define SRC_PORTS_MOTOR_H_

namespace MotorPorts
{
	// motors
	const unsigned int RIGHT_MOTOR1 = 0;
	const unsigned int RIGHT_MOTOR2 = 1;
	const unsigned int LEFT_MOTOR1 = 2;
	const unsigned int LEFT_MOTOR2 = 3;

	const unsigned int FRONT_WINCH_MOTOR = 4;
	const unsigned int BACK_WINCH_MOTOR = 5;

	const unsigned int SHOOTER_WHEELS_MOTOR = 6;

	const unsigned int SHOOTER_PITCH_MOTOR = 8;
	const unsigned int HOLDER_WHEELS_MOTOR = 9;

	// NAVX
	const unsigned int INTAKE_ROLLER_MOTOR = 10; // N0
	const unsigned int INTAKE_ANGLE_MOTOR = 11; // N1
	const unsigned int CLIMBER_ARM_MOTOR = 12; // N2
}

#endif /* SRC_PORTS_MOTOR_H_ */
