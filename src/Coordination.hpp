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
	
	/**
	 * Speeds up the shooter wheels to the provided speed
	 * and then pushes the ball into the shooter.
	 */
	void shootBall(float speed);

	/**
	 * Uses the front camera to aim the robot at the goal.
	 * Simultaneously turns left and right with mobility and lifts
	 * the shooter up and down.
	 */
	void autoAim();

	/**
	 * Combines autoAim() and shootBall().  First aims the robot,
	 * then shoots the ball.
	 */
	void autoShoot();
	void interrupt();
	State getState();
}

#endif // SRC_COORDINATION_H_
