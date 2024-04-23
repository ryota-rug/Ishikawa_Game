#include "Gas.h"
#include "ModelManager.h"
#include "PileBankerBase.h"
#include "CameraMiss.h"
#include "Effect_Manager.h"
#include "Jewely.h"

#define NOTFOUND_NULLBLOCK (999)
#define NOTFOUND_GASBLOCK (888)

using namespace std;

bool g_touchOnLava;


CGas::CGas(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY),
	m_moveSpeed(0.2f)
{
	m_Type = BLOCK_GAS;
	
	m_HP = 9999;
	m_DEF = 0;

	m_exploded = false;
	g_touchOnLava = false;
	m_moving = false;

	m_Invincibility = true;
	m_Slipped = true;

	m_moveDrawPos = { 0.0f, 0.0f, 0.0f };

	///ADDMODEL_SENDDATA("Gas", "Assets/unitychan/unitychan.fbx");
	
	m_Angle = (rand() % 1000) / 1000.0f;
	m_MovePos = { 0.0f,0.0f,0.0f };
	CModelManager::c_AddModel("GAS", "Assets/New_Block/gass/blocks_gasss.fbx");

	m_pSEExplosion = new SE("Assets/SE/Gas_Explosion.wav");
	m_pSECollisionNormalBunker = new SE("Assets/SE/Gas_CollisionNormalBunker.wav");
	m_pBreak_ItemSE = new SE("Assets/SE/Item_Break.wav");
}


CGas::~CGas()
{
	delete m_pBreak_ItemSE;
	delete m_pSEExplosion;
	delete m_pSECollisionNormalBunker;
}



void CGas::Update()
{
	//---マグマとの接触判定
	//マグマに触れていたら爆発する
	auto CheckLava = [this](int posX, int posY)
	{
		if (posX >= 0 && m_pMyStage->GetStageWidthNum().X > posX &&
			posY >= 0 && m_pMyStage->GetStageWidthNum().Y > posY)
		{
			Block_Base* tmp = m_pMyStage->GetBlockInfo(posX, posY);
			if (tmp == nullptr) { return false; }
			if (tmp->GetType() == Block_Base::BLOCK_MAGMA)
			{
				return true;
			}
		}

		return false;
	};

	g_touchOnLava =	CheckLava(m_MapPos.X + 1, m_MapPos.Y    ) |
					CheckLava(m_MapPos.X - 1, m_MapPos.Y    ) |
					CheckLava(m_MapPos.X    , m_MapPos.Y + 1) |
					CheckLava(m_MapPos.X    , m_MapPos.Y - 1);

	if (g_touchOnLava) 
	{ 
		CollisionNavigate(); 
	}



	//--- 移動中
	if (m_moving)
	{
		m_moving = false; //移動中なら下の処理で true になる

		if (m_moveDrawPos.X < -1.0f) { m_moveDrawPos.X += m_moveSpeed; m_moving = true; }
		if (m_moveDrawPos.X >  1.0f) { m_moveDrawPos.X -= m_moveSpeed; m_moving = true; }
		if (m_moveDrawPos.Y < -1.0f) { m_moveDrawPos.Y += m_moveSpeed; m_moving = true; }
		if (m_moveDrawPos.Y >  1.0f) { m_moveDrawPos.Y -= m_moveSpeed; m_moving = true; }


		return;
	}



	//---マップ座標移動
	//変数宣言
	int leftAir;
	int rightAir;
	int leftGas;
	int rightGas;

	leftAir = CheckLeft(leftAir = 0);		//左上の空洞までの距離
	rightAir = CheckRight(rightAir = 0);	//右上の空洞までの距離
	leftGas = CheckLeftGas(leftGas = 0);	//左のガスブロックまでの距離
	rightGas = CheckRightGas(rightGas = 0);	//右のガスブロックまでの距離


	//真上が空洞だったら上に移動
	if (leftAir == 0 || rightAir == 0)
	{
		m_pMyStage->MoveBlock(m_MapPos.X, m_MapPos.Y - 1);
		m_DrawPos = m_pMyStage->Get_DrawPos(m_MapPos.X, m_MapPos.Y - 1);
		m_moveDrawPos.Y = -Block_Base::BlockSize;
		m_moving = true;
		return;
	}

	//真上がガスだったら移動しない
	if (leftGas == 0 && rightGas == 0) { return; }	


	//ブロックが無い方向に向かって移動
	if (leftAir != NOTFOUND_NULLBLOCK || rightAir != NOTFOUND_NULLBLOCK)	//上に空洞がある場合
	{
		MoveGas(leftAir, rightAir);
		return;
	}

	//ガスに向かって移動
	if (leftGas != NOTFOUND_GASBLOCK || rightGas != NOTFOUND_GASBLOCK)	//移動できる場所にガスブロックが見つかった場合
	{
		if (leftGas == 0 || rightGas == 0) { return; }	//左右が両方ふさがっていたら移動しない

		MoveGas(leftGas, rightGas);
		return;
	}
}



