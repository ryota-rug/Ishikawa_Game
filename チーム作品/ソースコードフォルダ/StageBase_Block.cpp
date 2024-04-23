#include "StageBase.h"
#include <stdio.h>
#include "BlockBase.h"
#include "ItemBase.h"
#include <Windows.h>
#include "PileBankerBase.h"
#include "Effect_Manager.h"
#include "CameraMiss.h"

//�u���b�N
#include "Clay.h"
#include "Soil.h"
#include "Stone.h"
#include "Concrete.h"
#include "Bedrock.h"
#include "Sand.h"
#include "Ice.h"
#include "Water.h"
//#include "Magma.h"
#include "Gas.h"
#include "VirtualBlock.h"

//�������Ă���u���b�N�̍X�V
void Stage_Base::BlockUpdate()
{
	//���Ă���u���b�N�̃A�b�v�f�[�g
	for (auto it = m_RefugeBlock.begin();
		it != m_RefugeBlock.end();)
	{
		if ((*it) == nullptr)
		{
			continue;
		}

		//������̃A�b�v�f�[�g
		(*it)->Update_Refuge();

		if ((*it)->Get_Destroy())
		{
			delete (*it);
			it = m_RefugeBlock.erase(it);
		}
		else
		{
			it++;
		}
	}

	int BlockNum = m_Stage_Width.X * m_Stage_Width.Y;

	//�A�b�v�f�[�g���ĂȂ��̂Őݒ�
	for (int i = 0; i < BlockNum; i++)
	{
		if (m_mapInfo_Block[i] == nullptr)
		{
			continue;
		}

		//�܂��A�b�v�f�[�g���Ă��Ȃ����Ƃɂ���
		m_mapInfo_Block[i]->Set_DidUpdate(false);
	}

	for (int i = 0; i < BlockNum; i++)
	{
		if (m_mapInfo_Block[i] == nullptr)
		{
			continue;
		}

		//�A�b�v�f�[�g�����Ă��Ȃ�������
		if (!m_mapInfo_Block[i]->Get_DidUpdate())
		{
			Block_Base::BLOCK_TYPE NowType = m_mapInfo_Block[i]->GetType();

			//�u���b�N�̃A�b�v�f�[�g�̑O�ɂ��Ă����ׂ�������
			m_exeChangeBlock = false;
			m_exeMoveBlock = false;
			m_exeRefugeBlock = false;
			m_exeTakeTurnsBlock = false;

			m_mapInfo_Block[i]->Update();
			m_mapInfo_Block[i]->Set_DidUpdate(true);

			//������ʒu�̃u���b�N��ς���
			if (m_exeChangeBlock)
			{
				IntPos FormatMap = m_mapInfo_Block[i]->GetMap();
				FloatPos FormatPos = m_mapInfo_Block[i]->GetPos();
				delete m_mapInfo_Block[i];
				m_mapInfo_Block[i] = Temporary_Block;
				if (Temporary_Block == nullptr) continue;
				m_mapInfo_Block[i]->SetMap(FormatMap.X, FormatMap.Y);
				m_mapInfo_Block[i]->SetPos(FormatPos.X, FormatPos.Y, FormatPos.Z);
				continue;
			}

			//�u���b�N�𓮂���
			if (m_exeMoveBlock)
			{
				//�w�肵���|�W�V�����Ƀu���b�N�����邩
				if (m_mapInfo_Block[temporary_BlockPos.X + temporary_BlockPos.Y * m_Stage_Width.X] != nullptr)
				{
					MessageBox(nullptr, "�ړ��������|�W�V�����Ƀu���b�N������܂� ", "Move", MB_OK);
				}
				m_mapInfo_Block[temporary_BlockPos.X + temporary_BlockPos.Y * m_Stage_Width.X] = m_mapInfo_Block[i];
				m_mapInfo_Block[temporary_BlockPos.X + temporary_BlockPos.Y * m_Stage_Width.X]->SetMap(temporary_BlockPos.X, temporary_BlockPos.Y);
				m_mapInfo_Block[i] = nullptr;
				continue;
			}

			//�u���b�N�������
			if (m_exeRefugeBlock)
			{
				m_RefugeBlock.push_back(m_mapInfo_Block[i]);
				Block_Base *temp = m_RefugeBlock.back();
				temp->Set_ModelManager(m_pModelManager);
				temp->Set_CameraManager(m_pCameraManager);
				m_mapInfo_Block[i] = nullptr;
				continue;
			}

			//�u���b�N����シ��
			if (m_exeTakeTurnsBlock)
			{
				//���������Ă���
				Block_Base* temp = m_mapInfo_Block[i];
				//�����̏ꏊ�ɑ��������
				m_mapInfo_Block[i] = m_mapInfo_Block[temporary_BlockPos.X + temporary_BlockPos.Y * m_Stage_Width.X];
				//����̏ꏊ�Ɏ���������
				m_mapInfo_Block[temporary_BlockPos.X + temporary_BlockPos.Y * m_Stage_Width.X] = temp;

				//�V���ȏꏊ�̐ݒ�
				m_mapInfo_Block[i]->SetMap(i % m_Stage_Width.X, i / m_Stage_Width.X);
				m_mapInfo_Block[temporary_BlockPos.X + temporary_BlockPos.Y * m_Stage_Width.X]
					->SetMap(temporary_BlockPos.X, temporary_BlockPos.Y);

				continue;
			}

			//�u���b�N������
			if (m_mapInfo_Block[i]->Get_Destroy())
			{
				delete m_mapInfo_Block[i];
				m_mapInfo_Block[i] = nullptr;
				continue;
			}
		}
	}

	for (int i = 0; i < m_Stage_Width.X; i++)
	{
		//��ԏオ��ł��J���Ă�����
		if (m_mapInfo_Block[i] == nullptr)
		{
			Set_GameOver(Stage_Base::GAMEOVER_TYPE::GAMEOVER_CEILING_DESTROY);

			m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS
				, m_pCameraManager->Get_NowCamera()->GetPos(),
				m_pCameraManager->Get_NowCamera()->GetLook());

			CameraMiss* pMissCamera = dynamic_cast<CameraMiss*>(m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS));
			if (pMissCamera != nullptr)
				pMissCamera->Set({ 0.0f,300.0f,0.0f });
		}
	}
}

