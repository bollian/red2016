#ifndef SRC_HOLDERWHEELS_H_
#define SRC_HOLDERWHEELS_H_

#include <Utils.hpp>

namespace HolderWheels
{
	void initialize();
	void process();
	
	enum State {
		DISABLED,
		WAITING,
		MANUAL_CONTROL,
		SHOOTING_BALL
	};
	
	void engageManualControl();

	/**
	 * Pushes the ball forward into the shooter wheels for a small period of time.
	 * If the shooter wheels are on, this results in the ball being shot.
	 */
	void shootBall();
	void interrupt();
	State getState();

	void setDirection(Utils::HorizontalDirection dir);
	Utils::HorizontalDirection getDirection();
}

#endif /* SRC_HOLDERWHEELS_H_ */
