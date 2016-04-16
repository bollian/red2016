#ifndef SRC_SHOOTERPITCH_H_
#define SRC_SHOOTERPITCH_H_

#include <Utils.hpp>

namespace ShooterPitch
{
	extern const float SHOOTER_TO_TARGET_HEIGHT;

	void initialize();
	void process();

	void setSpeed(float speed);
	void setDirection(Utils::VerticalDirection dir);
	
	float getSpeed();
	Utils::VerticalDirection getDirection();
	
	int getPresetCount();
	float getAnglePreset(int index);
}

#endif /* SRC_SHOOTERPITCH_H_ */
