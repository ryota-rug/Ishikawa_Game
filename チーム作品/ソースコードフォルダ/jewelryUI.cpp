#include "jewelryUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

#define MAX_JEWELRY     (3)
#define MAX_CUREECTCNT (55)

//---------------------------------
// コンストラクタ
//---------------------------------
JewelryUI::JewelryUI()
	: m_UINum(0),
	  tmp(0)
{
	m_pSprite = new SpriteManager;
	//m_pPlayer = new C_Player;
	
	for (int i = 0; i < MAX_JEWELRY * 2; i++)
	{
		g_Jewelry[i].m_Pos         = { 0.0f, 0.0f};
		g_Jewelry[i].m_Size        = { 0.0f, 0.0f };
		g_Jewelry[i].m_Angle       = { 0.0f,   0.0f,  0.0f };
		g_Jewelry[i].m_StartPos    = { 0.0f, 0.0f };
		g_Jewelry[i].m_EndPos      = { 0.0f, 0.0f };
		g_Jewelry[i].m_ControlPos1 = { 0.0f, 0.0f };
		g_Jewelry[i].m_ControlPos2 = { 0.0f, 0.0f };
		g_Jewelry[i].CurrentCnt = 0;
		g_Jewelry[i].MaxCnt = 90;
		g_Jewelry[i].GetJewelry = false;
		g_Jewelry[i].Use = false;
		g_Jewelry[i].AnimeFlg = false;
	}

}


//--------------------
// デストラクタ
//--------------------
JewelryUI::~JewelryUI()
{
	for (int i = 0; i < m_UINum; i++)
	{
		g_Jewelry[i].m_pJewelryGet->Release();
		g_Jewelry[i].m_pJewelryNot->Release();
	}
	
	//delete m_pPlayer;
	delete m_pSprite;
}


//----------------------------------------
// 宝石を作成
// 引数：int num 作成する宝石UIの数
//----------------------------------------
void JewelryUI::MakeJewelryUI(int Num)
{
	// 保存用変数に作成するUIの数を代入
	m_UINum = Num;

	for (int i = 0; i < Num * 2; i++)
	{
		if (i < Num)
		{
			g_Jewelry[i].m_Pos = { 1110.0f, 200.0f - (i * 75.0f) };
		}
		else
		{
			g_Jewelry[i].m_Pos = { -1500.0f, 800.0f };
		}

		g_Jewelry[i].m_Size  = { 80.0f, -70.0f };
		g_Jewelry[i].m_Angle = { 0.0f,   0.0f,  10.0f };
		g_Jewelry[i].GetJewelry = false;

		LoadTextureFromFile("Assets/2D/ダイヤ_未獲得.png", &g_Jewelry[i].m_pJewelryNot);
		LoadTextureFromFile("Assets/2D/ダイヤ_獲得.png", &g_Jewelry[i].m_pJewelryGet);
	}

}


//----------------------------------------
// 宝石のUIを切り替える
//----------------------------------------
void JewelryUI::GetJewelryUI()
{
	g_Jewelry[tmp + m_UINum].GetJewelry = true;	
	tmp++;
}


