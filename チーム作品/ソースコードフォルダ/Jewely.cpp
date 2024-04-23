//#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include "Jewely.h"
#include "ModelManager.h"
#include "BlockBase.h"
#include "PileBankerBase.h"
#include "Player.h"
#include "Effect_Manager.h"
#include "Collision.h"
#include "CameraMiss.h"

using namespace std;


#define NOTFOUND_NULLBLOCK (999)
#define NOTFOUND_WATERBLOCK (999)
#define ANGLE_Z (1.0f)
#define ANGLE_RIGHT_END (-45.0f)
#define ANGLE_LEFT_END (45.0f)


CJewely::CJewely(Stage_Base * MyStage, int PosX, int PosY)
	:CItemBase(MyStage, PosX, PosY)
	, m_DownSpeed(50.0f / 40.0f), m_MoveSpeed(50.0f / 40.0f), bMovingRight(false), bMovingLeft(false), bWater_InFlg(false), bMovingDown(false)
	, m_angleZ(-45.0f), bMovingAngleR(false), bMovingAngleL(false)
{
	m_pModelManager->c_AddModel("Jewely", "Assets/NewItem/item_houseki1.fbx");
	m_State = CJewely::JEWELYSTATE::JEWELY_IN;

	m_pGet_JewelySE = new SE("Assets/SE/Get_Jewely.wav");
	m_pBreak_JewelySE = new SE("Assets/SE/Item_Break.wav");

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
	m_efkManager = Effect_Manager::GetManager();
	m_JewelyHandle = m_efkManager->Play(Effect_Manager::GetEffect("Kirakira"), 0, 0, 0);
	std::srand(time(NULL));
}

CJewely::~CJewely()
{
	m_efkManager->StopEffect(m_JewelyHandle);
	delete m_pBreak_JewelySE;
	delete m_pGet_JewelySE;
}

void CJewely::Update()
{	

		if(m_AniFrame == 0)
			m_nRand = rand() % 60 + 60;
		
		DirectX::XMFLOAT3 Pos = { m_DrawPos.X,m_DrawPos.Y,m_DrawPos.Z - 20};
		DirectX::XMFLOAT3 Size = { 10.0f,10.0f,10.0f };
		
		// エフェクト表示
		if (m_AniFrame == m_nRand)
		{
			m_efkManager->SetLocation(m_JewelyHandle, Pos.x, Pos.y, Pos.z);
			Effect_Manager::Play_Effect("Kirakira", Pos, Size);
			m_AniFrame = 0;
		}

		// ブロックの中にある場合
		Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y);
		if (pBlock != nullptr &&
			pBlock->GetType() != Block_Base::BLOCK_TYPE::BLOCK_WATER &&
			pBlock->GetType() != Block_Base::BLOCK_TYPE::BLOCK_GAS &&
			pBlock->GetType() != Block_Base::BLOCK_TYPE::BLOCK_MAGMA)
		{
			m_AniFrame++;
			return;
		}

		//下のブロックの情報を取ってくる
		pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y + 1);

		//真下が空洞だった場合
		if (pBlock == nullptr || pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER ||
			pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
			pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_MAGMA)
		{
			if (bMovingLeft || bMovingRight)
			{
				m_AniFrame++;
				return;
			}

			MoveDown();
		}
		else if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_INVINCIBLE)//下が外だった場合
		{
			//ステージ外に出た場合
			m_pMyStage->Refuge_Item();
			m_State = CJewely::JEWELY_OUT;
			m_PileLineNum = m_pMyStage->Get_MapPos(m_DrawPos.X, m_DrawPos.Y).X;
		}
		else // 真下が固体ブロック
		{
			// 揺らす
			MoveAngle();

			int leftDownDistance = CheckLeft(0);		//左下の空洞までの距離
			int rightDownDistance = CheckRight(0);	    //右下の空洞までの距離

			CheckCollisionWater();

			//同じ場所に水があるなら
			if (bWater_InFlg)
			{
				//下に空洞がある場合
				if ((leftDownDistance != NOTFOUND_NULLBLOCK || rightDownDistance != NOTFOUND_NULLBLOCK) && !(bMovingDown))
				{
					MoveJewely(leftDownDistance, rightDownDistance);
				}
			}// 水が先に動くので水の場所まで移動
			else if (!(bWater_InFlg) && bMovingLeft && !(bMovingDown))
			{
				MoveJewely(leftDownDistance, rightDownDistance);
			}
			else if (!(bWater_InFlg) && bMovingRight && !(bMovingDown))
			{
				MoveJewely(leftDownDistance, rightDownDistance);
			}

			// マグマの中に入ったらゲームオーバー
			CheckCollisionMagma();
		}
		m_AniFrame++;
}

