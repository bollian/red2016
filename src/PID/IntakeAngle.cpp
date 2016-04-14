#include <PID/IntakeAngle.hpp>
#include <Subsystems/IntakeAngle.hpp>
#include <Subsystems/Sensors.hpp>

IntakeAnglePID* IntakeAnglePID::instance = nullptr;

IntakeAnglePID::IntakeAnglePID() : PIDManager(0.02, 0.0001, 0.0)
{
	
}

float IntakeAnglePID::returnPIDInput()
{
	return Sensors::getIntakeAngle();
}

float IntakeAnglePID::getFeedForwardOutput(float target)
{
	if (target != getTarget()) {
		clearAccumulatedError();
	}
	return 0.0;
}

void IntakeAnglePID::usePIDOutput(float output, float feed_forward)
{
	IntakeAngle::setSpeed(output);
}

IntakeAnglePID* IntakeAnglePID::getInstance()
{
	if (!instance) {
		instance = new IntakeAnglePID();
	}
	return instance;
}
