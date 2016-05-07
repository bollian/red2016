#include <Ports/Motor.hpp>
#include <math.h>
#include <Subsystems/Mobility.hpp>
#include <Subsystems/Sensors.hpp>
#include <Utils.hpp>
#include <WPILib.h>

namespace Mobility
{
	const float ACCEPTABLE_ANGLE_ERROR = 1.0;
	const float ACCEPTABLE_DIST_ERROR = 5.0;
	
	const float MAX_SPEED_ADJUSTMENT = 3.2;
	
	SpeedController* left_motor1;
	SpeedController* left_motor2;
	SpeedController* right_motor1;
	SpeedController* right_motor2;

	State state = State::WAITING;

	bool normal_orientation = true;
	float target_angle = 0.0;
	float target_speed = 0.0;
	float left_target_dist = 0.0;
	float right_target_dist = 0.0;

	void setState(State new_state);

	void initialize()
	{
		left_motor1 = Utils::constructMotor(MotorPorts::LEFT_MOTOR1);
		left_motor2 = Utils::constructMotor(MotorPorts::LEFT_MOTOR2);
		right_motor1 = Utils::constructMotor(MotorPorts::RIGHT_MOTOR1);
		right_motor2 = Utils::constructMotor(MotorPorts::RIGHT_MOTOR2);
	}

	void process()
	{
		float left_dist;
		float right_dist;
		switch (state) {
		case State::DISABLED:
			left_motor1->Set(0.0);
			left_motor2->Set(0.0);
			right_motor1->Set(0.0);
			right_motor2->Set(0.0);
			break;
		
		case State::WAITING:
		case State::MANUAL_CONTROL:
			break;
			
		case State::DRIVE_DISTANCE:
			left_dist = Sensors::getLeftEncoderDistance();
			right_dist = Sensors::getRightEncoderDistance();
			
			if (fabs(left_dist - left_target_dist) < ACCEPTABLE_DIST_ERROR && fabs(right_dist - right_target_dist) < ACCEPTABLE_DIST_ERROR) {
				setState(State::WAITING);
				break;
			}
			else {
				target_speed = Utils::boundsCheck(((left_target_dist - left_dist) + (right_target_dist - right_dist)) / 2.0, -1.0, 1.0);
			}
		case State::DRIVE_STRAIGHT:
			float adjusted_speed = MAX_SPEED_ADJUSTMENT *
			    Utils::getRelative(Sensors::getRobotAngle(), target_angle, Sensors::MIN_GYRO_ANGLE, Sensors::MAX_GYRO_ANGLE) / 180.0;
			setLeftSpeed(target_speed - adjusted_speed);
			setRightSpeed(target_speed + adjusted_speed);
			break;
		}
	}

	void useNormalOrientation(bool normal)
	{
		normal_orientation = normal;
	}

	bool usingNormalOrientation()
	{
		return normal_orientation;
	}

	void setLeftSpeed(float speed)
	{
		if (state != State::DISABLED) {
			speed = normal_orientation ? speed : -speed;
			left_motor1->Set(speed);
			left_motor2->Set(speed);
		}
	}

	void setRightSpeed(float speed)
	{
		if (state != State::DISABLED) {
			speed = normal_orientation ? -speed : speed;
			right_motor1->Set(speed);
			right_motor2->Set(speed);
		}
	}

	void setStraight(float speed)
	{
		setLeftSpeed(speed);
		setRightSpeed(speed);
	}
	
	void engageManualControl()
	{
		setState(State::MANUAL_CONTROL);
	}
	
	void driveStraight(float speed)
	{
		target_speed = speed;
		setState(State::DRIVE_STRAIGHT);
	}
	
	void driveDistance(float distance)
	{
		left_target_dist = Sensors::getLeftEncoderDistance() + distance;
		right_target_dist = Sensors::getRightEncoderDistance() + distance;
		setState(State::DRIVE_DISTANCE);
	}
	
	void interrupt()
	{
		setState(State::WAITING);
	}
	
	State getState()
	{
		return state;
	}
	
	void setState(State new_state)
	{
		if (state != new_state) {
			switch (state) {
			case State::DISABLED:
				return; // do not allow a change from DISABLED
			
			case State::WAITING:
				break;
			
			case State::MANUAL_CONTROL:
			case State::DRIVE_STRAIGHT:
			case State::DRIVE_DISTANCE:
				setLeftSpeed(0.0);
				setRightSpeed(0.0);
				break;
			}
			
			switch (new_state) {
			case State::DISABLED:
				left_motor1->Set(0.0);
				left_motor2->Set(0.0);
				right_motor1->Set(0.0);
				right_motor2->Set(0.0);
				break;
			
			case State::MANUAL_CONTROL:
			case State::WAITING:
				break;
				
			case State::DRIVE_DISTANCE:
			case State::DRIVE_STRAIGHT:
				target_angle = Sensors::getRobotAngle();
				break;
			}
			
			state = new_state;
		}
	}
}
