#include <stdlib.h>
#include <time.h>
#include "Heat.h"
#include "ModelManager.h"
#include "PileBankerBase.h"
#include "BlockBase.h"
#include "Player.h"
#include "Effect_Manager.h"
#include "Collision.h"

using namespace std;

#define NOTFOUND_NULLBLOCK (999)
#define NOTFOUND_WATERBLOCK (999)
#define ANGLE_Z (1.0f)
#define ANGLE_RIGHT_END (-45.0f)
#define ANGLE_LEFT_END (45.0f)

CHeat::CHeat(Stage_Base * MyStage, int PosX, int PosY)
	:CItemBase(MyStage, PosX, PosY)
	, Down_Speed(50.0f / 40.0f), Move_Speed(50.0f / 40.0f), moving_right(false), moving_left(false), bWater_InFlg(false), moving_down(false)
	, m_angleZ(-45.0f)
{
	m_pModelManager->c_AddModel("Heat", "Assets/NewItem/item_heatitem1.fbx");
	m_State = CHeat::HEATSTATE::HEAT_IN;
	m_pGet_HeetSE = new SE("Assets/SE/Get_Heet.wav");
	m_pBreak_HeetSE = new SE("Assets/SE/Item_Break.wav");
	if (m_AngleNum == 1)
	{
		m_angleZ = 45.0f;
		m_AngleNum = 0;
	}
	else
	{
		m_angleZ = -45.0f;
		m_AngleNum = 1;
	}
}

CHeat::~CHeat()
{
	delete m_pBreak_HeetSE;
	delete m_pGet_HeetSE;
}

void CHeat::Update()
{
	// �u���b�N�̒��ɂ���ꍇ
	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y);
	if (pBlock != nullptr &&
		pBlock->GetType() != Block_Base::BLOCK_TYPE::BLOCK_WATER &&
		pBlock->GetType() != Block_Base::BLOCK_TYPE::BLOCK_GAS &&
		pBlock->GetType() != Block_Base::BLOCK_TYPE::BLOCK_MAGMA)
		return;

	//���̏�������Ă���
	pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y + 1);

	//�^�����󓴂������ꍇ
	if (pBlock == nullptr || pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_MAGMA)
	{
		if (moving_left || moving_right)
			return;

		MoveDown();

	}
	else if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_INVINCIBLE)//�����O�������ꍇ
	{
		m_pMyStage->Refuge_Item();
		m_State = CHeat::HEAT_OUT;
		m_PileLineNum = m_pMyStage->Get_MapPos(m_DrawPos.X, m_DrawPos.Y).X;
	}
	else // �^�����ő̃u���b�N
	{
		MoveAngle();

		int leftDownDistance = CheckLeft(0);	//�����̋󓴂܂ł̋���
		int rightDownDistance = CheckRight(0);	//�E���̋󓴂܂ł̋���

		CheckCollisionWater();

		//�ړ��ł���ꏊ�ɐ��u���b�N�����������ꍇ
		if (bWater_InFlg)
		{
			//���ɋ󓴂�����ꍇ
			if ((leftDownDistance != NOTFOUND_NULLBLOCK || rightDownDistance != NOTFOUND_NULLBLOCK) && !(moving_down))
			{
				MoveHeat(leftDownDistance, rightDownDistance);
			}
		}
		if (!(bWater_InFlg) && moving_left && !(moving_down))
		{
			MoveHeat(leftDownDistance, rightDownDistance);
		}

		if (!(bWater_InFlg) && moving_right && !(moving_down))
		{
			MoveHeat(leftDownDistance, rightDownDistance);
		}
	}

	CheckCollisionMagma();

}

