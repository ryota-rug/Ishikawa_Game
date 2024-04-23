#include "Water.h"
#include "ModelManager.h"
#include "PileBankerBase.h"
#include "Side_Banker.h"

CWater::CWater(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY)
{
	m_scaleCorrVal = { 1.0f, 1.0f, 1.0f };
	m_DrawPosCorrVal = { 0.0f, 0.0f, 0.0f };
	m_Slipped = true;
	m_bFlow = false;
	m_nFrame = 0;
	m_nFrameDest = 0;
	m_nLengthR = 0;
	m_nLengthL = 0;
	m_bDrawPosMoveNow = false;
	env = ENVIRONMENT_NO;	//動かない初期状態
	go = GO_STAY;
	m_Type = BLOCK_WATER;
	m_HP = 9999;
	m_DEF = 0;
	m_bOneCheck = false;
	m_pModelManager->c_AddModel("Water","Assets/New_Block/mizu/Square/blocks_mizu.fbx");	//一番上用のモデル

	m_pHitSE = new SE("Assets/SE/Liquid_Collision.wav");
	m_TurnHit = false;

	m_SorkHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("Soak"), 0.0f, 0.0f, 0.0f);
}

CWater::~CWater()
{
	delete m_pHitSE;
	Effect_Manager::GetManager()->StopEffect(m_MoveHandle);
	Effect_Manager::GetManager()->StopEffect(m_SorkHandle);

}

