#ifndef SRC_SHOOTERWHEELS_H_
#define SRC_SHOOTERWHEELS_H_

namespace ShooterWheels
{
	enum State {
		DISABLED,
		WAITING,
		MANUAL_CONTROL,
		MAINTAINING_RATE
	};
	
	void initialize();
	void process();

	void setSpeed(float speed);
	void setRate(float rate);
	float getSpeed();
	bool atRate();
	
	void interrupt();
	void engageManualControl();
	State getState();
	
	int getPresetCount();
	float getSpeedPreset(int index);
	float getRPMPreset(int index);
}

#endif /* SRC_SHOOTERWHEELS_H_ */
