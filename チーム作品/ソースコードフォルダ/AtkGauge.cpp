#include "AtkGauge.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

const float MaxAtk = 99.0f;
const float MinAtk = 0.0f;
const float MaxSizeY = -398.0f;   // 画像の最大サイズ

//--------------------
// コンストラクタ
//--------------------
AtkGauge::AtkGauge()
	:m_Size(45.0f, 0.0f), m_DisplayPos(1207.0f, 493.0f),
	 m_Scale(1.0f, 1.0f, 1.0f), m_Angle(0.0f, 0.0f, 0.0f),
	 m_Count(0.0f), m_NowAtk(0.0f), m_Rate(0.0f), m_AtkFlg(false)
{
	m_pSprite = new SpriteManager;

	// テクスチャ読み込み
	LoadTextureFromFile("Assets/2D/パワーゲージバー.png", &m_pAtkGauge);
}


//--------------------
// デストラクタ
//--------------------
AtkGauge::~AtkGauge()
{
	m_pAtkGauge->Release();
	delete m_pSprite;
}


//--------------------
// アタックゲージ変化
//--------------------
void AtkGauge::ChangeGauge(float Atk)
{
	// 攻撃力が99未満の時
	if (Atk < MaxAtk)
	{
		// 割合計算
		m_Rate = Atk / MaxAtk;
		m_Size.y = m_Rate * MaxSizeY;
	}
	else
	{
		Atk = MaxAtk;

		// 割合計算
		m_Rate = Atk / MaxAtk;
		m_Size.y = m_Rate * MaxSizeY;
	}
}


//--------------------
// ゲージを固定する
//--------------------
void AtkGauge::GaugeFix()
{
	m_AtkFlg = true;
}

//--------------------
// 描画
//--------------------
void AtkGauge::Draw()
{
	DirectX::XMFLOAT2 temp = m_DisplayPos;
	temp.y += (m_Size.y * 0.5f);// +2.0f;

	// ゲージの描画方法
	if (!m_AtkFlg)
	{
		// ゲージが固定されていない場合
		m_pSprite->Draw(temp, m_Size, m_Angle, { 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, m_pAtkGauge);
	}
	else
	{
		// ゲージが固定されている場合
		m_pSprite->Draw(temp, m_Size, m_Angle, { 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,0.0f,0.0f,1.0f }, m_pAtkGauge);
	}
	
}
