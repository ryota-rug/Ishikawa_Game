#include "Magma.h"
#include "Stone.h"
#include "ModelManager.h"
#include "PileBankerBase.h"
#include "Player.h"
#include "CameraMiss.h"

CMagma::CMagma(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY)
{
	m_scaleCorrVal = { 1.0f, 1.0f, 1.0f };
	m_DrawPosCorrVal = { 0.0f, 0.0f, 0.0f };
	m_Slipped = true;
	m_bFlow = false;
	m_nFrame = 0;
	m_nFrameCha = 0;
	m_nLengthR = 0;
	m_nLengthL = 0;
	m_bDrawPosMoveNow = false;
	env = ENVIRONMENT_NO;	//�����Ȃ��������
	go = GO_STAY;
	ice = NO;
	m_Type = BLOCK_MAGMA;
	m_HP = 9999;
	m_DEF = 0;
	m_bOneCheck = false;
	m_bPlayerHit = false;
	m_pModelManager->c_AddModel("Magma", "Assets/New_Block/magma/blocks_yogan.fbx");
	
}

CMagma::~CMagma()
{
	Effect_Manager::GetManager()->StopEffect(m_MoveHandle);
	Effect_Manager::GetManager()->StopEffect(m_MagmaHandle);
}

void CMagma::Update()
{
	CheckRight = m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y    );
	CheckLeft  = m_pMyStage->GetBlockInfo(m_MapPos.X - 1, m_MapPos.Y    );
	CheckUnder = m_pMyStage->GetBlockInfo(m_MapPos.X    , m_MapPos.Y + 1);
	CheckOver  = m_pMyStage->GetBlockInfo(m_MapPos.X    , m_MapPos.Y - 1);

	if (env != ENVIRONMENT_TO_STONE) 	//�΂ɂȂ邱�Ƃ��m�肵�������Ȃ�
	{
		//Environment�X�V  ��DrawPos��MapPos���Ⴄ�Ȃ�(DrawPos�ړ���)�X�V���Ȃ�
		EnvironmentTrans();
		//�����Ƀu���b�N�������āA���ꂪ����
		if (CheckUnder != nullptr)
		{
			if (CheckUnder->GetType() == Block_Base::BLOCK_WATER)
			{
				env = ENVIRONMENT_TO_STONE;
			}
		}
		if (CheckOver != nullptr)
		{
			if (CheckOver->GetType() == Block_Base::BLOCK_WATER)
			{
				env = ENVIRONMENT_TO_STONE;
			}
		}
		if (CheckLeft != nullptr)
		{
			if (CheckLeft->GetType() == Block_Base::BLOCK_WATER)
			{
				env = ENVIRONMENT_TO_STONE;
			}
		}
		if (CheckRight != nullptr)
		{
			if (CheckRight->GetType() == Block_Base::BLOCK_WATER)
			{
				env = ENVIRONMENT_TO_STONE;
			}
		}

		//�����Ƀu���b�N�������āA���ꂪ�X��
		if (CheckUnder != nullptr)
		{
			if (CheckUnder->GetType() == Block_Base::BLOCK_ICE)
			{
				env = ENVIRONMENT_TO_STONE;
				ice = UNDER;
			}
		}
		if (CheckOver != nullptr)
		{
			if (CheckOver->GetType() == Block_Base::BLOCK_ICE)
			{
				env = ENVIRONMENT_TO_STONE;
				ice = OVER;
			}
		}
		if (CheckLeft != nullptr)
		{
			if (CheckLeft->GetType() == Block_Base::BLOCK_ICE)
			{
				env = ENVIRONMENT_TO_STONE;
				ice = LEFT;
			}
		}
		if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y) != nullptr)
		{
			if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_ICE)
			{
				env = ENVIRONMENT_TO_STONE;
				ice = RIGHT;
			}
		}
	}

	//Environment�ɉ�����
	switch (env)
	{
	case CMagma::ENVIRONMENT_DOWN:
		if (CheckUnder != nullptr
			&& CheckUnder->GetType() == Block_Base::BLOCK_MAGMA) break;

		if (CheckUnder != nullptr)
			if (CheckUnder->GetType() == Block_Base::BLOCK_GAS)
			{
				m_pMyStage->TakeTurn_Block(m_MapPos.X, m_MapPos.Y + 1);
				break;
			}
		m_pMyStage->MoveBlock(m_MapPos.X, m_MapPos.Y + 1);
		break;
	case CMagma::ENVIRONMENT_BOTH_SIDES:
		if (go == GO_RIGHT)
		{
			if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y) != nullptr
				&& m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA) break;

			if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y) != nullptr)
				if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS)
				{
					m_pMyStage->TakeTurn_Block(m_MapPos.X + 1, m_MapPos.Y);
					break;
				}
			m_pMyStage->MoveBlock(m_MapPos.X + 1, m_MapPos.Y);
		}
		if (go == GO_LEFT)
		{
			if (CheckLeft != nullptr)
				if (CheckLeft->GetType() == Block_Base::BLOCK_MAGMA) break;

			if (CheckLeft != nullptr)
				if (CheckLeft->GetType() == Block_Base::BLOCK_GAS)
				{
					m_pMyStage->TakeTurn_Block(m_MapPos.X - 1, m_MapPos.Y);
					break;
				}
			m_pMyStage->MoveBlock(m_MapPos.X - 1, m_MapPos.Y);
		}
		break;
	case CMagma::ENVIRONMENT_RIGHT:
		if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y) != nullptr
			&& m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA)

			if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y) != nullptr)
				if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS)
				{
					m_pMyStage->TakeTurn_Block(m_MapPos.X + 1, m_MapPos.Y);
					break;
				}
		m_pMyStage->MoveBlock(m_MapPos.X + 1, m_MapPos.Y);
		break;
	case CMagma::ENVIRONMENT_LEFT:
		if (CheckLeft != nullptr
			&& CheckLeft->GetType() == Block_Base::BLOCK_MAGMA) break;

		if (CheckLeft != nullptr)
			if (CheckLeft->GetType() == Block_Base::BLOCK_GAS)
			{
				m_pMyStage->TakeTurn_Block(m_MapPos.X - 1, m_MapPos.Y);
				break;
			}
		m_pMyStage->MoveBlock(m_MapPos.X - 1, m_MapPos.Y);
		break;
	case CMagma::ENVIRONMENT_TO_STONE:
	{
		m_nFrameCha++;

		if (m_nFrameCha >= 17)
		{
			m_DrawPos = m_pMyStage->Get_DrawPos(m_MapPos.X,m_MapPos.Y);

			CStone* pStone = new CStone(m_pMyStage, m_MapPos.X, m_MapPos.Y);
			m_pMyStage->ChangeBlock(pStone);

			switch (ice)	//�ł܂錴�����X�Ȃ炻�̕����̕X�폜
			{
			case CMagma::NO:
				break;
			case CMagma::RIGHT:
				m_pMyStage->DestroyBlock(m_MapPos.X + 1, m_MapPos.Y);
				break;
			case CMagma::LEFT:
				m_pMyStage->DestroyBlock(m_MapPos.X - 1, m_MapPos.Y);
				break;
			case CMagma::UNDER:
				m_pMyStage->DestroyBlock(m_MapPos.X, m_MapPos.Y + 1);
				break;
			case CMagma::OVER:
				m_pMyStage->DestroyBlock(m_MapPos.X, m_MapPos.Y - 1);
				break;
			default:
				break;
			}
		}
		break;
	}
	case CMagma::ENVIRONMENT_FLOW:
		m_nFrame = 0;
		m_bFlow = true;
		break;
	default:

		break;
	}

	if (go == GO_STAY)
	{	//�ǂ����0�Ȃ����K�v�͖���
		if (m_nLengthR != 0.0f || m_nLengthL != 0.0f)
		{
			AccumulatesAnime();
		}
	}
	if (m_nEffeckFrame % 60 == 0)
	{
		m_MagmaHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("Magma"),
			0.0f,0.0f,0.0f);
	}
	Effect_Manager::GetManager()->SetScale(m_MagmaHandle, 15.0f, 10.0f, 10.0f);
	Effect_Manager::GetManager()->SetRotation(m_MagmaHandle, 0.0f, 0.0f, 0.0f);
	Effect_Manager::GetManager()->SetLocation(m_MagmaHandle, m_DrawPos.X, m_DrawPos.Y + 15.0f, m_DrawPos.Z + 10.0f);
	m_nEffeckFrame++;
	//�`����W���X�V
	DrawPosMove();
}

