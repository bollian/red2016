#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <PID/IntakeAngle.hpp>
#include <PID/ShooterPitch.hpp>
#include <PID/ShooterWheels.hpp>
#include <WPILib.h>

class Robot : public SampleRobot
{
public:
	Robot();
	void RobotInit();
	
	void Disabled();
	void Autonomous();
	void OperatorControl();
	void Test();
	
private:
	void processPID();
	
	IntakeAnglePID* intake_angle_pid;
	ShooterPitchPID* shooter_pitch_pid;
	ShooterWheelsPID* shooter_wheels_pid;
	
};

#endif // SRC_ROBOT_H_
