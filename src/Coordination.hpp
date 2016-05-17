#ifndef SRC_COORDINATION_H_
#define SRC_COORDINATION_H_

namespace Coordination
{
	enum State {
		DISABLED,
		WAITING,
		SHOOTING_BALL,
		AUTO_AIM,
		AUTO_SHOOT
	};
	
	void initialize();
	void process();
	
	void shootBall();
	void autoAim();
	void autoShoot();
	void interrupt();
	State getState();
}

#endif // SRC_COORDINATION_H_