void CMagma::Draw()
{

	float AddPosY = BlockSize * 0.5f;
	if (!m_bPlayerHit)
	{
		m_pModelManager->c_ModelDraw("Magma", m_DrawPos.X + m_DrawPosCorrVal.x, m_DrawPos.Y + m_DrawPosCorrVal.y - AddPosY, m_DrawPos.Z + m_DrawPosCorrVal.z,
			m_scale.x * m_scaleCorrVal.x, m_scale.y * m_scaleCorrVal.y, m_scale.z * m_scaleCorrVal.z, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		m_pModelManager->c_ModelDraw("Stone", m_DrawPos.X + m_DrawPosCorrVal.x, m_DrawPos.Y + m_DrawPosCorrVal.y - AddPosY, m_DrawPos.Z + m_DrawPosCorrVal.z,
			m_scale.x * m_scaleCorrVal.x, m_scale.y * m_scaleCorrVal.y, m_scale.z * m_scaleCorrVal.z, 0.0f, 0.0f, 0.0f);
	}
}

void CMagma::Update_Refuge()
{
	EnvironmentTrans();

	DrawPosMove();
}

void CMagma::EnvironmentTrans()
{
	//���t���[���߂�
	m_scaleCorrVal = { 1.0f, 1.0f, 1.0f };
	m_DrawPosCorrVal = { 0.0f, 0.0f, 0.0f };
	env = ENVIRONMENT_NO;
	go = GO_STAY;
	m_nLengthR = 0;
	m_nLengthL = 0;

	//DrawPos��MapPos���Ⴄ�Ȃ�(DrawPos�ړ���)�X�V���Ȃ�
	if ((int)m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).Y == (int)m_DrawPos.Y
		&& (int)m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).X == (int)m_DrawPos.X)
	{
		//�E���Ƀu���b�N���������K�X�����̏ꍇ
		if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y) == nullptr
			|| m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS
			|| m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER
			|| m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA)
		{
			m_bHoleR = false;
			m_nLengthR = 0;
			for (int i = 1; true; i++)
			{
				if (m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y) == nullptr
					|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS
					|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER
					|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA)
				{
					if (m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1) == nullptr
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_GAS
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_WATER
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_MAGMA)
					{
						m_bHoleR = true;
						break;
					}
				}
				else break;

				m_nLengthR++;
			}
			if (m_bHoleR)
			{
				env = ENVIRONMENT_RIGHT;
				go = GO_RIGHT;
			}
		}
		//�����Ƀu���b�N���������K�X����������ꍇ
		if (CheckLeft == nullptr
			|| CheckLeft->GetType() == Block_Base::BLOCK_GAS
			|| CheckLeft->GetType() == Block_Base::BLOCK_WATER
			|| CheckLeft->GetType() == Block_Base::BLOCK_MAGMA)
		{
			m_bHoleL = false;
			m_nLengthL = 0;
			for (int i = 1; true; i++)
			{
				if (m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y) == nullptr
					|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS
					|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER
					|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA)
				{
					if (m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1) == nullptr
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_GAS
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_WATER
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_MAGMA)
					{
						m_bHoleL = true;
						break;
					}
				}
				else break;

				m_nLengthL++;
			}
			if (m_bHoleL)
			{
				env = ENVIRONMENT_LEFT;
				go = GO_LEFT;
			}
		}
		//�����Ƀu���b�N���Ȃ��ꍇ
		if (CheckLeft == nullptr
			|| CheckLeft->GetType() == Block_Base::BLOCK_GAS
			|| CheckLeft->GetType() == Block_Base::BLOCK_WATER
			|| CheckLeft->GetType() == Block_Base::BLOCK_MAGMA)
			if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y) == nullptr
				|| m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS
				|| m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER
				|| m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA)
			{
				env = ENVIRONMENT_BOTH_SIDES;
				m_nLengthR = 0;
				m_nLengthL = 0;
				m_bHoleR = false;
				m_bHoleL = false;
				for (int i = 1; true; i++)
				{
					if (m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y) == nullptr
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA)
					{
						if (m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1) == nullptr
							|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_GAS
							|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_WATER
							|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_MAGMA)
						{
							m_bHoleR = true;
							break;
						}
					}
					else
					{
						break;
					}
					m_nLengthR++;
				}

				for (int i = 1; true; i++)
				{
					if (m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y) == nullptr
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA)
					{
						if (m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1) == nullptr
							|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_GAS
							|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_WATER
							|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_MAGMA)
						{
							m_bHoleL = true;
							break;
						}
					}
					else
					{
						break;
					}
					m_nLengthL++;
				}
				///////////////�����ŋ����𑪒�
				if (!m_bHoleR && !m_bHoleL)	//�����J���Ă��Ȃ�
				{
					go = GO_STAY;
				}
				else
				{
					//�ǂ��炩�̌����J���Ă���	
					if (m_bHoleL)
					{
						go = GO_LEFT;
					}
					if (m_bHoleR)
					{
						go = GO_RIGHT;
					}

					if (m_bHoleR && m_bHoleL)	//���������J���Ă���
					{
						if (m_nLengthR == m_nLengthL)	//���܂ł̋������ꏏ�Ȃ�
						{
							if (0) //�A�C�e�������邩
							{//����

							}
							else
							{//�Ȃ�
								if (rand() % 2)
								{
									go = GO_RIGHT;
								}
								else
								{
									go = GO_LEFT;
								}

							}
						}
					}
				}
			}

		//���Ƀu���b�N�������ꍇ
		if (CheckUnder == nullptr
			|| CheckUnder->GetType() == Block_Base::BLOCK_GAS)
		{
			m_nLengthR = 0;
			m_nLengthL = 0;
			env = ENVIRONMENT_DOWN;
		}


		//��ԉ��܂ŗ�����
		if (CheckUnder != nullptr)
			if (CheckUnder->GetType() == Block_Base::BLOCK_INVINCIBLE)
			{
				m_pMyStage->Refuge_Block();
				env = ENVIRONMENT_FLOW;
			}
	}
}