void CHeat::Draw()
{
	m_DrawPos.Z = -20.0f;
	switch (m_CoinCide)
	{
	case 1:
		m_pModelManager->c_ModelDraw("Heat", m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z
			, 0.4f, 0.4f, 0.5f, 0.0f, 0.0f, m_angleZ);
		break;
	case 2:
		m_pModelManager->c_ModelDraw("Heat", m_DrawPos.X - 5.0f, m_DrawPos.Y, m_DrawPos.Z
			, 0.3f, 0.3f, 0.4f, 0.0f, 0.0f, m_angleZ);
		m_pModelManager->c_ModelDraw("Heat", m_DrawPos.X + 5.0f, m_DrawPos.Y, m_DrawPos.Z
			, 0.3f, 0.3f, 0.4f, 0.0f, 0.0f, m_angleZ);
		break;
	case 3:
		m_pModelManager->c_ModelDraw("Heat", m_DrawPos.X - 5.0f, m_DrawPos.Y, m_DrawPos.Z
			, 0.3f, 0.3f, 0.4f, 0.0f, 0.0f, m_angleZ);
		m_pModelManager->c_ModelDraw("Heat", m_DrawPos.X + 5.0f, m_DrawPos.Y, m_DrawPos.Z
			, 0.3f, 0.3f, 0.4f, 0.0f, 0.0f, m_angleZ);
		m_pModelManager->c_ModelDraw("Heat", m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z
			, 0.3f, 0.3f, 0.4f, 0.0f, 0.0f, m_angleZ);
		break;
	default:
		break;
	}
	
}

// ======================
// �z��O�ɂ���ꍇ�̍X�V����
// ======================
void CHeat::RefugeUpdate()
{
	if (m_BreakAniFrame == 0)
	{
		m_DrawPos.Y -= Down_Speed / 2.0f;	// ����
	}
	
	C_Player* pPlayer = m_pMyStage->GetPlayer();

	//��΂��v���C���[�̈ʒu�������ɍs�����Ƃ�
	DirectX::XMFLOAT3 Position = { m_DrawPos.X,m_DrawPos.Y, m_DrawPos.Z };
	DirectX::XMFLOAT3 PlayerPos = { m_pMyStage->GetPlayer()->GetPos().X ,m_pMyStage->GetPlayer()->GetPos().Y,m_pMyStage->GetPlayer()->GetPos().Z };
	if (Collision::CheckSquare(Position, 30.0f, PlayerPos, 30.0f))
	{
		DirectX::XMFLOAT3 EffectSize = { 50.0f,50.0f,0.0f };
		Effect_Manager::Play_Effect("Heat", PlayerPos, EffectSize);
		m_pGet_HeetSE->Play();

		for (int i = 0; i < m_CoinCide; ++i)
		{
			pPlayer->AddHeetItem();
		}
		
		m_IsDestroy = true;
	}		
	else if (m_DrawPos.Y < m_pMyStage->GetPlayer()->GetPos().Y)
	{
		DirectX::XMFLOAT3 EffectSize = { 25.0f,25.0f,25.0f };
		DirectX::XMFLOAT3 EffectPos = { m_DrawPos.X,m_DrawPos.Y + 10 ,m_DrawPos.Z };
		if (m_BreakAniFrame == 0)
		{
			Effect_Manager::Play_Effect("HeatBreak", EffectPos, EffectSize);
			m_pBreak_HeetSE->Play();
			m_IsDestroy = true; // ���Ȃ��������
		}	
	}
}

// ===========================
// ���u���b�N�m�F�֐�
// ---------------------------
// ����1 : distance : ������
// ===========================
int CHeat::CheckLeft(int distance)
{
	//�}�b�v�̉��[�ɗ�����T������߂�
	if (m_MapPos.Y + 1 < 0) { return NOTFOUND_NULLBLOCK; }

	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - distance, m_MapPos.Y + 1); // �������

	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS)
	{
		return distance;
	}

	//�}�b�v�̍��[�ɗ�����T������߂�
	if (m_MapPos.X - (distance + 1) < 0) { return NOTFOUND_NULLBLOCK; }

	pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - (distance + 1), m_MapPos.Y); // ���u���b�N

	//���Ƀu���b�N��������ΒT���𑱂���
	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_WATER)
	{
		return CheckLeft(distance + 1);
	}
	else
		moving_left = false;

	//�T�����I���
	return NOTFOUND_NULLBLOCK;
}

