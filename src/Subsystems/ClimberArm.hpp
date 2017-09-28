#ifndef SRC_CLIMBERARM_H_
#define SRC_CLIMBERARM_H_

#include <Utils.hpp>

namespace ClimberArm
{
	void initialize();
	void process();

	void setSpeed(float speed);

	/**
	 * Sets the climber arm to a preset speed that is either up, down, or zero
	 */
	void setDirection(Utils::VerticalDirection dir);
	float getSpeed();
	Utils::VerticalDirection getDirection();
}

#endif /* SRC_CLIMBERARM_H_ */
