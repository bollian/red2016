#ifndef SRC_MOBILITY_H_
#define SRC_MOBILITY_H_

namespace Mobility
{
	enum State {
		DISABLED,
		WAITING,
		MANUAL_CONTROL,
		DRIVE_STRAIGHT,
		DRIVE_DISTANCE
	};
	
	void initialize();
	void process();

	void useNormalOrientation(bool normal);
	bool usingNormalOrientation();

	void setLeftSpeed(float speed);
	void setRightSpeed(float speed);
	void setStraight(float speed);
	
	void engageManualControl();
	void driveStraight(float speed);
	void driveDistance(float centimeters);
	void interrupt();
	State getState();
}

#endif /* SRC_MOBILITY_H_ */