// ===========================
// �E�u���b�N�m�F�֐�
// ---------------------------
// ����1 : distance ������
// ===========================
int CHeat::CheckRight(int distance)
{
	//�}�b�v�̉��[�ɗ�����T������߂�
	if (m_MapPos.Y + 1 < 0) { return NOTFOUND_NULLBLOCK; }

	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + distance, m_MapPos.Y + 1); // �E�����

	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS)
	{
		return distance;
	}

	//�}�b�v�̉E�[�ɗ�����T������߂�
	if (m_MapPos.X + (distance + 1) > m_pMyStage->GetStageWidthNum().X - 1) { return NOTFOUND_NULLBLOCK; }

	pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + (distance + 1), m_MapPos.Y); // �E�u���b�N

	//�E�Ƀu���b�N��������ΒT���𑱂���
	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_WATER)
	{
		return CheckRight(distance + 1);
	}
	else
		moving_right = false;

	//�T�����I���
	return NOTFOUND_NULLBLOCK;
}

// ===========================
// �����u���b�N�m�F�֐�
// ---------------------------
// ����1 : distance : ������
// ===========================
int CHeat::CheckLeftWater(int distance)
{
	//�}�b�v�̍��[�ɗ�����T������߂�
	if (m_MapPos.X - (distance + 1) < 0) { return NOTFOUND_WATERBLOCK; }

	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - (distance + 1), m_MapPos.Y + 1); // �����u���b�N���

	//�������󓴂Ȃ�T������߂�
	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
	{
		return NOTFOUND_WATERBLOCK;
	}

	//���Ƀu���b�N�������Ă��̉����󓴂���Ȃ��Ȃ�T���𑱂���
	pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - (distance + 1), m_MapPos.Y); // ���u���b�N���
	if (pBlock == nullptr)
	{
		return CheckLeftWater(distance + 1);
	}
	else if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS)
	{
		return CheckRightWater(distance + 1);
	}

	//���̃u���b�N�����Ȃ猻�ݒn�܂ł̋�����Ԃ�
	if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER) { return distance + 1; }

	//�T�����I���
	return NOTFOUND_WATERBLOCK;
}

// ===========================
// �E���u���b�N�m�F�֐�
// ---------------------------
// ����1 : distance : ������
// ===========================
int CHeat::CheckRightWater(int distance)
{
	//�}�b�v�̉E�[�ɗ�����T������߂�
	if (m_MapPos.X + (distance + 1) >= m_pMyStage->GetStageWidthNum().X - 1) { return NOTFOUND_WATERBLOCK; }

	//�E�����󓴂Ȃ�T������߂�
	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + (distance + 1), m_MapPos.Y + 1); // �E���u���b�N���
	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
	{
		return NOTFOUND_WATERBLOCK;
	}

	//�E�Ƀu���b�N�������Ă��̉����󓴂���Ȃ��Ȃ�T���𑱂���
	pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + (distance + 1), m_MapPos.Y); // �E�u���b�N���
	if (pBlock == nullptr)
	{
		return CheckRightWater(distance + 1);
	}
	else if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS)
	{
		return CheckRightWater(distance + 1);
	}

	//�E�̃u���b�N�����Ȃ猻�ݒn�܂ł̋�����Ԃ�
	if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER) { return distance + 1; }

	//�T�����I���
	return NOTFOUND_WATERBLOCK;
}

void CHeat::MoveHeat(int leftDis, int rightDis)
{
	//�������̕����߂������ꍇ
	if (leftDis < rightDis)
	{
		MoveLeft();
	}
	//�E�̋����̕����߂������܂��͓��������Ȃ�
	else if (leftDis > rightDis)
	{
		MoveRight();
	}
	//����������������
	else
	{
		FollowWater();
	}
}

// ===================
// ���֓�������
// ===================
void CHeat::MoveLeft()
{
	CItemBase* pHeat = m_pMyStage->GetHeet(m_MapPos.X - 1, m_MapPos.Y); // ���̃q�[�g�A�C�e�����

	//���Ƀq�[�g�A�C�e�����Ȃ��Ȃ�
	if (pHeat == nullptr)
	{
		//���Ɉړ�
		m_DrawPos.X -= Move_Speed;
		moving_left = true;
		//���̃u���b�N�̃|�W�V�����ɒ�������
		if (m_DrawPos.X <= m_pMyStage->Get_DrawPos(m_MapPos.X - 1, m_MapPos.Y).X)
		{
			// �`��|�W�V�����X�V
			m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X - 1, m_MapPos.Y).X;
			// �}�b�v��̃|�W�V�����X�V
			m_pMyStage->MoveHeet(m_MapPos.X - 1, m_MapPos.Y);
			moving_left = false;
		}
	}
	else
	{
		moving_left = true;
		//���Ɉړ�
		m_DrawPos.X -= Move_Speed;
		// ���̕�΂Əd�Ȃ�����
		if (pHeat->GetPos().X > m_DrawPos.X)
		{
			// �ړ���̕�΂ɐ��𑫂�
			pHeat->AddCoinCide(m_CoinCide);
			m_IsDestroy = true;
		}
	}
}

