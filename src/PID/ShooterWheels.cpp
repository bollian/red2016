#include <PID/ShooterWheels.hpp>
#include <Subsystems/Sensors.hpp>
#include <Subsystems/ShooterWheels.hpp>

ShooterWheelsPID* ShooterWheelsPID::instance = nullptr;

const float ShooterWheelsPID::F_COEFFICIENT = 0.00016;

ShooterWheelsPID::ShooterWheelsPID() : PIDManager(0.001, 0.0, 0.001)
{
	
}

float ShooterWheelsPID::returnPIDInput()
{
	return Sensors::getShooterWheelRate();
}

float ShooterWheelsPID::getFeedForwardOutput(float new_target)
{
	return F_COEFFICIENT * (new_target / 5000.0);
}

void ShooterWheelsPID::usePIDOutput(float output, float feed_forward)
{
	ShooterWheels::setSpeed(output + feed_forward);
}

ShooterWheelsPID* ShooterWheelsPID::getInstance()
{
	if (!instance) {
		instance = new ShooterWheelsPID();
	}
	return instance;
}