void CJewely::Draw()
{
	// 少しこちら側に突き出させる
	m_DrawPos.Z = -5.0f;
	
	switch (m_CoinCide)
	{
	case 1:
		m_pModelManager->c_ModelDraw("Jewely", m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z
			, m_size.x, m_size.y, m_size.z, 0.0f, 180.0f, m_angleZ);
		break;
	case 2:
		m_pModelManager->c_ModelDraw("Jewely", m_DrawPos.X - m_width, m_DrawPos.Y, m_DrawPos.Z
			, m_size.x, m_size.y, m_size.z, 0.0f, 180.0f, m_angleZ);

		m_pModelManager->c_ModelDraw("Jewely", m_DrawPos.X + m_width, m_DrawPos.Y, m_DrawPos.Z
			, m_size.x, m_size.y, m_size.z, 0.0f, 180.0f, m_angleZ);
		break;
	case 3:
		m_pModelManager->c_ModelDraw("Jewely", m_DrawPos.X - m_width, m_DrawPos.Y, m_DrawPos.Z
			, m_size.x, m_size.y, m_size.z, 0.0f, 180.0f, m_angleZ);

		m_pModelManager->c_ModelDraw("Jewely", m_DrawPos.X + m_width, m_DrawPos.Y, m_DrawPos.Z
			, m_size.x, m_size.y, m_size.z, 0.0f, 180.0f, m_angleZ);

		m_pModelManager->c_ModelDraw("Jewely", m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z
			, m_size.x, m_size.y, m_size.z, 0.0f, 180.0f, m_angleZ);
		break;
	default:
		break;
	}
}


// ======================
// 配列外にある場合の更新処理
// ======================
void CJewely::RefugeUpdate()
{
	if (m_BreakAniFrame == 0)
	{
		m_DrawPos.Y -= m_DownSpeed / 2.0f;	// 下へ

	//宝石がプレイヤーの位置よりも下に行ったとき
		DirectX::XMFLOAT3 Position = { m_DrawPos.X,m_DrawPos.Y, m_DrawPos.Z };
		DirectX::XMFLOAT3 PlayerPos = { m_pMyStage->GetPlayer()->GetPos().X ,m_pMyStage->GetPlayer()->GetPos().Y,m_pMyStage->GetPlayer()->GetPos().Z };
		float length = 30.0f;
		if (Collision::CheckSquare(Position, length, PlayerPos, length))
		{
			DirectX::XMFLOAT3 Size = { 50.0f,50.0f,0.0f };
			Effect_Manager::Play_Effect("Item", PlayerPos, Size);
			m_pGet_JewelySE->Play();

			for (int i = 0 ; i < m_CoinCide ; ++i)
			{
				m_pMyStage->Mina_Jewely();
			}
			
			m_IsDestroy = true;
		}
	}
	if (m_DrawPos.Y < m_pMyStage->GetPlayer()->GetPos().Y)
	{
		// 一度だけ入る
		if (m_BreakAniFrame == 0)
		{
			DirectX::XMFLOAT3 Size = { 25.0f,25.0f,25.0f };
			Effect_Manager::Play_Effect("JewelyBreak", { m_DrawPos.X,m_DrawPos.Y + 5 ,m_DrawPos.Z }, Size);
			m_pBreak_JewelySE->Play();
			m_IsDestroy = true;
		}
		m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS
			, m_pCameraManager->Get_NowCamera()->GetPos(),
			m_pCameraManager->Get_NowCamera()->GetLook());

		CameraMiss* pMissCamera = dynamic_cast<CameraMiss*>(m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS));
		if (pMissCamera != nullptr)
			pMissCamera->Set({ m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z });

		m_pMyStage->Set_GameOver(Stage_Base::GAMEOVER_TYPE::GAMEOVER_JEWELY_DOROP);
		m_BreakAniFrame++;
		
		
	}
}

