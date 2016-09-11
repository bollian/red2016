#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <WPILib.h>

class Robot : public SampleRobot
{
public:
	void RobotInit();
	
	void Disabled();
	void Autonomous();
	void OperatorControl();
	void Test();
	
private:
	void processPID();
	void interruptAll();
	
};

#endif // SRC_ROBOT_H_
