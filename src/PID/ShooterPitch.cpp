#include <PID/ShooterPitch.hpp>
#include <Subsystems/Sensors.hpp>
#include <Subsystems/ShooterPitch.hpp>

ShooterPitchPID* ShooterPitchPID::instance = nullptr;

ShooterPitchPID::ShooterPitchPID() : PIDManager(0.1, 0.0001, 0.0)
{
	
}

float ShooterPitchPID::returnPIDInput()
{
	return Sensors::getShooterAngle();
}

void ShooterPitchPID::usePIDOutput(float output, float feed_forward)
{
	ShooterPitch::setSpeed(output);
}

ShooterPitchPID* ShooterPitchPID::getInstance()
{
	if (!instance) {
		instance = new ShooterPitchPID();
	}
	return instance;
}
