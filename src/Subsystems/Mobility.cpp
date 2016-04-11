#include <Ports/Motor.h>
#include <Subsystems/Mobility.h>
#include <Utils.h>
#include <WPILib.h>

namespace Mobility
{
	SpeedController* left_motor1;
	SpeedController* left_motor2;
	SpeedController* right_motor1;
	SpeedController* right_motor2;

	bool normal_orientation = true;

	void initialize()
	{
		left_motor1 = Utils::constructMotor(MotorPorts::LEFT_MOTOR1);
		left_motor2 = Utils::constructMotor(MotorPorts::LEFT_MOTOR2);
		right_motor1 = Utils::constructMotor(MotorPorts::RIGHT_MOTOR1);
		right_motor2 = Utils::constructMotor(MotorPorts::RIGHT_MOTOR2);
	}

	void process()
	{

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
		if (normal_orientation) {
			left_motor1->Set(speed);
			left_motor2->Set(speed);
		}
		else {
			left_motor1->Set(-speed);
			left_motor2->Set(-speed);
		}
	}

	void setRightSpeed(float speed)
	{
		if (normal_orientation) {
			right_motor1->Set(-speed);
			right_motor2->Set(-speed);
		}
		else {
			right_motor1->Set(speed);
			right_motor2->Set(speed);
		}
	}

	void setStraight(float speed)
	{
		setLeftSpeed(speed);
		setRightSpeed(speed);
	}
}
