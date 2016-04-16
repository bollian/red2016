#ifndef SRC_SUBSYSTEMS_SENSORS_H_
#define SRC_SUBSYSTEMS_SENSORS_H_

namespace Sensors
{
	/*
	 * All distances, unless otherwise noted, are in centimeters.
	 */

	void initialize();
	void process();

	float getRobotAngle(); // degrees
	float getShooterAngle(); // degrees
	float getIntakeAngle(); // degrees

	float getShooterWheelRate(); // rotations per minute

	int getLidarDistance(); // centimeters

	float getLeftEncoderDistance(); // centimeters
	float getRightEncoderDistance(); // centimeters

	float getLeftEncoderSpeed(); // centimeters per second
	float getRightEncoderSpeed(); // centimeters per second

	bool isBallLimitPressed();
	bool isShooterLimitPressed();

	float getCurrent(unsigned int channel);

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