//Draw���W���ړ�
void CMagma::DrawPosMove()
{
	//�E�Ɉړ�
	if (m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).X > m_DrawPos.X)
	{
		m_DrawPos.X += Block_Base::BlockSize / m_MoveFrame;
		m_nFrame++;
		m_bDrawPosMoveNow = true;
		if (m_nEffeckFrame % 30 == 0)
		{
			m_MoveHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("MagmaMove"), 0.0f, 0.0f, 0.0f);
		}
		Effect_Manager::GetManager()->SetScale(m_MoveHandle, 15.0f, 15.0f, 15.0f);
		Effect_Manager::GetManager()->SetRotation(m_MoveHandle, 0.0f, 0.0f, 0.0f);
		Effect_Manager::GetManager()->SetLocation(m_MoveHandle, m_DrawPos.X - 20.0f, m_DrawPos.Y - 10.0f, m_DrawPos.Z);
		m_nEffeckFrame++;
	}
	
	//���Ɉړ�
	if (m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).X < m_DrawPos.X)
	{
		m_DrawPos.X -= Block_Base::BlockSize / m_MoveFrame;
		m_nFrame++;
		m_bDrawPosMoveNow = true;
		if (m_nEffeckFrame % 30 == 0)
		{
			m_MoveHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("MagmaMove"), 0.0f, 0.0f, 0.0f);
		}
		Effect_Manager::GetManager()->SetScale(m_MoveHandle, 15.0f, 15.0f, 15.0f);
		Effect_Manager::GetManager()->SetRotation(m_MoveHandle, 0.0f, 3.14f, 0.0f);
		Effect_Manager::GetManager()->SetLocation(m_MoveHandle, m_DrawPos.X + 20.0f, m_DrawPos.Y - 10.0f, m_DrawPos.Z);
		m_nEffeckFrame++;
	}

	//���Ɉړ�	
	if (m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).Y < m_DrawPos.Y)
	{
		m_DrawPos.Y -= Block_Base::BlockSize / m_MoveFrame;
		m_nFrame++;
		m_bDrawPosMoveNow = true;
	}

	//DrawPos��MapPos�̂���̉��P������
	if (m_nFrame >= m_MoveFrame)
	{
		m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).X;
		m_DrawPos.Y = m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).Y;
		m_nFrame = 0;
	}

	if (m_bFlow) FlowAnime();

}

