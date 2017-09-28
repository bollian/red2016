#ifndef SRC_SUBSYSTEMS_SENSORS_H_
#define SRC_SUBSYSTEMS_SENSORS_H_

namespace Sensors
{
	/*
	 * All distances, unless otherwise noted, are in centimeters.
	 */
	extern const float MIN_GYRO_ANGLE;
	extern const float MAX_GYRO_ANGLE;

	void initialize();
	void process();

	/**
	 * Returns the angle (yaw) of the robot from it's position at bootup
	 */
	float getRobotAngle();

	/**
	 * Returns the angle (pitch) of the shooter from it's home position in degrees
	 */
	float getShooterAngle(); // degrees

	/**
	 * Returns the angle (pitch) of the intake arm from the horizontal in degrees
	 */
	float getIntakeAngle();

	/**
	 * Returns the spin rate of the shooter wheels in rotations per minute
	 */
	float getShooterWheelRate();

	/**
	 * Returns the distance between the front of the robot and the object closest
	 * in front of it, as measured by the LIDAR sensor in centimeters
	 */
	int getLidarDistance();

	/**
	 * Returns the distance traveled by the left drive wheels since bootup in centimeters
	 */
	float getLeftEncoderDistance();

	/**
	 * Returns the distance traveled by the right drive wheels since bootup in centimeters
	 */
	float getRightEncoderDistance();

	/**
	 * Returns the current speed of the left drive train in centimeters per second
	 */
	float getLeftEncoderSpeed();

	/**
	 * Returns the current speed of the right drive train in centimeters per second
	 */
	float getRightEncoderSpeed();

	/**
	 * Returns whether the ball limit switch is being pressed by a ball, and therefore
	 * if there's a ball ready to be shot
	 */
	bool isBallLimitPressed();

	/**
	 * Returns whether or not the shooter is in it's home position
	 */
	bool isShooterLimitPressed();

	/**
	 * Returns the current draw on a Power Distribution Panel channel in amperes
	 */
	float getCurrent(unsigned int channel);

	/**
	 * The below functions check to see if the corresponding sensors are allowed to be
	 * used.  Function calls to Sensors that rely on disabled sensors will return some
	 * default value instead of throwing an exception.  Because those default values
	 * will be indistiguishable from a normally running sensor, you should always call
	 * the corresponding isEnabled function, and have backup code for the disabled case.
	 *
	 * A sensor may be hard disabled or soft disabled.  Hard disabled means that the
	 */

	bool isGyroEnabled();
	bool isShooterAngleEnabled();
	bool isIntakeAngleEnabled();
	bool isShooterTachEnabled();
	bool isLidarEnabled();
	bool areDriveEncodersEnabled();
	bool isBallLimitEnabled();
	bool isShooterLimitEnabled();
	bool isPDPEnabled();
	
	void enableGyro(bool enable);
	void enableShooterAngle(bool enable);
	void enableIntakeAngle(bool enable);
	void enableShooterTach(bool enable);
	void enableLidar(bool enable);
	void enableDriveEncoders(bool enable);
	void enableBallLimit(bool enable);
	void enableShooterLimit(bool enable);
	void enablePDP(bool enable);
}

#endif /* SRC_SUBSYSTEMS_SENSORS_H_ */
