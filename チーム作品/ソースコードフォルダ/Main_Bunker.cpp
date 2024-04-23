#include "Main_Bunker.h"
#include "StageBase.h"
#include "BlockBase.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "ModelManager.h"
#include "CameraPile.h"
#include <stdlib.h>
#include "Effect_Manager.h"

Main_Bunker::Main_Bunker(Stage_Base* MyStage,int LineNum,FloatPos DrawPos,bool Heet)
	:PileBanker(MyStage)
	,m_Range(10)
	, m_CanCreateSide(true)
{
	m_LineNum = LineNum;
	PileState = PileBanker::PileSelect::PILE_PREPARATION;
	m_DrawPos = DrawPos;
	m_Heet = Heet;

	m_pAtkGauge = new AtkGauge;   //アタックゲージ
	m_pUtuSE = new SE("Assets/SE/Tate_Uti.wav");

}
Main_Bunker::~Main_Bunker()
{
	delete m_pUtuSE;
	delete m_pAtkGauge;
}

void Main_Bunker::Update()
{
	switch (PileState)
	{
	case PILE_PREPARATION:	//打ち込み準備

		m_MapPos.X = m_LineNum;
		m_MapPos.Y = m_pMyStage->GetStageWidthNum().Y - 1;
		m_CountSpeed = 0.0f;
		m_SideInstance = false;
		m_Attack = 0;			//ここと
		PileState = PILE_CHAGE;	//ここを変えてやることでチャージを設定
		Collision_Check_EXE = true;
		m_StopCount = 0;
		m_OldPos = m_DrawPos;
		m_TempAttack = 0.0f;
		m_AddVector = 1;
		m_PileDrawState = PileDrawTYPE::PILE_DEFAULT;
		m_pChageSE->Play();

		break;

	case PILE_CHAGE:	//チャージをする

		if (IsKeyPress(VK_RETURN) || InputPressKey(LEFT_TRIGGER) || InputPressKey(A_BUTTON))	//チャージするため一応プレスで
		{
			if (m_AnimFrame % 30 == 0)
			{
				DirectX::XMFLOAT3 PlayerPos = { m_pMyStage->GetPlayer()->GetPos().X ,m_pMyStage->GetPlayer()->GetPos().Y,m_pMyStage->GetPlayer()->GetPos().Z };
				DirectX::XMFLOAT3 Size = { 50.0f,50.0f,50.0f };
				if (m_Heet)
					Effect_Manager::Play_Effect("HeatCharge", PlayerPos, Size);
				else
					Effect_Manager::Play_Effect("NormalCharge", PlayerPos, Size);
			}
			//攻撃力を変える
			if (m_Attack > m_MaxAttack || m_Attack < 0)
			{
				m_AddVector *= -1;
			}

			//一秒で最大までのどれくらいの割合をプラスするかを計算
			//それに足す方向をかけてやる
			m_TempAttack += (((float)m_MaxAttack * 1.0f) * (1.0f / 30.0f)) * m_AddVector;

			// アタックゲージの拡大・縮小
			m_pAtkGauge->ChangeGauge(m_TempAttack);
			
			//計算した結果を小数点切り捨てで入れる
			m_Attack = (int)m_TempAttack;

			//バイブレーション
			SetPowerVibration(20000, 20000);
			MoveVibration();

			m_AnimFrame++;
		}
		else
		{	//離したとき

			CModelManager::c_SetAnimetion("Player", "Charge_First", false);

			// ゲージを固定する
			m_pAtkGauge->GaugeFix();

			PileState = PILE_IN;
			m_pUtuSE->Play();
			m_PileDrawState = PileDrawTYPE::PILE_DEFAULT;

			if (m_Attack > m_MaxAttack)
			{
				m_Attack = m_MaxAttack;
			}

			if (m_Attack < 0)
			{
				m_Attack = 0;
			}

			StopVibration();
		}
		break;

	case PILE_IN:	//打っている最中

		//真ん中からステージの半分の位置より近くなったら(ブロックを壊し始めるポジション)
		if (((Block_Base::BlockSize * m_pMyStage->GetStageWidthNum().Y) * 0.5f) >= Stage_Base::CenterPos.Y - (m_DrawPos.Y + (Block_Base::BlockSize * 0.5f)))
		{
			//ステージの中に入った
			if (Collision_Check_EXE)
			{
				//次に同じ場所に当たっても処理しない
				Collision_Check_EXE = false;
				//今いるポジションにあるブロックの情報を取ってくる
				Block_Base* CollisionBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y);
				//ブロックがあったら
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
						const float Size = 8.0f;

						Effect_Manager::Play_Effect("HitEffect",DirectX::XMFLOAT3(m_DrawPos.X,m_DrawPos.Y + 20.0f,m_DrawPos.Z),
							DirectX::XMFLOAT3(Size, Size, Size),10);

						//カメラを揺らす処理
						BiblationCameraPile();

						//ブロックの体力を先に入れておく
						int BlockHP = CollisionBlock->GetHP();
						int BlockDEF = CollisionBlock->GetDEF();
						
						//ブロックが無的かどうか
						if (!CollisionBlock->Get_Invincibility())
						{
							CollisionBlock->Damage(m_Attack);
							m_Attack -= BlockDEF;
						}

						//体力が残っていた場合
						if (CollisionBlock->GetHP() > 0)
						{
							//壊れていない
							//戻すまでの処理を入れている
							m_pStopSE->Play();
							PileState = PILE_STOP;
							m_Attack = 0.0f;
							SetPowerVibration(65535, 65535);
							SetVibration(10);
							break;
						}
						else
						{
							//壊れた
							// 破壊数増加6
							CollisionBlock->CollisionBrock();
							//ワンフレーム置いて壊す
							m_pAttackSE->Play();
							m_HitStopCount = 10;
							PileState = PILE_HITSTOP;
							SetPowerVibration(65535, 65535);
							SetVibration(10);
							break;
						}
					}
				}
			}
			//ブロック分移動するまでカウント
			m_CountSpeed += m_ShotSpeed;
			//ブロック分移動したら
			if (m_CountSpeed >= Block_Base::BlockSize)
			{
				//もし横打ちする場合
				if (m_SideInstance)
				{
					//横打ちパイルバンカーの生成をする
					m_pMyStage->CreateSideBanker();
					m_ptempBanker = dynamic_cast<Side_Banker*>(m_pMyStage->GetSideBanker());
					PileState = PILE_STOP;
				}
				else
				{
					//カウントをゼロに戻して
					m_CountSpeed -= Block_Base::BlockSize;
					m_MapPos.Y--;

					//一番上を越えたら
					if (m_MapPos.Y < 0)
					{
						//ゲームオーバー
						PileState = PILE_GAMEOVER;
						m_pMyStage->Set_GameOver();
					}
				}

				//当たったときの処理を呼べるようにする
				Collision_Check_EXE = true;
			}
		}

		m_KeyGetPil = GetPressStick();

		if (m_CanCreateSide)
		{
			//左を押したとき
			if ((IsKeyTrigger(VK_LEFT) && !m_SideInstance) || (InputTriggerKey(LEFT_BUTTON))
				|| (InputTriggerKey(LEFT_STICK) && (m_KeyGetPil.x < 0.0f)))
			{
				//パイルバンカーが生成されていない場合
				if (!m_pMyStage->GetSideBanker())
				{
					m_Side_Direction = RIGHT;
					m_SideInstance = true;

				}
			}

			//左を押したとき
			if ((IsKeyTrigger(VK_RIGHT) && !m_SideInstance) || (InputTriggerKey(RIGHT_BUTTON))
				|| (InputTriggerKey(LEFT_STICK) && (m_KeyGetPil.x > 0.0f)))
			{
				//パイルバンカーが生成されていない場合
				if (!m_pMyStage->GetSideBanker())
				{
					m_Side_Direction = LEFT;
					m_SideInstance = true;
				}
			}
		}
		//描画する場所を移動する
		m_DrawPos.Y += m_ShotSpeed;

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
		
	case PILE_STOP:	//止める

		//動かない
		m_StopCount++;

		//カウントが戻った場合
		if (m_StopCount > (int)(60.0f * 0.5f))
		{
			//パイルバンカーが作られていた場合
			if(m_pMyStage->GetSideBanker())
			{
				//パイルバンカーが元の場所に戻った
				if(m_ptempBanker->GetDestroy())
				{
					//横打ちのパイルバンカーを消す
					m_pMyStage->DestroySideBanker();
					m_CountSpeed = 0.0f;
					PileState = PILE_BACK;
				}
			}
			else
			{
				m_CountSpeed = 0.0f;
				PileState = PILE_BACK;
			}
		}

		break;

	case PILE_BACK:	//戻る

		m_DrawPos.Y -= m_PullSpeed;

		m_CountSpeed += m_PullSpeed;

		if (m_CountSpeed > Block_Base::BlockSize)
		{
			m_MapPos.Y++;
			m_CountSpeed -= Block_Base::BlockSize;
		}

		if (m_BasePosition.Y > m_DrawPos.Y)
		{
			//パイルバンカー削除
			m_Destory = true;
		}

		break;

	case PILE_GAMEOVER:
		m_DrawPos.Y += m_ShotSpeed;
		break;
	default:
		break;
	}

	// アタックゲージの拡大・縮小
	m_pAtkGauge->ChangeGauge(m_Attack);

}

