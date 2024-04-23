#include "UI_ClearScore.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

UI_ClearScore::UI_ClearScore()
{
	const unsigned int SCREEN_CENTER_SIDE = 1280 * 0.5f;
	const unsigned int SCREEN_CENTER_LENGTH = 720 * 0.5f;

	m_pSprite = new SpriteManager;

	m_TextureNum = { 11,1 };
	m_TextureSize = { 1.0f / m_TextureNum.x ,1.0f / m_TextureNum.y };
	m_Transform.m_pos	 = {0.0f,0.0f};
	m_Transform.m_size	 = {40.0f,-40.0f};

	LoadTextureFromFile("Assets/2D/number_blue.png", &m_pScoreTexture);
}

UI_ClearScore::~UI_ClearScore()
{
	m_pScoreTexture->Release();
	delete m_pSprite;
}

void UI_ClearScore::Update()
{

}
void UI_ClearScore::Draw(int Score)
{
	int tempScore = Score;	//スコアをコピーしておく
	float Distance = 35.0f;	//数値との間隔

	UItransform TempTransform = m_Transform;

	TempTransform.m_pos.x = TempTransform.m_pos.x + (Distance * 3 * 0.5f - Distance * 0.5f);

	//桁は三桁
	for (int i = 0; i < 3; i++)
	{
		//最小桁
		int MinScore = tempScore % 10;

		DirectX::XMFLOAT2 UVPos;

		//サイズと最小桁から場所を計算
		UVPos.x = MinScore * m_TextureSize.x;
		UVPos.y = 0.0f;
		
		//描画
		m_pSprite->Draw(TempTransform.m_pos, TempTransform.m_size, DirectX::XMFLOAT3(0.0f,0.0f,0.0f),
			UVPos, m_TextureSize, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
			m_pScoreTexture);

		tempScore = tempScore / 10;
		TempTransform.m_pos.x -= Distance;
	}
}
void UI_ClearScore::SetPos(DirectX::XMFLOAT2 pos)
{
	m_Transform.m_pos = pos;
}