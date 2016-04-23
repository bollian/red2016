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

	void setSpeed(float speed);
	void setDirection(Utils::VerticalDirection dir);

	float getSpeed();
	Utils::VerticalDirection getDirection();
	
	void engageManualControl();
	void goToAngle(float degrees);
	void interrupt();
	State getState();
	
	int getPresetCount();
	float getAnglePreset(int index);
}

#endif /* SRC_SUBSYSTEMS_INTAKEANGLE_H_ */
