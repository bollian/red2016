#ifndef SRC_SUBSYSTEMS_INTAKEROLLER_H_
#define SRC_SUBSYSTEMS_INTAKEROLLER_H_

#include <Utils.hpp>

namespace IntakeRoller
{
	void initialize();
	void process();

	void setDirection(Utils::HorizontalDirection dir);
	Utils::HorizontalDirection getDirection();
}

#endif /* SRC_SUBSYSTEMS_INTAKEROLLER_H_ */
