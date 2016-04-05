#ifndef SRC_SUBSYSTEMS_INTAKEANGLE_H_
#define SRC_SUBSYSTEMS_INTAKEANGLE_H_

#include <Utils.h>

namespace IntakeAngle
{
	void initialize();
	void process();

	void setSpeed(float speed);
	void setDirection(Utils::VerticalDirection dir);

	float getSpeed();
	Utils::VerticalDirection getDirection();
}

#endif /* SRC_SUBSYSTEMS_INTAKEANGLE_H_ */