void Stage_Base::BlockDraw()
{
	int BlockNum = m_Stage_Width.X * m_Stage_Width.Y;

	for (auto it : m_RefugeBlock)
	{
		if (it != nullptr)
		{
			it->Draw();
		}
	}

	for (int i = 0; i < BlockNum; i++)
	{
		if (!m_mapInfo_Block[i])
		{
			continue;
		}
		m_mapInfo_Block[i]->Draw();
	}
}

//�����ɓ��ꂽ���l�̏ꏊ�ɂ���u���b�N�̏���Ԃ�
Block_Base* Stage_Base::GetBlockInfo(int X, int Y)
{
	//�͈͊O�̏ꍇ
	if (m_Stage_Width.X <= X || 0 > X ||
		m_Stage_Width.Y <= Y || 0 > Y)
	{
		if (!m_VirtualBlock)
		{
			//MessageBox(nullptr, "�͈͊O�̃u���b�N�̔��肪NULL�ł��B", "Error", MB_OK);
		}

		return m_VirtualBlock;
	}

	int Num = X + m_Stage_Width.X * Y;

	if (m_mapInfo_Block[Num] == nullptr)
	{
		//�u���b�N�̏�񂪂Ȃ�
		return nullptr;
	}
	else
	{
		return m_mapInfo_Block[X + m_Stage_Width.X * Y];
	}
}