void CGas::Draw()
{	
	m_MovePos.Y = sin(m_Angle) * 3.0f;

	m_Angle += 0.03f;

	FloatPos pos = m_DrawPos + m_MovePos + m_moveDrawPos;
	FloatSize size = { 0.5f, 0.5f, 0.5f };
	float angle[3] = { 0.0f, 90.0f, 0.0f };

	MODELDRAW_SENDDATA("GAS", pos, size, angle);
}



void CGas::CollisionNavigate()
{
	if (m_pMyStage->GetPileBanker()->GetHeet() ||	//熱杭だったら爆発する
		g_touchOnLava)								//マグマに触れていたら爆発する
	{
		m_pMyStage->GetPileBanker()->StopBanker();
		if (m_pMyStage->GetSideBanker() != nullptr) { m_pMyStage->GetSideBanker()->StopBanker(); }

		//連鎖的に爆発した時に２回目以降は呼び出さないようにする
		if (m_exploded) { return; }
		else			{ m_exploded = true; }
		
		//隣接ブロックを爆発させる
		ExplosionGas(m_MapPos.X  , m_MapPos.Y  );	//自分のいる位置
		ExplosionGas(m_MapPos.X  , m_MapPos.Y-1);	//上のブロック
		ExplosionGas(m_MapPos.X  , m_MapPos.Y+1);	//下のブロック
		ExplosionGas(m_MapPos.X+1, m_MapPos.Y  );	//右のブロック
		ExplosionGas(m_MapPos.X-1, m_MapPos.Y  );	//左のブロック

		m_pSEExplosion->Play();
		m_IsDestroy = true;
	}
	else
	{
		m_pSECollisionNormalBunker->Play();
	}

	g_touchOnLava = false;
}



int CGas::CheckLeft(int distance)
{
	if (m_MapPos.Y - 1 < 0) { return NOTFOUND_NULLBLOCK; }	//マップの上端に来たら探索をやめる
	if (m_pMyStage->GetBlockInfo(m_MapPos.X - distance, m_MapPos.Y - 1) == nullptr) { return distance; }	//上に空洞が見つかったらそこまでの距離を返す
	
	if (m_MapPos.X - (distance + 1) < 0) { return NOTFOUND_NULLBLOCK; }	//マップの左端に来たら探索をやめる
	if (m_pMyStage->GetBlockInfo(m_MapPos.X - (distance + 1), m_MapPos.Y) == nullptr) { return CheckLeft(distance+1); }	//左にブロックが無ければ探索を続ける

	return NOTFOUND_NULLBLOCK;	//探索を終わる
}

int CGas::CheckRight(int distance)
{
	if (m_MapPos.Y - 1 < 0) { return NOTFOUND_NULLBLOCK; }	//マップの上端に来たら探索をやめる	
	if (m_pMyStage->GetBlockInfo(m_MapPos.X + distance, m_MapPos.Y - 1) == nullptr) { return distance; }	//上に空洞が見つかったらそこまでの距離を返す

	if (m_MapPos.X + (distance + 1) > m_pMyStage->GetStageWidthNum().X - 1) { return NOTFOUND_NULLBLOCK; }	//マップの右端に来たら探索をやめる
	if (m_pMyStage->GetBlockInfo(m_MapPos.X + (distance + 1), m_MapPos.Y) == nullptr) { return CheckRight(distance+1); }	//右にブロックが無ければ探索を続ける
	
	return NOTFOUND_NULLBLOCK;	//探索を終わる
}



int CGas::CheckLeftGas(int distance)
{
	if (m_MapPos.Y - 1 < 0) { return NOTFOUND_GASBLOCK; }	//マップの上端に来たら探索をやめる

	//上にガスが見つかったらそこまでの距離を返す
	if (m_pMyStage->GetBlockInfo(m_MapPos.X - distance, m_MapPos.Y - 1) != nullptr &&
		m_pMyStage->GetBlockInfo(m_MapPos.X - distance, m_MapPos.Y - 1)->GetType() == BLOCK_GAS)
	{ return distance; }


	if (m_MapPos.X - (distance + 1) < 0) { return NOTFOUND_GASBLOCK; }	//マップの左端に来たら探索をやめる
	if (m_pMyStage->GetBlockInfo(m_MapPos.X - (distance + 1), m_MapPos.Y) == nullptr) { return CheckLeftGas(distance + 1); }	//左にブロックが無ければ探索を続ける
	if (m_pMyStage->GetBlockInfo(m_MapPos.X - (distance + 1), m_MapPos.Y)->GetType() == BLOCK_GAS) { return distance; }			//左のブロックがガスなら現在地までの距離を返す


	return NOTFOUND_GASBLOCK;	//探索を終わる
}

