#include <stdlib.h>
#include "attackjudgment.h"
#include "enemy.h"
#include "player.h"

bool AttackJudgment::Judgment(Enemy *enemy)
{
	// �v���C���[�����G�͈͓��ɓ�������ǂ�������
	if (enemy->AttackJudg())
	{
		return true;
	}

	return false;
}
