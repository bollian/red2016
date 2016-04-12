#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <PID/ShooterPitch.hpp>
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
	
	ShooterPitchPID* shooter_pitch_pid;
	
};

#endif // SRC_ROBOT_H_
