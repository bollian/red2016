#include <Utils.hpp>
#include <WPILib.h>

namespace Utils
{
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
