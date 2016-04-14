#ifndef SRC_PID_SHOOTERWHEELSPID_H_
#define SRC_PID_SHOOTERWHEELSPID_H_

#include <ED/PIDManager.hpp>

class ShooterWheelsPID : public ED::PIDManager
{
public:
	static ShooterWheelsPID* getInstance();
	
protected:
	float returnPIDInput();
	float getFeedForwardOutput(float new_target);
	void usePIDOutput(float output, float feed_forward);
	
private:
	ShooterWheelsPID();
	static ShooterWheelsPID* instance;
	
	static const float F_COEFFICIENT;
	
};

#endif // SRC_PID_SHOOTERWHEELSPID_H_
