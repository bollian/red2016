#ifndef SRC_SHOOTERPITCH_H_
#define SRC_SHOOTERPITCH_H_

#include <Utils.hpp>

namespace ShooterPitch
{
	enum State {
		DISABLED,
		WAITING,
		MANUAL_CONTROL,
		REACHING_ANGLE
	};
	
	extern const float SHOOTER_TO_TARGET_HEIGHT;

	void initialize();
	void process();
	void processPID();
	void enablePID(bool enable);

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

#endif /* SRC_SHOOTERPITCH_H_ */
