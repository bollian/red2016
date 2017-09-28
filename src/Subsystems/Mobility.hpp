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

	/**
	 * Sets whether or not the front of the robot is considered to be the side
	 * of the robot the shooter faces, or the side away from the shooter.
	 *
	 * This has the effect of reversing all drive motors.
	 */
	void useNormalOrientation(bool normal);

	/**
	 * Returns if the front of the robot is considered to be the same direction
	 * as the shooter, or the opposite direction
	 */
	bool usingNormalOrientation();

	void setLeftSpeed(float speed);
	void setRightSpeed(float speed);

	/**
	 * A convenience function that sets calls both setLeftSpeed and setRightSpeed
	 */
	void setStraight(float speed);
	
	void engageManualControl();

	/**
	 * Drives at the given speed while attempting to keep the robot pointed in
	 * the same direction
	 */
	void driveStraight(float speed);

	/**
	 * Drives a specific distance in centimeters while attempting to keep the
	 * robot pointed in the same direction
	 */
	void driveDistance(float centimeters);
	void interrupt();
	State getState();
}

#endif /* SRC_MOBILITY_H_ */
