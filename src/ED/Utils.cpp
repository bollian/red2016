#include <math.h>
#include <ED/Utils.hpp>

namespace ED
{
	int convertVoltage(float voltage, int voltage_levels, float max_voltage)
	{
		float output = (voltage / max_voltage) * ((float) voltage_levels - 1); // needs to be rounded, never do == w/ decimals
		return (int) (output + 0.5); // round the value
	}

	bool valueInRange(float value, float min, float max)
	{
		if (max < min) {
			float tmp = min;
			min = max;
			max = tmp;
		}

		return value > min && value < max;
	}

	float boundsCheck(float value, float lower, float upper)
	{
		if (lower > upper) {
			float tmp;
			tmp = lower;
			lower = upper;
			upper = tmp;
		}

		if (value > upper) {
			return upper;
		}
		if (value < lower) {
			return lower;
		}
		return value;
	}

	float wrap(float value, float min, float max)
	{
		while (value > max) {
			value -= (max - min);
		}
		while (value < min) {
			value += (max - min);
		}
		return value;
	}

	float getRelative(float value, float center, float min, float max)
	{
		if (max < min) {
			// if min is greater than max, values scale backwards
			float tmp = min;
			min = max;
			max = tmp;

			value = max - value + min;
			center = max - center + min;
		}

		value = value - center;
		if (fabs(value) > (max - min) / 2.0) {
			value += value < 0.0 ? max - min : min - max;
		}

		return value;
	}
}
