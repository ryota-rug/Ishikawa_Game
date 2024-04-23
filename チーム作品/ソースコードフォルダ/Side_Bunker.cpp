#include "Side_Banker.h"
#include "StageBase.h"
#include "BlockBase.h"
#include "Input.h"
#include "ModelManager.h"
#include "CameraPile.h"
#include "Main_Bunker.h"
#include "XboxKeyboard.h"
Side_Banker::Side_Banker(Stage_Base* MyStage,PileBanker* pMyBanker)
	:PileBanker(MyStage)
	, m_pMyBanker(pMyBanker)
	,m_Range(10)
{
	PileState = PILE_PREPARATION;
	Main_Bunker* temp = dynamic_cast<Main_Bunker*>(m_pMyBanker);
	m_Direction = temp->m_GetSideDirection();
	m_Heet = m_pMyBanker->GetHeet();
	m_pMainAttack = temp->Get_pAttack();
	m_pUtuSE = new SE("Assets/SE/Yoko_Uti.wav");
	m_SideSize = 0.0f;
}
Side_Banker::~Side_Banker()
{
	delete m_pUtuSE;
}
void Side_Banker::Update()
{
	switch (PileState)
	{
	case PileBanker::PILE_PREPARATION:	//準備
	{
		m_DrawPos = m_pMyBanker->GetDraw();
		m_DrawPos.Y += 3.0f;
		m_InstancePos = m_DrawPos;
		m_MapPos = m_pMyBanker->GetMap();
		//m_Attack = m_pMyBanker->GetAttack();
		m_Heet = m_pMyBanker->GetHeet();
		//動き面---------------------------------
		m_CountSpeed = 0.0f;	//ブロックのサイズを超えたらマップを1移動している
		Collision_Check_EXE = true;
		m_StopCount = 0;
		m_pUtuSE->Play();

		switch (m_Direction)
		{
		case	RIGHT:
		{
			m_ShotSpeed *= -1.0f;
			m_PullSpeed *= -1.0f;
			m_AddMap = -1;
		}
		break;
		case	LEFT:
		{
			m_ShotSpeed *= 1.0f;
			m_PullSpeed *= 1.0f;
			m_AddMap = 1;
		}
		break;
		default:
			break;
		}
		PileState = PileBanker::PILE_IN;
	}
	break;
	case PileBanker::PILE_IN://パイルが動いている
	{
		//ブロックがあったら
		if (Collision_Check_EXE)
		{
			Collision_Check_EXE = false;
			//今いるポジションにあるブロックの情報を取ってくる
			Block_Base* CollisionBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y);
	
			if (CollisionBlock != nullptr)
			{
				CollisionBlock->CollisionNavigate();

				bool EXE = true;

				//すり抜けだったら
				if (CollisionBlock->Get_Slipped())
				{
					EXE = false;
				}

				if (EXE)
				{
					if (m_Direction == RIGHT)
					{
						const float Size = 8.0f;

						Effect_Manager::Play_Effect("HitEffect", DirectX::XMFLOAT3(m_DrawPos.X + 30.0f, m_DrawPos.Y - 10.0f, m_DrawPos.Z),
							DirectX::XMFLOAT3(Size, Size, Size),DirectX::XMFLOAT3(-90.0f, 0.0f, 90.0f), 10);
					}
					else
					{
						const float Size = 8.0f;

						Effect_Manager::Play_Effect("HitEffect", DirectX::XMFLOAT3(m_DrawPos.X - 30.0f, m_DrawPos.Y - 10.0f, m_DrawPos.Z),
							DirectX::XMFLOAT3(Size, Size, Size),DirectX::XMFLOAT3(-90.0f,0.0f , -90.0f), 10);
					}

					BiblationCameraPile();
					//ブロックの体力を先に入れておく
					int BlockHP = CollisionBlock->GetHP();
					int BlockDEF = CollisionBlock->GetDEF();

					if (!CollisionBlock->Get_Invincibility())
					{
						CollisionBlock->Damage(*m_pMainAttack);
						*m_pMainAttack -= BlockDEF;
					}

					if (CollisionBlock->GetHP() > 0)
					{
						m_pStopSE->Play();
						*m_pMainAttack = 0;
						//壊れていない
						//戻すまでの処理を入れている
						PileState = PileBanker::PILE_STOP;
						SetPowerVibration(65535, 65535);
						SetVibration(10);
						break;
					}
					else
					{
						m_pAttackSE->Play();
						//壊れた
						//ワンフレーム置いて壊す
						m_HitStopCount = 10;
						PileState = PILE_HITSTOP;
						SetPowerVibration(65535, 65535);
						SetVibration(10);
					}
				}
			}
		}

		//ブロック分移動するまでカウント
		if (m_ShotSpeed > 0)
		{
			m_CountSpeed += m_ShotSpeed;
		}
		else
		{
			m_CountSpeed -= m_ShotSpeed;
		}

		if (m_CountSpeed > 1.0f || m_CountSpeed < -1.0f)
		{
			int a = 0;
			a++;
		}

		//ブロック分移動したら
		if (m_CountSpeed >= Block_Base::BlockSize)
		{
			//カウントをゼロに戻して
			m_CountSpeed = m_CountSpeed - Block_Base::BlockSize;
			m_MapPos.X += m_AddMap;
			Collision_Check_EXE = true;
			//配列の範囲を超えたら
			if (m_MapPos.X < 0 || m_MapPos.X > m_pMyStage->GetStageWidthNum().X)
			{
				if (m_Direction == RIGHT)
				{
					const float Size = 8.0f;

					Effect_Manager::Play_Effect("HitEffect", DirectX::XMFLOAT3(m_DrawPos.X + 30.0f, m_DrawPos.Y - 10.0f, m_DrawPos.Z),
						DirectX::XMFLOAT3(Size, Size, Size), DirectX::XMFLOAT3(-90.0f, 0.0f, 90.0f), 10);
				}
				else
				{
					const float Size = 8.0f;

					Effect_Manager::Play_Effect("HitEffect", DirectX::XMFLOAT3(m_DrawPos.X - 30.0f, m_DrawPos.Y - 10.0f, m_DrawPos.Z),
						DirectX::XMFLOAT3(Size, Size, Size), DirectX::XMFLOAT3(-90.0f, 0.0f, -90.0f), 10);
				}

				BiblationCameraPile();
				m_pStopSE->Play();
				//止める
				PileState = PileBanker::PILE_STOP;
			}
		}

		//描画する場所を移動する
		m_DrawPos.X += m_ShotSpeed;
	}
	break;
	case PILE_HITSTOP:	//ヒットストップ
	{
		m_HitStopCount--;

		if (m_HitStopCount < 0)
		{
			m_pMyStage->DestroyBlock(m_MapPos.X, m_MapPos.Y);
			PileState = PILE_IN;
		}
	}
	break;
	case PileBanker::PILE_STOP:	//パイルが止まった
	{
		//動かない
		m_StopCount++;

		if (m_StopCount > (int)(60.0f * 0.5f))
		{
			PileState = PileBanker::PILE_BACK;
			m_CountSpeed = 0.0f;
		}
	}
	break;
	case PileBanker::PILE_BACK://パイルが戻る
	{
		FloatPos BasePos = m_InstancePos;
		m_DrawPos.X -= m_PullSpeed;
		m_CountSpeed += m_PullSpeed;

		if (m_CountSpeed > Block_Base::BlockSize)
		{
			//右行き
			m_MapPos.X++;
			m_CountSpeed = m_CountSpeed - Block_Base::BlockSize;
		}
		else if(m_CountSpeed < -Block_Base::BlockSize)
		{
			//左行き
			m_MapPos.X--;
			m_CountSpeed = m_CountSpeed + Block_Base::BlockSize;
		}

		switch (m_Direction)
		{
		case RIGHT:
			if (BasePos.X < m_DrawPos.X)
			{
				PileState = PileBanker::PILE_DESTROY;
			}
			break;
		case LEFT:
			if (BasePos.X > m_DrawPos.X)
			{
				PileState = PileBanker::PILE_DESTROY;
			}
			break;
		default:
			break;
		}
	}
	break;

	case PileBanker::PILE_DESTROY:
		m_Destory = true;
		break;

	case PileBanker::PILE_GAMEOVER:	//ゲームオーバー

		break;
	}

}
void Side_Banker::Draw()
{
	float Angle;
	float PileNagasa;
	float Add_Scale = 0.502f / 3.0f;	//1でこの量大きくしてやればいい

	int Count = 0;
	switch (m_Direction)
	{
	case RIGHT:
		Angle = -90.0f;
		break;
	case LEFT:
		Angle = 90.0f;
		Add_Scale *= -1.0f;
		break;
	default:
		break;
	}

	switch (PileState)
	{
	case PileBanker::PILE_IN:
	{
		float nowSpeed = m_ShotSpeed < 0.0f ? m_ShotSpeed * -1.0f : m_ShotSpeed;
		Add_Scale = Add_Scale * nowSpeed;
		m_SideSize += Add_Scale;
	}
		break;
	case PileBanker::PILE_BACK:
	{
		float tempsize = m_SideSize;
		float nowSpeed = m_PullSpeed < 0.0f ? m_PullSpeed * -1.0f : m_PullSpeed;
		Add_Scale = Add_Scale * nowSpeed;
		Add_Scale *= 0.98f;
		m_SideSize -= Add_Scale;
		if((tempsize < 0.0f && m_SideSize > 0.0f) || (tempsize > 0.0f && m_SideSize < 0.0f))
		{
			m_SideSize = 0.0f;
		}
	}
		break;
	default:
		break;
	}

	const char* SidePile_Name;
	const char* SideAddPile_Name;

	if (m_Heet)
	{
		SidePile_Name = "SIDE_PILE_NETU";
		SideAddPile_Name = "SIDE_ADD_PILE_NETU";
	}
	else
	{
		SidePile_Name = "SIDE_PILE";
		SideAddPile_Name = "SIDE_ADD_PILE";

	}

	m_pModelManager->c_ModelDraw(SidePile_Name, m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z, 0.3f, 0.3f, 0.3f, 0.0f, Angle, 0.0f);
	m_pModelManager->c_ModelDraw(SideAddPile_Name, m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z, 0.3f, 0.3f, m_SideSize, 0.0f, 90.0f, 00.0f);
}
