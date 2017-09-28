#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <WPILib.h>

namespace Utils
{
	enum VerticalDirection
	{
		UP = 1,
		V_STILL = 0,
		DOWN = -1
	};
	enum HorizontalDirection
	{
		IN = 1,
		H_STILL = 0,
		OUT = -1
	};

	/**
	 * The type of motor controller currently being used by
	 * the robot
	 */
	enum MotorType
	{
		CAN_TALON,
		VICTOR_SP
	};

	/**
	 * Indicates whether or not the robot is using CANTalons
	 * or VictorSPs
	 */
	MotorType getMotorType();

	/**
	 * Constructs either a CANTalon or VictorSP motor controller
	 * depending on getMotorType()
	 */
	SpeedController* constructMotor(unsigned int port);
}

#endif /* SRC_UTILS_H_ */
