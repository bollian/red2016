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
	/**
	 * checks to see if a value is in an exclusive range
	 * @param  value the value to check
	 * @param  min   minimum required value
	 * @param  max   maxiumu required value
	 * @return       true if value is in the range (min, max) or (max, min) if max is less than min
	 */
	bool valueInRange(float value, float min, float max);
	/**
	 * limits a value to within a range
	 *
	 * if the lower limit is larger than the upper limit, this function flips the two
	 * @param  value the value to check the bounds against
	 * @param  lower the lower limit
	 * @param  upper the upper limits
	 * @return       if value is in the range [lower, upper], returns value; if value is outside that range, returns upper or lower accordingly
	 */
	float boundsCheck(float value, float lower, float upper);
	float wrap(float value, float min, float max);
	
	/**
	 * gets the shortest distance between value and center, and implements wrapping
	 *
	 * If min is greater than max, output scales backwards.  This can be useful
	 * with analog encoders that are mounted backwards.
	 *
	 * Example: a gyro outputs angles in the range [-180, 180].  You want to drive
	 * straight forward at angle 90.  Your current angle is -179.  getRelative will
	 * return 91, because if you add 91 to 90 you'd get -179 (with wrapping).  Now
	 * you know that you're 91 degrees to the right of 90.
	 * @param  value  the value that must be made relative
	 * @param  center the value to which the input is relative
	 * @param  min    the minimum value in the range.  If greater than maximum, output scales backwards
	 * @param  max    the maximum value in the range.  If less than minimum, output scales backwards
	 * @return        the shortest distance from center to value, scaled backwards if max < min
	 */
	float getRelative(float value, float center, float min, float max);
}

#endif /* SRC_UTILS_H_ */
