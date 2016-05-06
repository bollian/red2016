#include <math.h>
#include <Utils.hpp>
#include <WPILib.h>

namespace Utils
{
	void setDirection(void (*setter)(float), float up_speed, float down_speed, int dir)
	{
		switch (dir) {
		case 1:
			setter(up_speed);
			break;
		case 0:
			setter(0.0);
			break;
		case -1:
			setter(-down_speed);
			break;
		}
	}

	int getDirection(float (*getter)())
	{
		float speed = getter();
		return speed > 0.0 ?
		           1 :
		           (speed < 0.0 ?
		               -1 :
		               0);
	}

	MotorType getMotorType()
	{
		return MotorType::VICTOR_SP;
	}

	SpeedController* constructMotor(unsigned int port)
	{
		if (getMotorType() == MotorType::CAN_TALON)
		{
			return new CANTalon(port + 1);
		}
		else if (getMotorType() == MotorType::VICTOR_SP)
		{
			return new VictorSP(port);
		}
		else
		{
			// Log::getInstance()->write(Log::ERROR_LEVEL, "Unable to construct motor because of unknown motor type");
			return nullptr;
		}
	}

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
		while (value < min)
		{
			value += (max - min);
		}
		while (value > max)
		{
			value += (min - max);
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
