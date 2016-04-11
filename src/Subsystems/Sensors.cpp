#include <NAVX/AHRS.h>
#include <Ports/Analog.h>
#include <Ports/CAN.h>
#include <Ports/Digital.h>
#include <Ports/I2C.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>
#include <Utils.h>
#include <WPILib.h>

// get access to pi const: M_PI
#define _USE_MATH_DEFINES
#include <math.h>

namespace Sensors
{
	const float MIN_SHOOTER_ENCODER_VOLT = 1.4;
	const float MAX_SHOOTER_ENCODER_VOLT = 2.6;

	const float INTAKE_ENCODER_VOLT_SHIFT = 1.17;
	const float MIN_INTAKE_ENCODER_VOLT = 2.5;
	const float MAX_INTAKE_ENCODER_VOLT = 3.72;

	const int SHOOTER_WHEEL_PPR = 1;

	const int LIDAR_OFFSET = 10;

	const float DRIVE_WHEEL_DIAMETER = 7.9502;
	const int DRIVE_ENCODER_PPR = 128;

	float getShooterAngleActual();

	AHRS* navx;

	AnalogInput* shooter_encoder;
	int shooter_angle_offset = 0;

	AnalogInput* intake_encoder;

	Timer* tach_timer;
	Counter* shooter_wheel_tach;
	float last_tach_timestamp = 0.0;
	int last_tach_count = 0;
	float tach_rate = 0.0;

	Timer* lidar_timer;
	I2C* lidar;
	int lidar_distance = 0; // centimeters
	int lidar_stage = 0;

	Encoder* left_drive_encoder;
	Encoder* right_drive_encoder;

	DigitalInput* ball_limit;
	DigitalInput* shooter_limit;

	PowerDistributionPanel* pdp;

	void initialize()
	{
		navx = new AHRS(SPI::Port::kMXP);

		shooter_encoder = new AnalogInput(AnalogPorts::SHOOTER_ENCODER);

		intake_encoder = new AnalogInput(AnalogPorts::INTAKE_ENCODER);

		tach_timer = new Timer();
		shooter_wheel_tach = new Counter(DigitalPorts::SHOOTER_WHEEL_TACH);

		lidar_timer = new Timer();
		lidar = new I2C(I2C::Port::kMXP, I2CPorts::LIDAR_ADDRESS);

		left_drive_encoder = new Encoder(DigitalPorts::LEFT_ENCODER_A, DigitalPorts::LEFT_ENCODER_B);
		right_drive_encoder = new Encoder(DigitalPorts::RIGHT_ENCODER_A, DigitalPorts::RIGHT_ENCODER_B, true); // the right encoder goes in reverse

		ball_limit = new DigitalInput(DigitalPorts::BALL_LIMIT);
		shooter_limit = new DigitalInput(DigitalPorts::SHOOTER_LIMIT);

		pdp = new PowerDistributionPanel(CANPorts::PDP);

		float distance_per_pulse = 2.0 * M_PI * DRIVE_WHEEL_DIAMETER / (float)DRIVE_ENCODER_PPR;
		left_drive_encoder->SetDistancePerPulse(distance_per_pulse);
		right_drive_encoder->SetDistancePerPulse(distance_per_pulse);

		tach_timer->Start();
		lidar_timer->Start();

		tach_timer->Reset();
		lidar_timer->Reset();
	}

	void process()
	{
		// update lidar
		if (lidar_timer->Get() > (0.04 * (float)lidar_stage)) {
			uint8_t lidar_range_copy;
			switch (lidar_stage) {
			case 0:
				lidar->Write(I2CPorts::LIDAR_INIT_REGISTER, 4);
				++lidar_stage;
				break;
			case 1:
				lidar_range_copy = I2CPorts::LIDAR_RANGE_REGISTER;
				lidar->WriteBulk(&lidar_range_copy, 1);
				++lidar_stage;
				break;
			case 2:
				uint8_t buffer[2];
				lidar->ReadOnly(2, buffer);
				lidar_distance = ((buffer[0] << 8) + buffer[1]) - LIDAR_OFFSET;
				++lidar_stage;
				break;
			case 3:
				lidar_timer->Reset();
				lidar_stage = 0;
			}
		}

		// update shooter wheel tachometer speed
		int tach_count = shooter_wheel_tach->Get();
		float tach_timestamp = tach_timer->Get();
		if (tach_count > last_tach_count) {
			tach_rate = (tach_count - last_tach_count) / (tach_timestamp - last_tach_timestamp) / (float)SHOOTER_WHEEL_PPR * 60.0;

			last_tach_count = tach_count;
			last_tach_timestamp = tach_timestamp;
		}
		else if (tach_timestamp - last_tach_timestamp > 1.0) {
			tach_rate = 0.0;
		}

		// update the shooter home switch
		if (isShooterLimitPressed() && isShooterAngleEnabled()) {
			shooter_angle_offset = getShooterAngleActual();
		}
	}

