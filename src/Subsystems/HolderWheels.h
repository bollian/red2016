#ifndef SRC_HOLDERWHEELS_H_
#define SRC_HOLDERWHEELS_H_

#include <Utils.h>

namespace HolderWheels
{
	void initialize();
	void process();

	void setDirection(Utils::HorizontalDirection dir);
	Utils::HorizontalDirection getDirection();
}

#endif /* SRC_HOLDERWHEELS_H_ */