// ===========================
// 左下空洞確認関数
// ---------------------------
// 引数1 : distance : 距離数
// ===========================
int CJewely::CheckLeft(int distance)
{

	//マップの下端に来たら探索をやめる
	if (m_MapPos.Y + 1 < 0) { return NOTFOUND_NULLBLOCK; }

	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - distance, m_MapPos.Y + 1); // 左下情報

	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_WATER)
	{
		return distance;
	}

	//マップの左端に来たら探索をやめる
	if (m_MapPos.X - (distance + 1) < 0) { return NOTFOUND_NULLBLOCK; }

	pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - (distance + 1), m_MapPos.Y); // 左ブロック

	//左にブロックが無ければ探索を続ける
	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_WATER)
	{
		return CheckLeft(distance + 1);
	}
	else
		bMovingLeft = false;
		

	//探索を終わる
	return NOTFOUND_NULLBLOCK;
}

// ===========================
// 右下空洞確認関数
// ---------------------------
// 引数1 : distance 距離数
// ===========================
int CJewely::CheckRight(int distance)
{
	//マップの下端に来たら探索をやめる
	if (m_MapPos.Y + 1 < 0) { return NOTFOUND_NULLBLOCK; }

	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + distance, m_MapPos.Y + 1); // 右下の情報

	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_WATER)
	{
		return distance;
	}

	//マップの右端に来たら探索をやめる
	if (m_MapPos.X + (distance + 1) > m_pMyStage->GetStageWidthNum().X - 1) { return NOTFOUND_NULLBLOCK; }

	pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + (distance + 1), m_MapPos.Y); // 右ブロック

	//右にブロックが無ければ探索を続ける
	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_WATER)
	{
		return CheckRight(distance + 1);
	}
	else
		bMovingRight = false;

	//探索を終わる
	return NOTFOUND_NULLBLOCK;
}

// ===========================
// 左水ブロック確認関数
// ---------------------------
// 引数1 : distance : 距離数
// ===========================
int CJewely::CheckLeftWater(int distance)
{
	//マップの左端に来たら探索をやめる
	if (m_MapPos.X - (distance + 1) < 0) { return NOTFOUND_WATERBLOCK; }

	//左下が空洞なら探索をやめる
	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - (distance + 1), m_MapPos.Y + 1); // 左下ブロック情報
	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
	{
		return NOTFOUND_WATERBLOCK;
	}

	//左にブロックが無くてその下が空洞じゃないなら探索を続ける
	pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - (distance + 1), m_MapPos.Y); // 左ブロック情報
	if (pBlock == nullptr)
	{
		return CheckLeftWater(distance + 1);
	}
	else if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS)
	{
		return CheckRightWater(distance + 1);
	}

	//左のブロックが水なら現在地までの距離を返す
	if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER) { return distance + 1; }

	//探索を終わる
	return NOTFOUND_WATERBLOCK;
}

// ===========================
// 右水ブロック確認関数
// ---------------------------
// 引数1 : distance : 距離数
// ===========================
int CJewely::CheckRightWater(int distance)
{
	//マップの右端に来たら探索をやめる
	if (m_MapPos.X + (distance + 1) >= m_pMyStage->GetStageWidthNum().X - 1) { return NOTFOUND_WATERBLOCK; }

	//右下が空洞なら探索をやめる
	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + (distance + 1), m_MapPos.Y + 1); // 右下ブロック情報
	if (pBlock == nullptr ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS ||
		pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
	{
		return NOTFOUND_WATERBLOCK;
	}

	//右にブロックが無くてその下が空洞じゃないなら探索を続ける
	pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + (distance + 1), m_MapPos.Y); // 右ブロック情報
	if (pBlock == nullptr)
	{
		return CheckRightWater(distance + 1);
	}
	else if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_GAS)
	{
		return CheckRightWater(distance + 1);
	}

	//右のブロックが水なら現在地までの距離を返す
	if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
		return distance + 1;

	//探索を終わる
	return NOTFOUND_WATERBLOCK;
}

// ==========================
// 水との当たり判定
// ==========================
void CJewely::CheckCollisionWater()
{
	bWater_InFlg = false;
	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y);
	//水と重なっているなら
	if (pBlock != nullptr)
	{
		if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
		{
			float size = 5.0f; // アイテムの幅
			FloatPos blockpos = { pBlock->GetPos().X, pBlock->GetPos().Y}; // ブロックの場所
			if ((m_DrawPos.X - size < blockpos.X) &&
				(m_DrawPos.X + size > blockpos.X) &&
				(m_DrawPos.Y - size < blockpos.Y) &&
				m_DrawPos.Y + size > blockpos.Y)
			{
				bWater_InFlg = true;
				bWaterFlg = true;
			}	
		}
	}
}

