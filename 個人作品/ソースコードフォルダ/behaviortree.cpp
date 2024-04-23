#include "behaviortree.h"
#include "actionbase.h"
#include "nodebase.h"
#include "execjudgmentbase.h"
#include "Enemy.h"
#include "behaviordata.h"

void BehaviorTree::AddNode(std::string search_name, std::string entry_name, int priority, SELECT_RULE select_rule, ExecJudgmentBase *judgment, ActionBase *action)
{
	if (search_name != "")
	{
		NodeBase *search_node = m_Root->SearchNode(search_name);

		if (search_node != NULL)
		{
			NodeBase *sibling = search_node->GetLastChild();
			NodeBase *add_node = new NodeBase(entry_name, search_node, sibling, priority, select_rule, judgment, action, search_node->GetHirerchyNo() + 1);

			search_node->AddChild(add_node);
		}
	} else {
		if (m_Root == NULL)
		{
			m_Root = new NodeBase(entry_name, NULL, NULL, priority, select_rule, judgment, action, 1);
		}
	}
}

// ���_
NodeBase *BehaviorTree::Inference(Enemy *enemy, BehaviorData *data)
{
	// �f�[�^�����Z�b�g���ĊJ�n
	data->Init();
	return m_Root->Inference(enemy, data);
}

// �V�[�P���X�m�[�h����̐��_�J�n
NodeBase *BehaviorTree::SequenceBack(NodeBase *sequence_node, Enemy *enemy, BehaviorData *data)
{
	return sequence_node->Inference(enemy, data);
}

// �m�[�h���s
NodeBase *BehaviorTree::Run(Enemy *enemy, NodeBase *action_node, BehaviorData *data)
{
	// �m�[�h���s
	ActionBase::STATE state = action_node->Run(enemy);

	// ����I��
	if (state == ActionBase::STATE::COMPLETE)
	{
		// �V�[�P���X�̓r�����𔻒f
		NodeBase *sequence_node = data->PopSequenceNode();

		// �r������Ȃ��Ȃ�I��
		if (sequence_node == NULL)
		{
			return NULL;
		} else {
			// �r���Ȃ炻������n�߂�
			return SequenceBack(sequence_node, enemy, data);
		}
	// ���s�͏I��
	} else if (state == ActionBase::STATE::FAILED) {
		return NULL;
	}

	// ����ێ�
	return action_node;
}
