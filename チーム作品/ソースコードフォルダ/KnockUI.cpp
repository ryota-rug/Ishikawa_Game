#include "knockUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

//********** 定数定義 **********
#define MAX_KNOCK_UI     (2)   // UIの桁数
#define ANIM_FRAME    (2)   // アニメーションの1コマのフレーム数
#define ANIM_SPLIT_X (11)	// 画像の分割数（横）
#define ANIM_SPLIT_Y  (1)   // 画像の分割数（縦）


//--------------------
// コンストラクタ
//--------------------
KnockUI::KnockUI()
{
	m_pSprite = new SpriteManager;

	for (int i = 0; i < MAX_KNOCK_UI; i++)
	{
		// 画像の位置
		g_KnockUI[i].m_Pos = { 340.0f + (i * 60.0f), 657.0f };
		//g_KnockUI[i].m_Pos = { 1113.0f, 498.0f  - (i * 50.0f) };

		// 画像のサイズ
		g_KnockUI[i].m_Size = { 65.0f, -70.0f };

		// 画像の角度
		g_KnockUI[i].m_Angle = { 0.0f, 0.0f, 0.0f };

		// 画像の拡縮
		g_KnockUI[i].m_Scale = { 1.0f, 1.0f, 1.0f };

		// 画像の左上のUV座標
		g_KnockUI[i].posTexCoord = { 0.0f, 0.0f };

		// 画像の分割数
		g_KnockUI[i].sizeTexCoord.x = 1.0f / (float)ANIM_SPLIT_X;
		g_KnockUI[i].sizeTexCoord.y = 1.0f;

		// 画像の使用状態
		g_KnockUI[i].use = true;

		// フレーム数
		g_KnockUI[i].frame = 0;

		// 画像の何コマ目か
		g_KnockUI[i].currentAnimNo = 0;

		// テクスチャ読み込み
		LoadTextureFromFile("Assets/2D/number_blue.png", &g_KnockUI[i].m_pKnockUI);
	}

	// 打ち付け回数初期化
	m_KnockCnt = 0;


}


//--------------------
// デストラクタ
//--------------------
KnockUI::~KnockUI()
{
	for (int i = 0; i < MAX_KNOCK_UI; i++)
	{
		g_KnockUI[i].m_pKnockUI->Release();
	}
	
	delete m_pSprite;
}


//--------------------
// 描画
//--------------------
void KnockUI::Draw()
{
	for (int i = 0; i < MAX_KNOCK_UI; i++)
	{
		// SpriteにUV情報を送る
		Sprite::SetUVPos(g_KnockUI[i].posTexCoord);
		Sprite::SetUVScale(g_KnockUI[i].sizeTexCoord);

		m_pSprite->Draw(
			g_KnockUI[i].m_Pos, g_KnockUI[i].m_Size, g_KnockUI[i].m_Angle,
			g_KnockUI[i].posTexCoord, g_KnockUI[i].sizeTexCoord, { 1.5f,1.5f,1.5f,1.0f },
			g_KnockUI[i].m_pKnockUI);
	}

	Sprite::SetUVPos({ 0.0f, 0.0f });
	Sprite::SetUVScale({1.0f, 1.0f});
}


//----------------------------------
// 打ち付け回数増加
// 引数：int num  打ち付けた回数
//----------------------------------
void KnockUI::AddKnock(int num)
{
	m_KnockCnt += num;

	// 上限補正
	if (99 < m_KnockCnt)
	{
		m_KnockCnt = 99;
	}

	// テクスチャ座標更新
	KnockUI::UpdateTexCoord();
}


//----------------------------------
// 画像のUV座標更新
//----------------------------------
void KnockUI::UpdateTexCoord()
{
	int tmp = m_KnockCnt;

	for (int i = MAX_KNOCK_UI - 1; 0 <= i; i--)
	{
		// tmpの値の下一桁取得
		g_KnockUI[i].currentAnimNo = tmp % 10;

		// テクスチャ座標更新
		g_KnockUI[i].posTexCoord.x = g_KnockUI[i].sizeTexCoord.x *
			(g_KnockUI[i].currentAnimNo % ANIM_SPLIT_X);

		g_KnockUI[i].posTexCoord.y = g_KnockUI[i].sizeTexCoord.y *
			(g_KnockUI[i].currentAnimNo / ANIM_SPLIT_X);

		// 桁落とし
		tmp /= 10;
	}
}


//----------------------------------
// 打ち付け回数取得
//----------------------------------
int KnockUI::GetKnockCnt()
{
	return m_KnockCnt;
}