// ==================
// �E�֓�������
// ==================
void CHeat::MoveRight()
{
	CItemBase* pHeat = m_pMyStage->GetHeet(m_MapPos.X + 1, m_MapPos.Y); // �E�̃q�[�g�A�C�e�����

	//�E�Ƀq�[�g�A�C�e�����Ȃ��Ȃ�
	if (pHeat == nullptr)
	{
		//�E�Ɉړ�
		m_DrawPos.X += Move_Speed;
		moving_right = true;
		//�E�̃u���b�N�̃|�W�V�����ɒ�������
		if (m_DrawPos.X >= m_pMyStage->Get_DrawPos(m_MapPos.X + 1, m_MapPos.Y).X)
		{
			// �`��|�W�V�����X�V
			m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X + 1, m_MapPos.Y).X;
			// �}�b�v��̃|�W�V�����X�V
			m_pMyStage->MoveHeet(m_MapPos.X + 1, m_MapPos.Y);
			moving_right = false;
		}
	}
	else
	{
		moving_right = true;
		//�E�Ɉړ�
		m_DrawPos.X -= Move_Speed;
		// �E�̕�΂Əd�Ȃ�����
		if (pHeat->GetPos().X < m_DrawPos.X)
		{
			// �ړ���̕�΂ɐ��𑫂�
			pHeat->AddCoinCide(m_CoinCide);
			m_IsDestroy = true;
		}
	}
}

// ====================
// ���֓�������
// ====================
void CHeat::MoveDown()
{
	CItemBase* pHeat = m_pMyStage->GetHeet(m_MapPos.X, m_MapPos.Y + 1); //���̃q�[�g�A�C�e��

	// ���Ƀq�[�g�A�C�e�����Ȃ��Ȃ�
	if (pHeat == nullptr)
	{
		//���ɍ~���
		m_DrawPos.Y -= Down_Speed;
		moving_down = true;
		//���̃u���b�N�̃|�W�V�����ɒ�������
		if (m_DrawPos.Y <= m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y + 1).Y)
		{
			// �`��|�W�V�����X�V
			m_DrawPos.Y = m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y + 1).Y;

			m_pMyStage->MoveHeet(m_MapPos.X, m_MapPos.Y + 1);
			moving_down = false;
		}
	}
	else
	{
		moving_down = true;
		//���ɍ~���
		m_DrawPos.Y -= Down_Speed;

		if (pHeat->GetPos().Y > m_DrawPos.Y)
		{
			pHeat->AddCoinCide(m_CoinCide);
			m_IsDestroy = true;
		}
	}
}

// ========================
// ���ɂ��Ă�������
// ========================
void CHeat::FollowWater()
{
	Block_Base* pRightBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y); // �E�̃u���b�N
	Block_Base* pLeftBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - 1, m_MapPos.Y);	// ���̃u���b�N

	if (pRightBlock != nullptr)
	{
		if (pRightBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
		{
			//�E�Ɉړ�
			m_DrawPos.X += Move_Speed;
			moving_right = true;

			//�E�̃u���b�N�̃|�W�V�����ɒ�������
			if (m_DrawPos.X >= m_pMyStage->Get_DrawPos(m_MapPos.X + 1, m_MapPos.Y).X)
			{
				// �`��|�W�V�����X�V
				m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X + 1, m_MapPos.Y).X;
				// �}�b�v��̃|�W�V�����X�V
				m_pMyStage->MoveJewely(m_MapPos.X + 1, m_MapPos.Y);

				// �}�b�v��̃|�W�V�����܂Œ�������t���O������
				moving_right = false;
			}
		}
	}
	if (pLeftBlock != nullptr)
	{
		if (pLeftBlock->GetType() != Block_Base::BLOCK_TYPE::BLOCK_WATER)
			return;

		//���Ɉړ�
		m_DrawPos.X -= Move_Speed;
		moving_left = true;

		//���̃u���b�N�̃|�W�V�����ɒ�������
		if (m_DrawPos.X <= m_pMyStage->Get_DrawPos(m_MapPos.X - 1, m_MapPos.Y).X)
		{
			// �`��|�W�V�����X�V
			m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X - 1, m_MapPos.Y).X;
			// �}�b�v��̃|�W�V�����X�V
			m_pMyStage->MoveJewely(m_MapPos.X - 1, m_MapPos.Y);

			moving_left = false;
		}
	}
}