void CWater::Update()
{
	if ((m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y - 1) != nullptr
		&& m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y - 1)->GetType() == Block_Base::BLOCK_WATER))	//上に水があるか
	{
		//四角ブロック
		Effect_Manager::GetManager()->SetLocation(m_SorkHandle, Effekseer::Vector3D(m_DrawPos.X, m_DrawPos.Y - Block_Base::BlockSize * 0.5f, m_DrawPos.Z + Block_Base::BlockSize * 0.5f));
		Effect_Manager::GetManager()->SetScale(m_SorkHandle, 10.0f, 10.0f, 10.0f);
	}
	else
	{
		//削れブロック
		Effect_Manager::GetManager()->SetLocation(m_SorkHandle, Effekseer::Vector3D(m_DrawPos.X, m_DrawPos.Y - Block_Base::BlockSize * 0.5f, m_DrawPos.Z + Block_Base::BlockSize * 0.5f));
		Effect_Manager::GetManager()->SetScale(m_SorkHandle, 10.0f, 5.0f, 10.0f);
	}



	CheckRight = m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y    );
	CheckLeft  = m_pMyStage->GetBlockInfo(m_MapPos.X - 1, m_MapPos.Y    );
	CheckUnder = m_pMyStage->GetBlockInfo(m_MapPos.X,     m_MapPos.Y + 1);
	CheckOver  = m_pMyStage->GetBlockInfo(m_MapPos.X,     m_MapPos.Y - 1);

	//毎フレーム戻す
	m_scaleCorrVal = { 1.0f, 1.0f, 1.0f };
	m_DrawPosCorrVal = { 0.0f, 0.0f, 0.0f };
	m_nLengthR = 0;
	m_nLengthL = 0;


	if (env != ENVIRONMENT_DESTROY) 	//消えることが確定したら入らない
	{
		//Environment更新  ※DrawPosとMapPosが違うなら(DrawPos移動中)更新しない
		EnvironmentTrans();

		//そこにブロックがあって、それがマグマまたは砂か (DrawPos移動中でも更新
		if (CheckUnder != nullptr)
		{
			if (CheckUnder->GetType() == Block_Base::BLOCK_MAGMA
				|| CheckUnder->GetType() == Block_Base::BLOCK_SAND)
			{
				env = ENVIRONMENT_DESTROY;
			}
		}
		if (CheckOver != nullptr)
		{
			if (CheckOver->GetType() == Block_Base::BLOCK_MAGMA
				|| CheckOver->GetType() == Block_Base::BLOCK_SAND)
			{
				env = ENVIRONMENT_DESTROY;
			}
		}
		if (CheckLeft != nullptr)
		{
			if (CheckLeft->GetType() == Block_Base::BLOCK_MAGMA
			||  CheckLeft->GetType() == Block_Base::BLOCK_SAND)
			{
				env = ENVIRONMENT_DESTROY;
			}
		}
		if (CheckRight != nullptr)
		{
			if (CheckRight->GetType() == Block_Base::BLOCK_MAGMA
			||  CheckRight->GetType() == Block_Base::BLOCK_SAND)
			{
				env = ENVIRONMENT_DESTROY;
			}
		}
	}

	//Environmentに応じて
	switch (env)
	{
	case CWater::ENVIRONMENT_DOWN:
		if(CheckUnder != nullptr
		 && CheckUnder->GetType() == Block_Base::BLOCK_WATER) break;

		if (CheckUnder != nullptr)
			if(CheckUnder->GetType() == Block_Base::BLOCK_GAS)
			{
				m_pMyStage->TakeTurn_Block(m_MapPos.X, m_MapPos.Y + 1);
				break;
			}
		m_pMyStage->MoveBlock(m_MapPos.X, m_MapPos.Y + 1);
		
		break;
	case CWater::ENVIRONMENT_BOTH_SIDES:
		if (go == GO_RIGHT)
		{
			if (CheckRight != nullptr
				&& CheckRight->GetType() == Block_Base::BLOCK_WATER) break;

			if (CheckRight != nullptr)
				if (CheckRight->GetType() == Block_Base::BLOCK_GAS)
				{
					m_pMyStage->TakeTurn_Block(m_MapPos.X + 1, m_MapPos.Y);
					break;
				}
			m_pMyStage->MoveBlock(m_MapPos.X + 1, m_MapPos.Y);
		}
		if(go == GO_LEFT)
		{
			if (CheckLeft != nullptr)
				if (CheckLeft->GetType() == Block_Base::BLOCK_WATER) break;

			if (CheckLeft != nullptr)
				if (CheckLeft->GetType() == Block_Base::BLOCK_GAS)
					{
						m_pMyStage->TakeTurn_Block(m_MapPos.X - 1, m_MapPos.Y);
						break;
					}
			m_pMyStage->MoveBlock(m_MapPos.X - 1, m_MapPos.Y);
		}
		break;
	case CWater::ENVIRONMENT_RIGHT:
		if (CheckRight != nullptr
			&& CheckRight->GetType() == Block_Base::BLOCK_WATER) break;

		if (CheckRight != nullptr)
			if( CheckRight->GetType() == Block_Base::BLOCK_GAS)
			{
				m_pMyStage->TakeTurn_Block(m_MapPos.X + 1, m_MapPos.Y);
				break;
			}
		m_pMyStage->MoveBlock(m_MapPos.X + 1, m_MapPos.Y);
		break;
	case CWater::ENVIRONMENT_LEFT:
		if (CheckLeft != nullptr
			&& CheckLeft->GetType() == Block_Base::BLOCK_WATER) break;

		if (CheckLeft != nullptr)
			if(CheckLeft->GetType() == Block_Base::BLOCK_GAS)
			{
				m_pMyStage->TakeTurn_Block(m_MapPos.X - 1, m_MapPos.Y);
				break;
			}
		m_pMyStage->MoveBlock(m_MapPos.X - 1, m_MapPos.Y);
		break;
	case CWater::ENVIRONMENT_DESTROY:
		m_nFrameDest++;

		if (m_nFrameDest >= 17)
		{
			Effect_Manager::Play_Effect("Steam", { m_DrawPos.X,m_DrawPos.Y,m_DrawPos.Z }, { 100.0f,100.0f,100.0f },30);
			m_pMyStage->ChangeBlock(nullptr);
		}
		break;
	case CWater::ENVIRONMENT_FLOW:
		m_nFrame = 0;
		m_bFlow = true;
		m_nFrameEffect = 0;
		break;
		break;
	default:

		break;
	}
	
	if (go == GO_STAY)
	{	//どちらも0なら入る必要は無い
		if (m_nLengthR != 0.0f || m_nLengthL != 0.0f)
		{
			AccumulatesAnime();
		}
	}

	//描画座標を更新
	DrawPosMove();

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

				m_pHitSE->Play();
				
				if (side)
				{
					Side_Banker* pSideBanker = dynamic_cast<Side_Banker*>(pPile);
					
					if (pSideBanker->GetDirection() == PileBanker::RIGHT) 
					{
						//右
						Effect_Manager::Play_Effect("WaterSprash", DirectX::XMFLOAT3(m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z),
							DirectX::XMFLOAT3(10.0f, 10.0f, 10.0f),
							DirectX::XMFLOAT3(0.0f, 0.0f, -90.0f),
							100);
					}
					else
					{
						//左
						Effect_Manager::Play_Effect("WaterSprash", DirectX::XMFLOAT3(m_DrawPos.X, m_DrawPos.Y - (BlockSize * 0.5f), m_DrawPos.Z),
							DirectX::XMFLOAT3(10.0f, 10.0f, 10.0f),
							DirectX::XMFLOAT3(0.0f, 0.0f, 90.0f),
							100);
					}

				}
				else
				{
					Effect_Manager::Play_Effect("WaterSprash", DirectX::XMFLOAT3(m_DrawPos.X, m_DrawPos.Y - (BlockSize * 0.5f), m_DrawPos.Z),
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

void CWater::Draw()
{
	float AddPosY = BlockSize * 0.5f;
	if ((m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y - 1) != nullptr
	 && m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y - 1)->GetType() == Block_Base::BLOCK_WATER))	//上に水があるか
	{
		m_pModelManager->c_ModelDraw("SquareWater", m_DrawPos.X + m_DrawPosCorrVal.x, m_DrawPos.Y + m_DrawPosCorrVal.y, m_DrawPos.Z + m_DrawPosCorrVal.z,
			m_scale.x * m_scaleCorrVal.x, m_scale.y * m_scaleCorrVal.y, m_scale.z * m_scaleCorrVal.z, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		m_pModelManager->c_ModelDraw("Water", m_DrawPos.X + m_DrawPosCorrVal.x, m_DrawPos.Y + m_DrawPosCorrVal.y - AddPosY, m_DrawPos.Z + m_DrawPosCorrVal.z,
			m_scale.x * m_scaleCorrVal.x, m_scale.y * m_scaleCorrVal.y, m_scale.z * m_scaleCorrVal.z, 0.0f, 0.0f, 0.0f);
	}

}

void CWater::Update_Refuge()
{
	if (m_bFlow) FlowAnime();
}

void CWater::EnvironmentTrans()
{
	if (env == ENVIRONMENT_DESTROY) return;	//削除が確定したら入らない
	env = ENVIRONMENT_NO;
	go = GO_STAY;

	//DrawPosとMapPosが違うなら(DrawPos移動中)更新しない
	if ((int)m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).Y == (int)m_DrawPos.Y
		&& (int)m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).X == (int)m_DrawPos.X)
	{
		//右側にブロックが無いかガスかマグマの場合
		if (CheckRight == nullptr
			|| CheckRight->GetType() == Block_Base::BLOCK_GAS
			|| CheckRight->GetType() == Block_Base::BLOCK_MAGMA
			|| CheckRight->GetType() == Block_Base::BLOCK_WATER)
		{
			m_bHoleR = false;
			m_nLengthR = 0;
			for (int i = 1; true; i++)
			{
				if (m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y) == nullptr
				|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS
				|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA
				|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER)
				{
					if (m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1) == nullptr
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_GAS
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_MAGMA
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_WATER)
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
		//左側にブロックが無いかガスかマグマがある場合
		if (CheckLeft == nullptr
			|| CheckLeft->GetType() == Block_Base::BLOCK_GAS
			|| CheckLeft->GetType() == Block_Base::BLOCK_MAGMA
			|| CheckLeft->GetType() == Block_Base::BLOCK_WATER)
		{
			m_bHoleL = false;
			m_nLengthL = 0;
			for (int i = 1; true; i++)
			{
				if (m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y) == nullptr
					|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_GAS
					|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA
					|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER)
				{
					if (m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1) == nullptr
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_GAS
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_MAGMA
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_WATER)
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
		//両側にブロックがない場合
		if (CheckLeft == nullptr
			|| CheckLeft->GetType() == Block_Base::BLOCK_GAS
			|| CheckLeft->GetType() == Block_Base::BLOCK_MAGMA
		||  CheckLeft->GetType() == Block_Base::BLOCK_WATER)
		if (CheckRight == nullptr
			|| CheckRight->GetType() == Block_Base::BLOCK_GAS
			|| CheckRight->GetType() == Block_Base::BLOCK_MAGMA
		||  CheckRight->GetType() == Block_Base::BLOCK_WATER)
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
					|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA
					|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER)
				{
					if (m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1) == nullptr
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_GAS
						|| m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_MAGMA
					 || m_pMyStage->GetBlockInfo(m_MapPos.X + i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_WATER)
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
					|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA
					|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y)->GetType() == Block_Base::BLOCK_WATER)
				{
					if (m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1) == nullptr
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_MAGMA
						|| m_pMyStage->GetBlockInfo(m_MapPos.X - i, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_WATER)
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
			////////////////ここで距離を測定
			if (!m_bHoleR && !m_bHoleL)	//穴が開いていない
			{
				go = GO_STAY;
			}
			else
			{
				//どちらかの穴が開いている	
				if (m_bHoleL)
				{
					go = GO_LEFT;
				}
				if (m_bHoleR)
				{
					go = GO_RIGHT;
				}

				if (m_bHoleR && m_bHoleL)	//両方穴が開いている
				{
					if (m_nLengthR == m_nLengthL)	//穴までの距離が一緒なら
					{
						if (0) //アイテムがあるか
						{//ある
							
						}
						else
						{//ない
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
					else//穴までの距離がちがうなら
					{
						if (m_nLengthR > m_nLengthL)
						{
							go = GO_LEFT;
						}
						else
						{
							go = GO_RIGHT;
						}
					}
				}				
			}
		}

		//下にブロックが無い場合
		if (CheckUnder == nullptr
			|| CheckUnder->GetType() == Block_Base::BLOCK_GAS)
		{
			m_nLengthR = 0;
			m_nLengthL = 0;
			env = ENVIRONMENT_DOWN;
		}

		//したが水の場合
		if (CheckUnder != nullptr
			&& CheckUnder->GetType() == Block_Base::BLOCK_WATER)
		{
			env = ENVIRONMENT::ENVIRONMENT_NO;
		}

		//一番下まで来た時
		if (CheckUnder != nullptr)
			if (CheckUnder->GetType() == Block_Base::BLOCK_INVINCIBLE)
			{
				m_nLengthR = 0;
				m_nLengthL = 0;
				m_pMyStage->Refuge_Block();
				env = ENVIRONMENT_FLOW;
			}
	}
}

//Draw座標を移動
void CWater::DrawPosMove()
{
//右に移動
	if (m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).X > m_DrawPos.X)
	{
		m_DrawPos.X += Block_Base::BlockSize / m_MoveFrame;
		m_nFrame++;
		m_bDrawPosMoveNow = true;
		if (m_nFrameEffect % 30 == 0)
		{
			m_MoveHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("WaterMove"), 0.0f, 0.0f, 0.0f);
		}
		Effect_Manager::GetManager()->SetScale(m_MoveHandle, 15.0f, 15.0f, 15.0f);
		Effect_Manager::GetManager()->SetRotation(m_MoveHandle,0.0f, 0.0f, 0.0f);
		Effect_Manager::GetManager()->SetLocation(m_MoveHandle, m_DrawPos.X - 20.0f, m_DrawPos.Y - 15.0f, m_DrawPos.Z);
		m_nFrameEffect++;
	}

	//左に移動
	if (m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).X < m_DrawPos.X)
	{
		m_DrawPos.X -= Block_Base::BlockSize / m_MoveFrame;
		m_nFrame++;
		m_bDrawPosMoveNow = true;
		if (m_nFrameEffect % 30 == 0)
		{
			m_MoveHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("WaterMove"), 0.0f, 0.0f, 0.0f);
		}
		Effect_Manager::GetManager()->SetScale(m_MoveHandle, 15.0f, 15.0f, 15.0f);
		Effect_Manager::GetManager()->SetRotation(m_MoveHandle, 0.0f, 3.14f, 0.0f);
		Effect_Manager::GetManager()->SetLocation(m_MoveHandle, m_DrawPos.X + 20.0f, m_DrawPos.Y - 15.0f, m_DrawPos.Z);
		m_nFrameEffect++;
	}

	//下に移動	
	if (m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).Y < m_DrawPos.Y)
	{
		m_DrawPos.Y -= Block_Base::BlockSize / m_MoveFrame;
		m_nFrame++;
		m_bDrawPosMoveNow = true;
	}

	//DrawPosとMapPosのずれの改善を期待
	if (m_nFrame >= m_MoveFrame)
	{
		m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).X;
		m_DrawPos.Y = m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y).Y;
		m_nFrame = 0;
	}

	
}

