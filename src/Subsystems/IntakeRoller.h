#ifndef SRC_SUBSYSTEMS_INTAKEROLLER_H_
#define SRC_SUBSYSTEMS_INTAKEROLLER_H_

#include <Utils.h>

namespace IntakeRoller
{
	void initialize();
	void process();

	void setDirection(Utils::VerticalDirection dir);
	Utils::HorizontalDirection getDirection();
}

#endif /* SRC_SUBSYSTEMS_INTAKEROLLER_H_ */
