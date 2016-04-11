#ifndef SRC_CLIMBERARM_H_
#define SRC_CLIMBERARM_H_

#include <Utils.hpp>

namespace ClimberArm
{
	void initialize();
	void process();

	void setSpeed(float speed);
	void setDirection(Utils::VerticalDirection dir);
	float getSpeed();
	Utils::VerticalDirection getDirection();
}

#endif /* SRC_CLIMBERARM_H_ */
