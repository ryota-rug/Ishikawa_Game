#include "Sand.h"
#include "ModelManager.h"
#include "PileBankerBase.h"
#include "Player.h"
#include "CameraMiss.h"
#include "Effect_Manager.h"
#include "Side_Banker.h"

#include "Clay.h"

#define IF_NOT_FIRST_FRAME if(m_lateFrame < 40){m_lateFrame++;} else

using namespace std;


CSand::CSand(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY),
	m_moveSpeed(2.0f)
{
	m_Type = BLOCK_SAND;
	m_HP = 9999;
	m_DEF = 9999;

	m_Invincibility = true;
	m_Slipped = true;

	m_moving = false;

	m_touchOnWater = false;
	m_lateFrame = 0;

	m_moveDrawPos = { 0.0f, 0.0f, 0.0f };
	ADDMODEL_SENDDATA("Sand", "Assets/New_Block/suna/blocks_suna.fbx");
	ADDMODEL_SENDDATA("Clay", "Assets/New_Block/nendo/blocks_nendo.fbx");

	m_pSEFall = new SE("Assets/SE/Sand_Fall.wav");
	m_pSEToClay = new SE("Assets/SE/Sand_toClay.wav");

	m_TurnHit = false;
}

CSand::~CSand()
{
	Effect_Manager::GetManager()->StopEffect(m_HitHandle);
	delete m_pSEFall;
	delete m_pSEToClay;
}

void CSand::Update()
{
	//移動中
	if (m_moving)
	{
		m_moving = false;	//移動中なら下の処理で true になる

		if (m_moveDrawPos.Y < -1.0f){ m_moveDrawPos.Y += m_moveSpeed; m_moving = true; }
		if (m_moveDrawPos.Y >  1.0f){ m_moveDrawPos.Y -= m_moveSpeed; m_moving = true; }

		return;
	}

	if (!m_touchOnWater)
	{
		//関数定義
		auto CheckWater = [this](int posX, int posY)
		{
			if (posX >= 0 && m_pMyStage->GetStageWidthNum().X >= posX &&
				posY >= 0 && m_pMyStage->GetStageWidthNum().Y >= posY)
			{
				if (m_pMyStage->GetBlockInfo(posX, posY) == nullptr) { return false; }
				if (m_pMyStage->GetBlockInfo(posX, posY)->GetType() == Block_Base::BLOCK_WATER)
				{
					return true;
				}
			}

			return false;
		};

		//水に触れているかチェック
		m_touchOnWater = CheckWater(m_MapPos.X + 1, m_MapPos.Y) |
			CheckWater(m_MapPos.X - 1, m_MapPos.Y) |
			CheckWater(m_MapPos.X, m_MapPos.Y + 1) |
			CheckWater(m_MapPos.X, m_MapPos.Y - 1);
	}


	//水に触れていたら粘土に変化
	if (m_touchOnWater)
	{
		IF_NOT_FIRST_FRAME
		{
			CClay* pClay = new CClay(m_pMyStage, m_MapPos.X, m_MapPos.Y);
			m_pMyStage->ChangeBlock(pClay);
			m_pSEToClay->Play();
		}

	}


	//下のブロックが空いていたら下に移動
	if (m_MapPos.Y + 1 < m_pMyStage->GetStageWidthNum().Y)
	{
		if (m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y + 1) == nullptr)
		{
			m_pMyStage->MoveBlock(m_MapPos.X, m_MapPos.Y + 1);
			m_DrawPos = m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y + 1);
			m_moveDrawPos.Y = +Block_Base::BlockSize;
			m_moving = true;
			m_bEffect = true;
			m_pSEFall->Play();
		}
		else if (m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y + 1)->GetType() != Block_Base::BLOCK_TYPE::BLOCK_WATER &&
			m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y + 1)->GetType() != Block_Base::BLOCK_TYPE::BLOCK_GAS)
		{
			if (m_bEffect)
			{
				Effect_Manager::Play_Effect("SandSpread", { m_DrawPos.X,m_DrawPos.Y - 25.0f,m_DrawPos.Z - 20.0f }, { 10.0f,10.0f,10.0f });
				m_bEffect = false;
			}
			
		}
	}
	else
	{
		m_pMyStage->Refuge_Block();
		m_moving = true;
	}

	//撃ち始めてからパイルが当たっていない
	if (!m_TurnHit)
	{
		bool side = true;

		PileBanker* pPile;
		pPile = m_pMyStage->GetSideBanker();

		//サイドバンカーがない場合
		if (!pPile)
		{
			side = false;
			pPile = m_pMyStage->GetPileBanker();
		}

		//どちらかがある場合
		if (pPile)
		{
			IntPos tempPos = pPile->GetMap();
			IntPos tempDrawPos = m_pMyStage->Get_MapPos(m_DrawPos.X, m_DrawPos.Y);

			if (tempPos.X == tempDrawPos.X && tempPos.Y == tempDrawPos.Y)
			{
				m_TurnHit = true;

				if (side)
				{
					Side_Banker* pSideBanker = dynamic_cast<Side_Banker*>(pPile);

					if (pSideBanker->GetDirection() == PileBanker::RIGHT)
					{
						//右
						Effect_Manager::Play_Effect("HitSand", DirectX::XMFLOAT3(m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z),
							DirectX::XMFLOAT3(10.0f, 10.0f, 10.0f),
							100);
					}
					else
					{
						//左
						Effect_Manager::Play_Effect("HitSand", DirectX::XMFLOAT3(m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z),
							DirectX::XMFLOAT3(10.0f, 10.0f, 10.0f),
							100);
					}

				}
				else
				{
					Effect_Manager::Play_Effect("HitSand", DirectX::XMFLOAT3(m_DrawPos.X, m_DrawPos.Y - (BlockSize * 0.5f), m_DrawPos.Z),
						DirectX::XMFLOAT3(10.0f, 10.0f, 10.0f),
						100);
				}

			}
		}
	}

	//撃ち始めてパイルが一度でもあたっている
	if (m_TurnHit)
	{
		//パイルバンカーがnullになったらターンの終了
		if (!m_pMyStage->GetPileBanker())
		{
			m_TurnHit = false;
		}
	}
}

