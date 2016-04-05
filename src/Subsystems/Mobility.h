#ifndef SRC_MOBILITY_H_
#define SRC_MOBILITY_H_

namespace Mobility
{
	void initialize();
	void process();

	void useNormalOrientation(bool normal);
	bool usingNormalOrientation();

	void setLeftSpeed(float speed);
	void setRightSpeed(float speed);
	void setStraight(float speed);
}

#endif /* SRC_MOBILITY_H_ */