// =========================
// マグマとの当たり判定
// =========================
void CJewely::CheckCollisionMagma()
{
	Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y);
	if (pBlock != nullptr)
	{
		if (pBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_MAGMA)
		{
			float halfsize = Block_Base::BlockSize / 2; // ブロックの半分サイズ
			FloatPos blockpos = { pBlock->GetPos().X, pBlock->GetPos().Y }; // ブロックの場所
			if ((m_DrawPos.X - 10.0f < blockpos.X + halfsize) &&
				(m_DrawPos.X + 10.0f > blockpos.X - halfsize) &&
				(m_DrawPos.Y - 10.0f < blockpos.Y + halfsize) &&
				m_DrawPos.Y + 10.0f > blockpos.Y - halfsize)
			{
				// 一度だけ入る
				if (m_BreakAniFrame == 0)
				{
					DirectX::XMFLOAT3 effectsize = { 25.0f,25.0f,25.0f };
					Effect_Manager::Play_Effect("JewelyBreak", { m_DrawPos.X,m_DrawPos.Y + 5 ,m_DrawPos.Z }, effectsize);
					m_pBreak_JewelySE->Play();
					m_IsDestroy = true;
				}

				// カメラをゲームオーバー用に切り替える
				m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS
					, m_pCameraManager->Get_NowCamera()->GetPos(),
					m_pCameraManager->Get_NowCamera()->GetLook());

				CameraMiss* pMissCamera = dynamic_cast<CameraMiss*>(m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS));
				if (pMissCamera != nullptr)
					pMissCamera->Set({m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z});

				// ゲームオーバーセット
				m_pMyStage->Set_GameOver(Stage_Base::GAMEOVER_TYPE::GAMEOVER_JEWELY_MELT);
				m_BreakAniFrame++;
			}
		}
	}
}


// =========================
// 動き関数
// -------------------------
// 引数1 : leftDis : 左との距離
// 引数2 : rightDis : 右との距離
// =========================
void CJewely::MoveJewely(int leftDis, int rightDis)
{
	//左距離の方が近かった場合
	if (leftDis < rightDis)
	{
		MoveLeft();
	}
	//右の距離の方が近かった場合
	else if (leftDis > rightDis)
	{
		MoveRight();
	}
	//同じ距離だったら水の動きに合わせる
	else
	{
		FollowWater();
	}
}

// ===================
// 左へ動く処理
// ===================
void CJewely::MoveLeft()
{
	CItemBase* pJewely = m_pMyStage->GetJewely(m_MapPos.X - 1, m_MapPos.Y); // 左の宝石情報
	// 左に宝石がないなら
	if (pJewely == nullptr)
	{
		//左に移動
		m_DrawPos.X -= m_MoveSpeed;
		bMovingLeft = true;

		//左のブロックのポジションに着いたら
		if (m_DrawPos.X <= m_pMyStage->Get_DrawPos(m_MapPos.X - 1, m_MapPos.Y).X)
		{
			// 描画ポジション更新
			m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X - 1, m_MapPos.Y).X;
			// マップ上のポジション更新
			m_pMyStage->MoveJewely(m_MapPos.X - 1, m_MapPos.Y);
			bMovingLeft = false;
		}
	}
	else
	{
		bMovingLeft = true;
		//左に移動
		m_DrawPos.X -= m_MoveSpeed;
		// 左の宝石と重なったら重なった分表示させる
		if (pJewely->GetPos().X > m_DrawPos.X)
		{
			// 移動先の宝石に数を足す
			pJewely->AddCoinCide(m_CoinCide);
			m_IsDestroy = true;
		}
	}
}

// ==================
// 右へ動く処理
// ==================
void CJewely::MoveRight()
{
	CItemBase* pJewely = m_pMyStage->GetJewely(m_MapPos.X + 1, m_MapPos.Y); // 右のアイテム情報
		//右に宝石がないなら
	if (pJewely == nullptr)
	{
		//右に移動
		m_DrawPos.X += m_MoveSpeed;
		bMovingRight = true;

		//右のブロックのポジションに着いたら
		if (m_DrawPos.X >= m_pMyStage->Get_DrawPos(m_MapPos.X + 1, m_MapPos.Y).X)
		{
			// 描画ポジション更新
			m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X + 1, m_MapPos.Y).X;
			// マップ上のポジション更新
			m_pMyStage->MoveJewely(m_MapPos.X + 1, m_MapPos.Y);

			// マップ上のポジションまで着いたらフラグを下す
			bMovingRight = false;
		}
	}
	else
	{
		bMovingRight = true;
		//右に移動
		m_DrawPos.X -= m_MoveSpeed;

		// 右の宝石と重なったら
		if (pJewely->GetPos().X < m_DrawPos.X)
		{
			// 移動先の宝石に数を足す
			pJewely->AddCoinCide(m_CoinCide);
			m_IsDestroy = true;
		}
	}
}