//���������u���b�N��ۑ�����
void Stage_Base::CreateBlock(int X, int Y, Block_Base* pBlock)
{
	if (m_Stage_Width.X <= X || 0 >= X ||
		m_Stage_Width.Y <= Y || 0 >= Y)
	{
		MessageBox(nullptr, "��肽���ꏊ�̐��l���ُ�ł� ", "Error", MB_OK);
		return;
	}

	if (m_mapInfo_Block[X + m_Stage_Width.X * Y] != nullptr)
	{
		//���ꂽ���Ƃ���Ƀu���b�N��������������Ă���
		MessageBox(nullptr, "�����Ƀu���b�N�͂�������܂� ", "Error", MB_OK);
	}
	else
	{
		//�u���b�N�̃����������蓖�Ă�
		int BlockNum = X + m_Stage_Width.X * Y;
		m_mapInfo_Block[BlockNum] = pBlock;
		m_mapInfo_Block[BlockNum]->SetMap(X, Y);
		m_mapInfo_Block[BlockNum]->SetPos(m_BasePos.X + (Block_Base::BlockSize * X),
			m_BasePos.Y + (Block_Base::BlockSize * Y), m_BasePos.Z);
		m_mapInfo_Block[BlockNum]->Set_ModelManager(m_pModelManager);
		m_mapInfo_Block[BlockNum]->Set_CameraManager(m_pCameraManager);
	}
}

//�u���b�N����������
void Stage_Base::DestroyBlock(int X, int Y)
{
	if (m_Stage_Width.X <= X || 0 > X ||
		m_Stage_Width.Y <= Y || 0 > Y)
	{
		MessageBox(nullptr, "�󂵂����u���b�N�̐��l���ُ�ł� ", "Error", MB_OK);
		return;
	}


	if (m_mapInfo_Block[X + m_Stage_Width.X * Y] == nullptr)
	{
		//���������ʒu�Ƀu���b�N���Ȃ�
		MessageBox(nullptr, "�����u���b�N������܂���", "Error", MB_OK);
	}
	else
	{
		int BlockNum = X + m_Stage_Width.X * Y;
		Block_Base::BLOCK_TYPE type = m_mapInfo_Block[BlockNum]->GetType();
		DirectX::XMFLOAT3 Position = { m_mapInfo_Block[BlockNum]->GetPos().X, m_mapInfo_Block[BlockNum]->GetPos().Y, m_mapInfo_Block[BlockNum]->GetPos().Z };
		DirectX::XMFLOAT3 Size = { 150.0f,150.0f,150.0f };
		switch (type)
		{
		case Block_Base::BLOCK_CLAY:	Effect_Manager::Play_Effect("Clay", Position, Size); break;
		case Block_Base::BLOCK_SOIL:	Effect_Manager::Play_Effect("Soil", Position, Size); break;
		case Block_Base::BLOCK_STONE:	Effect_Manager::Play_Effect("Stone", Position, Size); break;
		case Block_Base::BLOCK_CONCRETE: Effect_Manager::Play_Effect("Concrete", Position, Size); break;
		case Block_Base::BLOCK_BEDROCK:  break;
		case Block_Base::BLOCK_SAND:	 break;
		case Block_Base::BLOCK_ICE:		Effect_Manager::Play_Effect("Ice", Position, Size); break;
		}
		
		//�u���b�N������
		delete m_mapInfo_Block[BlockNum];
		m_mapInfo_Block[BlockNum] = nullptr;

	}
}

void Stage_Base::MoveBlock(int X, int Y)	//�u���b�N���ړ�������
{
	m_exeMoveBlock = true;

	temporary_BlockPos.X = X;
	temporary_BlockPos.Y = Y;
}
void Stage_Base::ChangeBlock(Block_Base* NewBlock)//���Ԃ�̃|�W�V�����ɐV�����u���b�N�֒u��������
{
	m_exeChangeBlock = true;
	//�ꎞ���Ă���
	Temporary_Block = NewBlock;
	if (Temporary_Block == nullptr) return;
	Temporary_Block->Set_ModelManager(m_pModelManager);
	Temporary_Block->Set_CameraManager(m_pCameraManager);
}

//�z��O�ɔ��
void Stage_Base::Refuge_Block()
{
	m_exeRefugeBlock = true;
}

void Stage_Base::TakeTurn_Block(int X, int Y)					//�����Ƃ��̏ꏊ�ɂ���u���b�N����������
{
	m_exeTakeTurnsBlock = true;
	temporary_BlockPos.X = X;
	temporary_BlockPos.Y = Y;
}