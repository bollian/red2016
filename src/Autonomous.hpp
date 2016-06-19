#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_

namespace Autonomous
{
	enum Play {
		DO_NOTHING,
		MOVE_TO_DEFENSE,
		CROSS_DEFENSE,
		CROSS_DEFENSE_SHOOT,
		SPY_BOT_SHOOT,
		SPY_BOT_SHOOT_REACH
	};
	
	void initialize(int position, int defense, int shoot);
	void process();
}

#endif // SRC_AUTONOMOUS_H_