//----------------------------------------
// 宝石取得時のアニメーション更新
//----------------------------------------
void JewelryUI::GetMoveJewelry()
{
	for (int i = m_UINum; i < m_UINum * 2; i++)
	{
		// 宝石を取得していた場合
		if (g_Jewelry[i].GetJewelry && !g_Jewelry[i].AnimeFlg)
		{
			// 一度だけやる処理
			if (g_Jewelry[i].Use == false)
			{
				//引数の座標からスクリーン座標に変換する
				m_2DJewelyPos = m_pCameraManager->ChangeScreenPos(m_pPlayer->GetPos());
				// プレイヤーの現在座標を取得
				g_Jewelry[i].m_Pos = m_2DJewelyPos;

				// 開始地点の設定
				g_Jewelry[i].m_StartPos = m_2DJewelyPos;

				// 終了地点
				g_Jewelry[i].m_EndPos = g_Jewelry[i - m_UINum].m_Pos;

				// 制御点１
				g_Jewelry[i].m_ControlPos1 = {
					(g_Jewelry[i].m_EndPos.x - g_Jewelry[i].m_StartPos.x) * 0.4f,
					(g_Jewelry[i].m_EndPos.y - g_Jewelry[i].m_StartPos.y) * 0.15f
				};

				// 制御点２
				g_Jewelry[i].m_ControlPos2 = {
				(g_Jewelry[i].m_EndPos.x - g_Jewelry[i].m_StartPos.x) * 0.3f,
				(g_Jewelry[i].m_EndPos.y - g_Jewelry[i].m_StartPos.y) * 0.03f
				};

				// フラグ切り替え
				g_Jewelry[i].Use = true;
			}
		

			// カウンタの更新
			g_Jewelry[i].CurrentCnt++;

			float Bzier0 = pow(1 - (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt, 3);
			float Bzier1 = 
				 pow(3 * (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt * 
				(pow(1 - (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt, 2)), 3);

			float Bzier2 = 
				 pow(3 * (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt, 2) *
				(1 - (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt);
			float Bzier3 = pow((float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt, 3);

			// 座標の更新
			g_Jewelry[i].m_Pos.x = (g_Jewelry[i].m_StartPos.x    * Bzier0) +
				                   (g_Jewelry[i].m_ControlPos1.x * Bzier1) +
								   (g_Jewelry[i].m_ControlPos2.x * Bzier2) +
				                   (g_Jewelry[i].m_EndPos.x      * Bzier3);

			g_Jewelry[i].m_Pos.y = (g_Jewelry[i].m_StartPos.y    * Bzier0) +
				                   (g_Jewelry[i].m_ControlPos1.y * Bzier1) +
							       (g_Jewelry[i].m_ControlPos2.y * Bzier2) +
				                   (g_Jewelry[i].m_EndPos.y      * Bzier3);

			// 終了判定
			if (g_Jewelry[i].m_EndPos.x - 25.0f <= g_Jewelry[i].m_Pos.x &&
				g_Jewelry[i].m_EndPos.x + 25.0f >= g_Jewelry[i].m_Pos.x)
			{
				if (g_Jewelry[i].m_EndPos.y - 25.0f <= g_Jewelry[i].m_Pos.y &&
					g_Jewelry[i].m_EndPos.y + 25.0f >= g_Jewelry[i].m_Pos.y)
				{
					// 移動時に使用したUIを画面外へ
					g_Jewelry[i].m_Size = { 0.0f, 0.0f };
					g_Jewelry[i].m_Pos = { 1500.0f, 800.0f };
					g_Jewelry[i].AnimeFlg = true;

					// 獲得時の宝石UIの表示
					g_Jewelry[i - m_UINum].GetJewelry = true;

				}
			}
		}

	}

}


//--------------------
// 描画
//--------------------
void JewelryUI::Draw()
{
	for (int i = 0; i < m_UINum * 2; i++)
	{
		// 宝石が未獲得の場合
		if (g_Jewelry[i].GetJewelry == false)
		{
			m_pSprite->Draw(g_Jewelry[i].m_Pos, g_Jewelry[i].m_Size, g_Jewelry[i].m_Angle,
							{ 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, 
							g_Jewelry[i].m_pJewelryNot);
		}

		// 宝石を獲得している場合
		if (g_Jewelry[i].GetJewelry == true)
		{
			m_pSprite->Draw(g_Jewelry[i].m_Pos, g_Jewelry[i].m_Size, g_Jewelry[i].m_Angle,
							{ 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, 
							g_Jewelry[i].m_pJewelryGet);
		}
	
	}
}


//---------------------------------------
// 宝石を獲得
// 引数：int num 宝石の獲得数
//---------------------------------------
int AddJewelry(int num)
{
	return 0;
}

void JewelryUI::SetPlayer(C_Player* pPlayer)
{
	m_pPlayer = pPlayer;
}

void JewelryUI::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}