#ifndef SRC_PID_INTAKEANGLEPID_H_
#define SRC_PID_INTAKEANGLEPID_H_

#include <ED/PIDManager.hpp>

class IntakeAnglePID : public ED::PIDManager
{
public:
	static IntakeAnglePID* getInstance();

protected:
	float returnPIDInput();
	float getFeedForwardOutput(float target);
	void usePIDOutput(float output, float feed_forward);

private:
	IntakeAnglePID();
	static IntakeAnglePID* instance;
	
};

#endif // SRC_PID_INTAKEANGLEPID_H_
