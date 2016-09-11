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
}
