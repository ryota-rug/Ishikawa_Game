#include <stdlib.h>
#include "attackjudgment.h"
#include "enemy.h"
#include "player.h"

bool AttackJudgment::Judgment(Enemy *enemy)
{
	// ƒvƒŒƒCƒ„[‚ªõ“G”ÍˆÍ“à‚É“ü‚Á‚½‚ç’Ç‚¢‚©‚¯‚é
	if (enemy->AttackJudg())
	{
		return true;
	}

	return false;
}
