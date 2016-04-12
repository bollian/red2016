#ifndef SRC_PID_SHOOTERPITCHPID_H_
#define SRC_PID_SHOOTERPITCHPID_H_

#include <ED/PIDManager.hpp>

class ShooterPitchPID : public ED::PIDManager
{
public:
	static ShooterPitchPID* getInstance();
	
protected:
	float returnPIDInput();
	void usePIDOutput(float output, float feed_forward);
	
private:
	ShooterPitchPID();
	static ShooterPitchPID* instance;
	
};

#endif // SRC_PID_SHOOTERPITCHPID_H_
