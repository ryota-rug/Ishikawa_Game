#include "GameUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

using namespace DirectX;

GameUI::GameUI()
	:m_Size(1280.0f, -720.0f), m_DisplayPos(640.0f, 360.0f),
	m_Pos(640.0f, 360.0f, 0.0f), m_Scale(1.0f, 1.0f, 1.0f), m_Angle(0.0f, 0.0f, 0.0f)
{
	m_pSprite = new SpriteManager;


	// テクスチャ読み込み
	LoadTextureFromFile("Assets/2D/main_UI2.png", &m_pNazoBar);
}

GameUI::~GameUI()
{
	// テクスチャ解放
	m_pNazoBar->Release();
	delete m_pSprite;
}

void GameUI::Draw()
{
	m_pSprite->Draw(m_DisplayPos, m_Size, m_Angle, { 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, m_pNazoBar);
}
