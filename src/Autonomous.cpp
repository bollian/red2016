#include <Autonomous.hpp>

namespace Autonomous
{
	int position = 0;
	int defense = 0;
	int shoot = 0;
	
	Play play = Play::DO_NOTHING;
	int stage = 0;
	
	void moveToDefense();
	void crossDefense();
	void crossDefenseShoot();
	void spyBotShoot();
	void spyBotShootReach();
	
	void initialize(int position, int defense, int shoot)
	{
		stage = 0;
		
		Autonomous::position = position;
		Autonomous::defense = defense;
		Autonomous::shoot = shoot;
		
		if (position == 0 && defense == 0 && shoot == 0) {
			play = Play::DO_NOTHING;
		}
		else if (position != 0 && defense == 0 && shoot == 0) {
			play = Play::MOVE_TO_DEFENSE;
		}
		else if (position != 0 && defense != 0 && shoot == 0) {
			play = Play::CROSS_DEFENSE;
		}
		else if (position != 0 && defense != 0 && (shoot == 1 || shoot == 2)) {
			play = Play::CROSS_DEFENSE_SHOOT;
		}
		else if (position == 0 && defense == 0 && (shoot == 1 || shoot == 2)) {
			play = Play::SPY_BOT_SHOOT;
		}
		else if (position != 0 && defense == 0 && (shoot == 1 || shoot == 2)) {
			play = Play::SPY_BOT_SHOOT_REACH;
		}
	}
	
	void process()
	{
		switch (play) {
		case Play::MOVE_TO_DEFENSE:
			moveToDefense();
			break;
		
		case Play::CROSS_DEFENSE:
			crossDefense();
			break;
		
		case Play::CROSS_DEFENSE_SHOOT:
			crossDefenseShoot();
			break;
		
		case Play::SPY_BOT_SHOOT:
			spyBotShoot();
			break;
		
		case Play::SPY_BOT_SHOOT_REACH:
			spyBotShootReach();
			break;
		
		case Play::DO_NOTHING:
			return;
		}
	}
	
	void moveToDefense()
	{
		
	}
	
	void crossDefense()
	{
		
	}
	
	void crossDefenseShoot()
	{
		
	}
	
	void spyBotShoot()
	{
		
	}
	
	void spyBotShootReach()
	{
		
	}
}
