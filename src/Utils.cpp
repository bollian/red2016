#include <Utils.h>
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


	float boundaryCheck(float target, float min, float max)
	{
		if(target > max)
		{
			return max;
		}
		if (target < min)
		{
			return min;
		}
		return target;
	}
	float deadZoneCheck(float axis, float offset)
	{
		if (axis > offset || axis < offset)
		{
			return axis;
		}
		return 0.0;
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
}