int CGas::CheckRightGas(int distance)
{
	if (m_MapPos.Y - 1 < 0) { return NOTFOUND_GASBLOCK; }	//マップの上端に来たら探索をやめる

	//上にガスが見つかったらそこまでの距離を返す
	if (m_pMyStage->GetBlockInfo(m_MapPos.X + distance, m_MapPos.Y - 1) != nullptr &&
		m_pMyStage->GetBlockInfo(m_MapPos.X + distance, m_MapPos.Y - 1)->GetType() == Block_Base::BLOCK_GAS)
	{ return distance; }

	if (m_MapPos.X + (distance + 1) >= m_pMyStage->GetStageWidthNum().X) { return NOTFOUND_GASBLOCK; }	//マップの右端に来たら探索をやめる
	if (m_pMyStage->GetBlockInfo(m_MapPos.X + (distance + 1), m_MapPos.Y) == nullptr) { return CheckRightGas(distance + 1); }	//右にブロックが無ければ探索を続ける
	if (m_pMyStage->GetBlockInfo(m_MapPos.X + (distance + 1), m_MapPos.Y)->GetType() == BLOCK_GAS) { return distance; }			//右のブロックがガスなら現在地までの距離を返す

	
	return NOTFOUND_GASBLOCK;	//探索を終わる
}



void CGas::MoveGas(int leftDis, int rightDis)
{
	//左の距離と右の距離が同じだった場合
	if (leftDis == rightDis) { return; }


	//左の距離の方が近かった場合
	if (leftDis < rightDis)
	{
		//左に移動
		m_pMyStage->MoveBlock(m_MapPos.X - 1, m_MapPos.Y);
		m_DrawPos = m_pMyStage->Get_DrawPos(m_MapPos.X - 1, m_MapPos.Y);
		m_moveDrawPos.X = +Block_Base::BlockSize;
		m_moving = true;
		return;
	}

	//右の距離の方が近かった場合
	if (leftDis > rightDis)
	{
		//右に移動
		m_pMyStage->MoveBlock(m_MapPos.X + 1, m_MapPos.Y);
		m_DrawPos = m_pMyStage->Get_DrawPos(m_MapPos.X + 1, m_MapPos.Y);
		m_moveDrawPos.X = -Block_Base::BlockSize;
		m_moving = true;
		return;
	}
}



void CGas::ExplosionGas(int posX, int posY)
{
	if (posX < 0 || m_pMyStage->GetStageWidthNum().X - 1 < posX) { return; }
	if (posY < 0 || m_pMyStage->GetStageWidthNum().Y - 1 < posY) { return; }

	if (m_bEffectFlg == 0)
	{
		DirectX::XMFLOAT3 pos = { m_DrawPos.X,m_DrawPos.Y,m_DrawPos.Z };
		DirectX::XMFLOAT3 size = { 10.0f,10.0f,10.0f };
		Effect_Manager::Play_Effect("Explosion", pos, size);
		m_bEffectFlg++;
	}
	

	//ブロックがなければ壊さない
	if (m_pMyStage->GetBlockInfo(posX, posY) == nullptr) 
	{
		//宝石があれば壊す
		if (m_pMyStage->GetJewely(posX, posY) != nullptr)
		{
			CItemBase* pJewely = m_pMyStage->GetJewely(posX, posY);
			DirectX::XMFLOAT3 pos = { pJewely->GetPos().X,pJewely->GetPos().Y,pJewely->GetPos().Z };
			Effect_Manager::Play_Effect("JewelyBreak", pos, { 25.0f,25.0f,25.0f });
			m_pBreak_ItemSE->Play();
			m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS
				, m_pCameraManager->Get_NowCamera()->GetPos(),
				m_pCameraManager->Get_NowCamera()->GetLook());

			CameraMiss* pMissCamera = dynamic_cast<CameraMiss*>(m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MISS));
			if (pMissCamera != nullptr)
				pMissCamera->Set({ m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z });
			m_pMyStage->DestroyJewely(posX, posY);
			m_pMyStage->Set_GameOver(Stage_Base::GAMEOVER_TYPE::GAMEOVER_JEWELY_DESTROY);
		}
		// ヒートアイテムがあれば壊す
		if (m_pMyStage->GetHeet(posX, posY) != nullptr)
		{
			CItemBase* pHeat = m_pMyStage->GetHeet(posX, posY);
			DirectX::XMFLOAT3 pos = { pHeat->GetPos().X,pHeat->GetPos().Y,pHeat->GetPos().Z };
			Effect_Manager::Play_Effect("HeatBreak", pos, { 25.0f,25.0f,25.0f });
			m_pBreak_ItemSE->Play();
			m_pMyStage->DestroyHeet(posX, posY);
		}
		return; 
	}


	//ブロックの種類
	Block_Base::BLOCK_TYPE type = m_pMyStage->GetBlockInfo(posX, posY)->GetType();

	//爆発では壊せないブロック
	if (type == Block_Base::BLOCK_BEDROCK)
	{
		return;
	}

	//ガスブロック
	else if (type == Block_Base::BLOCK_GAS)
	{
		m_pMyStage->GetBlockInfo(posX, posY)->CollisionNavigate();
	}

	//それ以外のブロック
	else
	{
		m_pMyStage->DestroyBlock(posX, posY);
	}
}

