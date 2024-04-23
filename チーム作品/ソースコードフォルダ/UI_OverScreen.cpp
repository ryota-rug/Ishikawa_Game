#include "UI_OverScreen.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

UI_OverScreen::UI_OverScreen()
{
	m_pSprite = new SpriteManager;

	DirectX::XMFLOAT2 WindowSize = { 1280.0f, 720.0f };

	//スクリーンのポジションの設定
	m_ScreenTransform.m_pos = { WindowSize.x * 0.5f,-200.0f };
	m_ScreenTransform.m_size = { 1200.0f,-600.0f };
	m_ScreenTransform.m_Scale = { 1.0f,1.0f,1.0f };
	m_ScreenTransform.m_Angle = { 0.0f,0.0f,0.0f };
	// テクスチャ読み込み
	LoadTextureFromFile("Assets/2D/screen.png", &m_pScreenTexture);

	const char* TextureName[UI_Over::MAX] =
	{
		"Assets/2D_Roma/letter/GameOver0.png",			//ゲームオーバー
		"Assets/2D_Roma/letter/Retry0.png",			//リトライ
		"Assets/2D_Roma/letter/StageSelect.png",	//ステージセレクト
	};

	const char* ChoseTextureName[UI_Over::MAX] =
	{
		"Assets/2D_Roma/letter/GameOver0.png",				//ゲームオーバー
		"Assets/2D_Roma/letter/Retry_Select.png",		//リトライ
		"Assets/2D_Roma/letter/StageSelect_Select.png",	//ステージセレクト
	};

	DirectX::XMFLOAT2 PosIndex[UI_Over::MAX] =
	{
		{0.0f,-110.0f},	//ゲームオーバー
		{0.0f,20.0f},	//リトライ
		{0.0f,90.0f},	//ステージセレクト
	};

	DirectX::XMFLOAT2 SizeIndex[UI_Over::MAX] =
	{
		{400.0f,-50.0f},
		{240.0f,-40.0f},
		{360.0f,-45.0f},
	};

	//座標の設定
	for (int i = 0; i < UI_Over::MAX; i++)
	{
		m_Transform[i].m_pos = PosIndex[i];
		m_Transform[i].m_size = SizeIndex[i];
		m_Transform[i].m_Scale = { 1.0f,1.0f,1.0f };
		m_Transform[i].m_Angle = { 0.0f,0.0f,0.0f };

		LoadTextureFromFile(TextureName[i], &m_pTexture[i]);
		LoadTextureFromFile(ChoseTextureName[i], &m_pChoseTexture[i]);
	}

	m_pArm = new Image2D("Assets/2D/screen_arm.png", m_pSprite);
	m_pArm->size = { 4890.0f * 0.15f,3135.0f * 0.15f };
	m_ArmAddPos = { 0.0f, -200.0f };
}
UI_OverScreen::~UI_OverScreen()
{
	delete m_pArm;
	for (int i = 0; i < UI_Over::MAX; i++)
	{
		m_pTexture[i]->Release();
		m_pChoseTexture[i]->Release();
	}
	m_pScreenTexture->Release();

	delete m_pSprite;
}
bool UI_OverScreen::Update()
{
	const unsigned int SCREEN_CENTER_SIDE = 1280 * 0.5f;
	const unsigned int SCREEN_CENTER_LENGTH = 720 * 0.5f;

	bool End_exe = false;

	switch (m_NowState)
	{
	case UI_OverScreen::STATE_INIT:
		m_NowState = UI_OverScreen::STATE_IN;
		break;
	case UI_OverScreen::STATE_IN:	//スクリーンを入れる
		if (SCREEN_CENTER_LENGTH <= m_ScreenTransform.m_pos.y)
		{
			m_ScreenTransform.m_pos.y = SCREEN_CENTER_LENGTH;
			m_NowState = UI_OverScreen::STATE_STAY;
		}

		m_ScreenTransform.m_pos.y += 15.0f;
		break;
	case UI_OverScreen::STATE_STAY:

		break;
	case UI_OverScreen::STATE_OUT:	//スクリーンを外に出す
		if (-250.0f >= m_ScreenTransform.m_pos.y)
		{
			m_NowState = UI_OverScreen::STATE_END;
		}

		m_ScreenTransform.m_pos.y -= 25.0f;

		break;
	case UI_OverScreen::STATE_END:
		End_exe = true;
		break;
	default:
		break;
	}

	return End_exe;
}

void UI_OverScreen::ScreenInit()
{
	m_NowState = UI_OverScreen::STATE_INIT;
}

void UI_OverScreen::ScreenDraw()
{
	m_pArm->pos.x = m_ScreenTransform.m_pos.x + m_ArmAddPos.x;
	m_pArm->pos.y = m_ScreenTransform.m_pos.y + m_ArmAddPos.y;
	m_pArm->Draw();

	m_pSprite->Draw(m_ScreenTransform.m_pos, m_ScreenTransform.m_size, m_ScreenTransform.m_Angle,
		DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		m_pScreenTexture);
}

void UI_OverScreen::GameOverDraw()
{
	UItransform TempPos = m_Transform[UI_Over::GAMEOVER];

	TempPos.m_pos.x += m_ScreenTransform.m_pos.x;
	TempPos.m_pos.y += m_ScreenTransform.m_pos.y;

	m_pSprite->Draw(TempPos.m_pos, TempPos.m_size, TempPos.m_Angle,
		DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		m_pChoseTexture[UI_Over::GAMEOVER]);
}

void UI_OverScreen::RetryDraw(bool Select)
{
	UItransform TempPos = m_Transform[UI_Over::RETRY];
	ID3D11ShaderResourceView* pTexture;
	if (Select)
	{
		pTexture = m_pChoseTexture[UI_Over::RETRY];
	}
	else
	{
		pTexture = m_pTexture[UI_Over::RETRY];
	}


	TempPos.m_pos.x += m_ScreenTransform.m_pos.x;
	TempPos.m_pos.y += m_ScreenTransform.m_pos.y;

	m_pSprite->Draw(TempPos.m_pos, TempPos.m_size, TempPos.m_Angle,
		DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		pTexture);
}

void UI_OverScreen::StageSelectDraw(bool Select)
{
	UItransform TempPos = m_Transform[UI_Over::STAGESELECT];
	ID3D11ShaderResourceView* pTexture;
	if (Select)
	{
		pTexture = m_pChoseTexture[UI_Over::STAGESELECT];
	}
	else
	{
		pTexture = m_pTexture[UI_Over::STAGESELECT];
	}


	TempPos.m_pos.x += m_ScreenTransform.m_pos.x;
	TempPos.m_pos.y += m_ScreenTransform.m_pos.y;

	m_pSprite->Draw(TempPos.m_pos, TempPos.m_size, TempPos.m_Angle,
		DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		pTexture);
}

UI_OverScreen::STATE_OVER UI_OverScreen::GetState()
{
	return m_NowState;
}

void UI_OverScreen::SetState(UI_OverScreen::STATE_OVER NextState)
{
	m_NowState = NextState;
}