#ifndef SRC_SUBSYSTEMS_INTAKEANGLE_H_
#define SRC_SUBSYSTEMS_INTAKEANGLE_H_

#include <Utils.hpp>

namespace IntakeAngle
{
	enum State {
		DISABLED,
		WAITING,
		MANUAL_CONTROL,
		REACHING_ANGLE
	};
	
	void initialize();
	void process();
	void processPID();
	void enablePID(bool enable);

	/**
	 * Sets the turn rate of the intake arm.  Positive speeds move the arm up,
	 * negative speeds move the arm down.
	 */
	void setSpeed(float speed);
	void setDirection(Utils::VerticalDirection dir);

	float getSpeed();
	Utils::VerticalDirection getDirection();
	
	void engageManualControl();

	/**
	 * Uses sensors to try and reach a specific angle from the horizontal.
	 * Will use PID control only if OI says it's enabled
	 */
	void goToAngle(float degrees);

	void interrupt();
	State getState();
	
	int getPresetCount();
	float getAnglePreset(int index);
}

#endif /* SRC_SUBSYSTEMS_INTAKEANGLE_H_ */