	float getRobotAngle()
	{
		if (isGyroEnabled()) {
			return navx->GetYaw();
		}
		else {
			return 0.0;
		}
	}

	float getShooterAngleActual()
	{
		return 90.0 * (shooter_encoder->GetVoltage() - MIN_SHOOTER_ENCODER_VOLT) / (MAX_SHOOTER_ENCODER_VOLT - MIN_SHOOTER_ENCODER_VOLT);
	}

	float getShooterAngle()
	{
		if (isShooterAngleEnabled()) {
			return getShooterAngleActual() - shooter_angle_offset;
		}
		else {
			return 0.0;
		}
	}

	float getIntakeAngle()
	{
		if (isIntakeAngleEnabled()) {
			float voltage = intake_encoder->GetVoltage() + INTAKE_ENCODER_VOLT_SHIFT; // shift the voltages away from the 0.0 - 5.0 discontinuity
			voltage = Utils::wrap(voltage, 0.0, 5.0);
			voltage = 5.0 - voltage; // flip the voltages so that higher values give higher angles
			return 90.0 * (voltage - MIN_INTAKE_ENCODER_VOLT) / (MAX_INTAKE_ENCODER_VOLT - MIN_INTAKE_ENCODER_VOLT);
		}
		else {
			return 0.0;
		}
	}

	float getShooterWheelRate()
	{
		if (isShooterTachEnabled()) {
			return tach_rate;
		}
		else {
			return 0.0;
		}
	}

	int getLidarDistance()
	{
		if (isLidarEnabled()) {
			return lidar_distance;
		}
		else {
			return 0;
		}
	}

	float getLeftEncoderDistance()
	{
		if (areDriveEncodersEnabled()) {
			if (Mobility::usingNormalOrientation()) {
				return left_drive_encoder->GetDistance();
			}
			else {
				return -left_drive_encoder->GetDistance();
			}
		}
		else {
			return 0.0;
		}
	}

	float getRightEncoderDistance()
	{
		if (areDriveEncodersEnabled()) {
			if (Mobility::usingNormalOrientation()) {
				return right_drive_encoder->GetDistance();
			}
			else {
				return -right_drive_encoder->GetDistance();
			}
		}
		else {
			return 0.0;
		}
	}

	float getLeftEncoderSpeed()
	{
		if (areDriveEncodersEnabled()) {
			if (Mobility::usingNormalOrientation()) {
				return left_drive_encoder->GetRate();
			}
			else {
				return -left_drive_encoder->GetRate();
			}
		}
		else {
			return 0.0;
		}
	}

	float getRightEncoderSpeed()
	{
		if (areDriveEncodersEnabled()) {
			if (Mobility::usingNormalOrientation()) {
				return right_drive_encoder->GetRate();
			}
			else {
				return -right_drive_encoder->GetRate();
			}
		}
		else {
			return 0.0;
		}
	}

	bool isBallLimitPressed()
	{
		if (isBallLimitEnabled()) {
			// all limit switches are normally open so that it looks like they're not pressed when not plugged in
			return !ball_limit->Get();
		}
		else {
			return false;
		}
	}

	bool isShooterLimitPressed()
	{
		if (isShooterLimitEnabled()) {
			// all limit switches are normally open so that it looks like they're not pressed when not plugged in
			return !shooter_limit->Get();
		}
		else {
			return false;
		}
	}

	float getCurrent(unsigned int channel)
	{
		if (isPDPEnabled()) {
			return pdp->GetCurrent(channel);
		}
		else {
			return 0.0;
		}
	}

	bool isGyroEnabled()
	{
		return true;
	}

	bool isShooterAngleEnabled()
	{
		return true;
	}

	bool isIntakeAngleEnabled()
	{
		return true;
	}

	bool isShooterTachEnabled()
	{
		return true;
	}

	bool isLidarEnabled()
	{
		return true;
	}

	bool areDriveEncodersEnabled()
	{
		return false;
	}

	bool isBallLimitEnabled()
	{
		return true;
	}

	bool isShooterLimitEnabled()
	{
		return true;
	}

	bool isPDPEnabled()
	{
		return true;
	}
}
