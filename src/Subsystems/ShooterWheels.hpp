#ifndef SRC_SHOOTERWHEELS_H_
#define SRC_SHOOTERWHEELS_H_

namespace ShooterWheels
{
	void initialize();
	void process();

	void setSpeed(float speed);
	float getSpeed();
	
	int getPresetCount();
	float getSpeedPreset(int index);
	float getRPMPreset(int index);
}

#endif /* SRC_SHOOTERWHEELS_H_ */