void CSand::Update_Refuge()
{
	m_DrawPos.Y -= m_moveSpeed;
	FloatPos PlayerPos = m_pMyStage->GetPlayer()->GetPos();
	if (m_DrawPos.Y < PlayerPos.Y)
	{
		if (m_bEffect)
		{
			Effect_Manager::Play_Effect("SandSpread", { m_DrawPos.X,m_DrawPos.Y + 0.0f,m_DrawPos.Z + 20 }, { 25.0f,25.0f,25.0f });
			m_bEffect = false;
		}

		if (m_pMyStage->GetPlayer()->GetLine() == m_MapPos.X)
		{
			m_pMyStage->Set_GameOver(Stage_Base::GAMEOVER_TYPE::GAMEOVER_HIT_SAND);
			m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS
				, m_pCameraManager->Get_NowCamera()->GetPos(),
				m_pCameraManager->Get_NowCamera()->GetLook());

			FloatPos temp = m_pMyStage->GetPlayer()->GetPos();
			m_pMyStage->GetPlayer()->SetPos(DirectX::XMFLOAT3(m_DrawPos.X,temp.Y,m_DrawPos.Z));

			CameraMiss* pMissCamera = dynamic_cast<CameraMiss*>(m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS));
			if (pMissCamera != nullptr)
				pMissCamera->Set({ PlayerPos.X, PlayerPos.Y, PlayerPos.Z });
		}

		// ゲームオーバーのアニメーションで砂を残したいので(描画しておいてほしいので)
		if (m_pMyStage->Get_GameOverType() != Stage_Base::GAMEOVER_HIT_SAND)
		{
			m_IsDestroy = true;
		}
	}
}

void CSand::Draw()
{
	FloatPos pos = m_DrawPos + m_moveDrawPos;
	FloatSize size = { 0.5f, 0.5f, 0.5f };
	float angle[3] = { 0.0f, 0.0f, 0.0f };

	MODELDRAW_SENDDATA("Sand", pos, size, angle);
}

void CSand::CollisionNavigate()
{

}

bool CSand::CheckWater(int posX, int posY)
{
	if (posX >= 0 && m_pMyStage->GetStageWidthNum().X >= posX &&
		posY >= 0 && m_pMyStage->GetStageWidthNum().Y >= posY)
	{
		if (m_pMyStage->GetBlockInfo(posX, posY) == nullptr) { return false; }
		if (m_pMyStage->GetBlockInfo(posX, posY)->GetType() == Block_Base::BLOCK_WATER)
		{
			return true;
		}
	}

	return false;
}