// ==========================
// ���Ƃ̓����蔻��
// ==========================
void CHeat::CheckCollisionWater()
{
	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y);
	bWater_InFlg = false;
	//���Əd�Ȃ��Ă���Ȃ�
	if (m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y) != nullptr)
	{
		if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
		{
			float size = 5.0f; // �A�C�e���̕�
			FloatPos blockpos = { pBlock->GetPos().X, pBlock->GetPos().Y }; // �u���b�N�̏ꏊ
			if ((m_DrawPos.X - size <= blockpos.X) &&
				(m_DrawPos.X + size >= blockpos.X) &&
				(m_DrawPos.Y - size < blockpos.Y) &&
				(m_DrawPos.Y + size > blockpos.Y))
			{
				bWater_InFlg = true;
				bWaterFlg = true;
			}
		}
	}

	// ���Ɉ�x�G�ꂽ��ԂŐ���������荶�ɂ���Ȃ�
	if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y) != nullptr && bWaterFlg)
	{
		if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
			bWater_InFlg = true;
	}
	// ���Ɉ�x�G�ꂽ��ԂŐ����������E�ɂ���Ȃ�
	if (m_pMyStage->GetBlockInfo(m_MapPos.X - 1, m_MapPos.Y) != nullptr && bWaterFlg)
	{
		if (m_pMyStage->GetBlockInfo(m_MapPos.X - 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
			bWater_InFlg = true;
	}
}

void CHeat::CheckCollisionMagma()
{
	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y);
	if (pBlock != nullptr)
	{
		if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_MAGMA)
		{
			float halfsize = Block_Base::BlockSize / 2; // �u���b�N�̔����T�C�Y
			FloatPos blockpos = { pBlock->GetPos().X, pBlock->GetPos().Y }; // �u���b�N�̏ꏊ
			if ((m_DrawPos.X - 5.0f < blockpos.X + halfsize) &&
				(m_DrawPos.X + 5.0f > blockpos.X - halfsize) &&
				(m_DrawPos.Y - 5.0f < blockpos.Y + halfsize) &&
				m_DrawPos.Y + 5.0f > blockpos.Y - halfsize)
			{
				Effect_Manager::Play_Effect("HeatBreak", { m_DrawPos.X,m_DrawPos.Y + 10 ,m_DrawPos.Z }, { 25.0f,25.0f,25.0f });
				m_pBreak_HeetSE->Play();
				m_IsDestroy = true;
			}
		}
	}
}

// =======================
// ���E�ɗh�炷�֐�
// =======================
void CHeat::MoveAngle()
{
	// �p�x���E���E�l�ȏ�ɂȂ�����
	if (m_angleZ <= ANGLE_RIGHT_END)
	{
		moving_angle_R = false;
		moving_angle_L = true;

	}
	// �p�x�������E�l�ȉ��ɂȂ�����
	if (m_angleZ >= ANGLE_LEFT_END)
	{
		moving_angle_L = false;
		moving_angle_R = true;
	}

	// �E�ɌX���Ă�Ȃ�
	if (moving_angle_R)
	{
		m_angleZ -= ANGLE_Z;
	}
	else
	{
		m_angleZ += ANGLE_Z;
	}

	//�X�����E�Ȃ�
	if (m_angleZ < 0)
	{
		SetAngle(CItemBase::ITEM_ANGLE::RIGHT);
	}
	// �X�������Ȃ�
	else if (m_angleZ > 0)
	{
		SetAngle(CItemBase::ITEM_ANGLE::LEFT);
	}
}
