#include "attackaction.h"
#include "Enemy.h"

ActionBase::STATE AttackAction::Run(Enemy * enemy)
{
	//マス目分は移動させたい
	if(!enemy->MoveToPlayer())
		return ActionBase::STATE::RUN;

	//if (!enemy->IsGoal())
	//{
	//	return ActionBase::STATE::RUN;
	//}

	// プレイヤーの場所に着いたらCOMPLETE
	return ActionBase::STATE::COMPLETE;
}
