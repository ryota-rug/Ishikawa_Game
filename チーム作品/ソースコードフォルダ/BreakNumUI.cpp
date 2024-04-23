#include "BreakNumUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

//********** 定数定義 **********
#define MAX_BREAK_UI        (2)   // UIの桁数
#define ANIM_BREAK_FRAME    (2)   // アニメーションの1コマのフレーム数
#define ANIM_BREAK_SPLIT_X (11)	  // 画像の分割数（横）
#define ANIM_BREAK_SPLIT_Y  (1)   // 画像の分割数（縦）


//--------------------
// コンストラクタ
//--------------------
BreakNumUI::BreakNumUI()
{
	m_pSprite = new SpriteManager;
	

	for (int i = 0; i < MAX_BREAK_UI; i++)
	{
		// 画像の位置
		g_BreakUI[i].m_Pos = { 130.0f + (i * 60.0f), 657.0f };
		//g_BreakUI[i].m_Pos = { 1113.0f, 360.0f - (i * 50.0f) };

		// 画像のサイズ
		g_BreakUI[i].m_Size = { 65.0f, -70.0f };

		// 画像の角度
		g_BreakUI[i].m_Angle = { 0.0f, 0.0f, 0.0f };

		// 画像の拡縮
		g_BreakUI[i].m_Scale = { 1.0f, 1.0f, 1.0f };

		// 画像の左上のUV座標
		g_BreakUI[i].posTexCoord = { 0.0f, 0.0f };

		// 画像の分割数
		g_BreakUI[i].sizeTexCoord.x = 1.0f / (float)ANIM_BREAK_SPLIT_X;
		g_BreakUI[i].sizeTexCoord.y = 1.0f;

		// 画像の使用状態
		g_BreakUI[i].use = true;

		// フレーム数
		g_BreakUI[i].frame = 0;

		// 画像の何コマ目か
		g_BreakUI[i].currentAnimNo = 0;

		// テクスチャ読み込み
		LoadTextureFromFile("Assets/2D/number_blue.png", &g_BreakUI[i].m_pBreakUI);
	}

	// 打ち付け回数初期化
	m_BreakCnt = 0;
}


//--------------------
// デストラクタ
//--------------------
BreakNumUI::~BreakNumUI()
{
	for (int i = 0; i < MAX_BREAK_UI; i++)
	{
		g_BreakUI[i].m_pBreakUI->Release();
	}

	delete m_pSprite;
}


//--------------------
// 描画
//--------------------
void BreakNumUI::Draw()
{
	for (int i = 0; i < MAX_BREAK_UI; i++)
	{
		m_pSprite->Draw(
			g_BreakUI[i].m_Pos, g_BreakUI[i].m_Size, g_BreakUI[i].m_Angle,
			g_BreakUI[i].posTexCoord, g_BreakUI[i].sizeTexCoord,
			{ 1.4f,1.4f,1.4f,1.0f },
			g_BreakUI[i].m_pBreakUI);
	}

	Sprite::SetUVPos({ 0.0f, 0.0f });
	Sprite::SetUVScale({ 1.0f, 1.0f });
}


//--------------------------------------
// 破壊数増加
// 引数：int num  破壊したブロックの数
//--------------------------------------
void BreakNumUI::AddNum(int num)
{

		m_BreakCnt += 1;

		// 上限補正
		if (99 < m_BreakCnt)
		{
			m_BreakCnt = 99;
		}

		// テクスチャ座標更新
		BreakNumUI::UpdateTexCoord();

}



//----------------------------------
// 画像のUV座標更新
//----------------------------------
void BreakNumUI::UpdateTexCoord()
{
	int tmp = m_BreakCnt;

	for (int i = MAX_BREAK_UI - 1; 0 <= i; i--)
	{
		// tmpの値の下一桁取得
		g_BreakUI[i].currentAnimNo = tmp % 10;

		// テクスチャ座標更新
		g_BreakUI[i].posTexCoord.x = g_BreakUI[i].sizeTexCoord.x *
			(g_BreakUI[i].currentAnimNo % ANIM_BREAK_SPLIT_X);

		g_BreakUI[i].posTexCoord.y = g_BreakUI[i].sizeTexCoord.y *
			(g_BreakUI[i].currentAnimNo / ANIM_BREAK_SPLIT_X);

		// 桁落とし
		tmp /= 10;
	}
}


//----------------------------------
// ブロック破壊数取得
//----------------------------------
int BreakNumUI::GetBreckCnt()
{
	return m_BreakCnt;
}