void CWater::AccumulatesAnime()
{
	m_scaleCorrVal.x = 1 + m_nLengthR + m_nLengthL;
//	m_scaleCorrVal.y = 1.0f / (1 + m_nLengthR + m_nLengthL);
	m_DrawPosCorrVal.y = - ((Block_Base::BlockSize / 2) / (m_nLengthR + m_nLengthL)) / 2;
	if (m_nLengthR == m_nLengthL) return;
	m_DrawPosCorrVal.x = (Block_Base::BlockSize / 2) * (m_nLengthR - m_nLengthL);
}

void CWater::FlowAnime()
{
	m_nLengthR = 0;
	m_nLengthL = 0;
	m_DrawPos.Y -= Block_Base::BlockSize / m_MoveFrame;
	m_nFrame--;
	if (m_nFrame <=  -m_MoveFrame * 1.6)
	{
		m_IsDestroy = true;
	}
	//四角ブロック
	Effect_Manager::GetManager()->SetLocation(m_SorkHandle, Effekseer::Vector3D(m_DrawPos.X, m_DrawPos.Y - Block_Base::BlockSize * 0.5f, m_DrawPos.Z + Block_Base::BlockSize * 0.5f));
	Effect_Manager::GetManager()->SetScale(m_SorkHandle, 10.0f, 10.0f, 10.0f);
}