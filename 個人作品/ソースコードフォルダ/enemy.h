// Enemy�I�u�W�F�N�g [enemy.h]
#pragma once

#include "gameObject.h"
#include "character.h"
#include "astarnodemanager.h"


class Enemy : public Character
{
	enum State
	{
		Stopping,
		Moving,
	};
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Run();
	void SetAiTree(class BehaviorTree *ai_tree);
	bool MoveToPlayer(); // �v���C���[�֌�����
	bool RandomMove();   // �����_���œ���
	void SetBomb();
	void SearchRoute(FieldManager::Info* goal);
	bool CheckExplosion(); // ���݂̏ꏊ�������͈͓���
	void PreDraw() override;
	int GetDistanceToPlayer(); // �v���C���[�Ƃ̋���
	bool IsGoal() { return m_bGoal; }
	bool AttackJudg();
private:
	//class AnimationModel* m_Model;
	class BehaviorTree *m_AiTree;			// �r�w�C�r�A�c���[
	class BehaviorData *m_BehaviorData;		// �r�w�C�r�A�f�[�^
	class NodeBase *m_ActiveNode;			// ���s���m�[�h
	class AStarNodeManager* m_AstarMan;		// A*�}�l�[�W���[
	std::list<FieldManager::Info*> path;	// �o�H
	State m_NowState = State::Stopping;
	FieldManager::Info* TargetInfo;			// �^�[�Q�b�g�̏ꏊ���
	int m_TargetX; // ��������̔ԍ�
	int m_TargetY; // ��L�Ɠ���
	int m_MaxMoveMass = 10;		// �����_�����ő剽�}�X������
	int m_MoveMass = 0;			// �������}�X�̐�
	int m_AnimFrame = 0;
	int m_SightDistance = 7;   // ���G�͈�
	float	m_Blend = 0.0f;
	float m_downspeed = 5.0f;	// �󒆂��牺����X�s�[�h
	float m_lifetime = 0.0f;	// ��������Ă���̎���
	float m_attackstarttime = 10.0f; //�ǂ������n�߂�b�� 
	bool m_bWalkFlg = false;
	bool m_bJumpFlg = false;
	bool m_bOldWalk = false;
	bool m_bGround = false;		// �n�ʂɂ��Ă��邩
	
	bool m_bGoal = false;		// �ړI�̏ꏊ�ɒ�������

	bool IsWithinTheRange(int x, int y);	// �t�B�[���h�����ǂ���
	void SetHeading();						// �������挈��
	void SetRandomHeading();				// �����_���Ō������挈��
	bool CheckArrival();					// ���̃|�C���g�ɒ�������
};
