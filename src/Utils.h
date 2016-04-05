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
	void setDirection(void (*setter)(float), float up_speed, float down_speed, int dir);
	int getDirection(float (*getter)());

	enum MotorType
	{
		CAN_TALON,
		VICTOR_SP
	};

	MotorType getMotorType();
	SpeedController* constructMotor(unsigned int port);

	int convertVoltage(float voltage, int voltage_levels, float max_voltage);
	float boundaryCheck(float target, float min, float max);
	float deadZoneCheck(float axis, float offset);
	float wrap(float value, float min, float max);
}

#endif /* SRC_UTILS_H_ */