void Main_Bunker::Draw()
{
	const char* MainPile_Name;
	const char* MainAddPile_Name;

	if (m_Heet)
	{
		MainPile_Name = "MAIN_PILE_NETU";
		MainAddPile_Name = "MAIN_ADD_PILE_NETU";
	}
	else
	{
		MainPile_Name = "MAIN_PILE";
		MainAddPile_Name = "MAIN_ADD_PILE";
	}

	float HokanPos = 5.0f;
			m_pModelManager->c_ModelDraw(MainPile_Name, m_DrawPos.X, m_DrawPos.Y + HokanPos, m_DrawPos.Z, 0.3f, 0.3f, 0.3f, 0.0f, 90.0f, 0.0f);

	float PileNagasa = 40.0f;
	int Count = 0;
	for (float AddDrawPos = m_BasePosition.Y;AddDrawPos < m_DrawPos.Y;AddDrawPos += PileNagasa)
	{
		m_pModelManager->c_ModelDraw(MainAddPile_Name, m_DrawPos.X, AddDrawPos + HokanPos, m_DrawPos.Z, 0.3f, 0.3f, 0.3f, 0.0f, 0.0f, 0.0f);
		Count++;
	}
}


// UI表示用
void Main_Bunker::UIDraw()
{
	// アタックゲージ描画
	EnableDepth(false);
	m_pAtkGauge->Draw();
	EnableDepth(true);
}

Main_Bunker::PileDirection Main_Bunker::m_GetSideDirection()
{
	return m_Side_Direction;
}

int* Main_Bunker::Get_pAttack()
{
	return &m_Attack;
}

void Main_Bunker::Can_TypeInSide(bool Can)
{
	m_CanCreateSide = Can;
}