// ====================
// 下へ動く処理
// ====================
void CJewely::MoveDown()
{
	CItemBase* pJewely = m_pMyStage->GetJewely(m_MapPos.X, m_MapPos.Y + 1);
	// 下に宝石がないなら
	if (pJewely == nullptr)
	{
		//下に降りる
		m_DrawPos.Y -= m_DownSpeed;
		bMovingDown = true;
		//下のブロックのポジションに着いたら
		if (m_DrawPos.Y <= m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y + 1).Y)
		{
			// 描画ポジション更新
			m_DrawPos.Y = m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y + 1).Y;

			m_pMyStage->MoveJewely(m_MapPos.X, m_MapPos.Y + 1);
			bMovingDown = false;
		}
	}
	else
	{
		bMovingDown = true;
		//下に降りる
		m_DrawPos.Y -= m_DownSpeed;
		// 下の宝石と重なったら
		if (pJewely->GetPos().Y > m_DrawPos.Y)
		{
			// 移動先の宝石に数を足す
			pJewely->AddCoinCide(m_CoinCide);
			m_IsDestroy = true;
		}
	}
}

// ========================
// 水についていく処理
// ========================
void CJewely::FollowWater()
{
	Block_Base* pRightBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y); // 右のブロック
	Block_Base* pLeftBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - 1, m_MapPos.Y);	// 左のブロック

	if (pRightBlock != nullptr)
	{
		if (pRightBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
		{
			//右に移動
			m_DrawPos.X += m_MoveSpeed;
			bMovingRight = true;

			//右のブロックのポジションに着いたら
			if (m_DrawPos.X >= m_pMyStage->Get_DrawPos(m_MapPos.X + 1, m_MapPos.Y).X)
			{
				// 描画ポジション更新
				m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X + 1, m_MapPos.Y).X;
				// マップ上のポジション更新
				m_pMyStage->MoveJewely(m_MapPos.X + 1, m_MapPos.Y);

				// マップ上のポジションまで着いたらフラグを下す
				bMovingRight = false;
			}
		}
	}
	else if (pLeftBlock != nullptr)
	{
		if (pLeftBlock->GetType() == Block_Base::BLOCK_TYPE::BLOCK_WATER)
		{
			//左に移動
			m_DrawPos.X -= m_MoveSpeed;
			bMovingLeft = true;

			//左のブロックのポジションに着いたら
			if (m_DrawPos.X <= m_pMyStage->Get_DrawPos(m_MapPos.X - 1, m_MapPos.Y).X)
			{
				// 描画ポジション更新
				m_DrawPos.X = m_pMyStage->Get_DrawPos(m_MapPos.X - 1, m_MapPos.Y).X;
				// マップ上のポジション更新
				m_pMyStage->MoveJewely(m_MapPos.X - 1, m_MapPos.Y);

				bMovingLeft = false;
			}
		}
	}
}

// =======================
// 左右に揺らす関数
// =======================
void CJewely::MoveAngle()
{
	// 角度が右限界値以上になったら
	if (m_angleZ <= ANGLE_RIGHT_END)
	{
		bMovingAngleR = false;
		bMovingAngleL = true;

	}
	// 角度が左限界値以下になったら
	else if (m_angleZ >= ANGLE_LEFT_END)
	{
		bMovingAngleL = false;
		bMovingAngleR = true;
	}

	// 右に傾いてるなら
	if (bMovingAngleR)
		m_angleZ -= ANGLE_Z;
	else
		m_angleZ += ANGLE_Z;

	//傾きが右なら
	if (m_angleZ < 0.0f)
		SetAngle(CItemBase::ITEM_ANGLE::RIGHT);
	// 傾きが左なら
	else if (m_angleZ > 0.0f) 
		SetAngle(CItemBase::ITEM_ANGLE::LEFT);
}