void CMagma::AccumulatesAnime()
{
	m_scaleCorrVal.x = 1 + m_nLengthR + m_nLengthL;
	m_scaleCorrVal.y = 1.0f / (1 + m_nLengthR + m_nLengthL);
//	m_DrawPosCorrVal.y = -(Block_Base::BlockSize / 2) / (m_nLengthR + m_nLengthL);
	if (m_nLengthR == m_nLengthL) return;
	m_DrawPosCorrVal.x = (Block_Base::BlockSize / 2) * (m_nLengthR - m_nLengthL);

}

void CMagma::FlowAnime()
{
	m_DrawPos.Y -= Block_Base::BlockSize / m_MoveFrame;
	m_nFrame--;

	FloatPos PlayerPos = m_pMyStage->GetPlayer()->GetPos();
	if (m_nFrame <= -(m_MoveFrame - m_n) * 2)
	{
		if (m_pMyStage->GetPlayer()->GetLine() == m_MapPos.X)
		{
			m_bPlayerHit = true;

			FloatPos temp = m_pMyStage->GetPlayer()->GetPos();
			m_pMyStage->GetPlayer()->SetPos({ m_DrawPos.X,temp.Y,m_DrawPos.Z });
			//m_DrawPos = { m_DrawPos.X,-230.0f,m_DrawPos.Z };

			m_pMyStage->Set_GameOver(Stage_Base::GAMEOVER_TYPE::GAMEOVER_HIT_MAGMA);
			m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS
				, m_pCameraManager->Get_NowCamera()->GetPos(),
				m_pCameraManager->Get_NowCamera()->GetLook());

			CameraMiss* pMissCamera = dynamic_cast<CameraMiss*>(m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS));
			if (pMissCamera != nullptr)
				pMissCamera->Set({ PlayerPos.X, PlayerPos.Y, PlayerPos.Z });
		}
	}


	if (m_nFrame <= -m_MoveFrame * 2)
	{
		m_IsDestroy = true;
	}
}
