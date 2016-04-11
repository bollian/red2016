#ifndef SRC_WINCHES_H_
#define SRC_WINCHES_H_

#include <Utils.hpp>

namespace Winches
{
	void initialize();
	void process();

	void setFrontSpeed(float speed);
	void setBackSpeed(float speed);

	void setFrontDirection(Utils::VerticalDirection dir);
	void setBackDirection(Utils::VerticalDirection dir);

	float getFrontSpeed();
	float getBackSpeed();

	Utils::VerticalDirection getFrontDirection();
	Utils::VerticalDirection getBackDirection();
}

#endif /* SRC_WINCHES_H_ */
