#include "attackaction.h"
#include "Enemy.h"

ActionBase::STATE AttackAction::Run(Enemy * enemy)
{
	//�}�X�ڕ��͈ړ���������
	if(!enemy->MoveToPlayer())
		return ActionBase::STATE::RUN;

	//if (!enemy->IsGoal())
	//{
	//	return ActionBase::STATE::RUN;
	//}

	// �v���C���[�̏ꏊ�ɒ�������COMPLETE
	return ActionBase::STATE::COMPLETE;
}
