#include "randomaction.h"
#include "enemy.h"

ActionBase::STATE RandomAction::Run(Enemy * enemy)
{
	if (!(enemy->RandomMove()))
		return ActionBase::STATE::RUN;

	return ActionBase::STATE::COMPLETE;
}
