#include "LoadScene.h"
#include "Sound.h"

using namespace DirectX;

CScene_Load::CScene_Load()
{
	m_pSpriteManager = new SpriteManager();

	m_pBack = new Image2D("Assets/2D/Black.png", m_pSpriteManager);
	m_pBack->pos = { 640.0f, 360.0f };
	m_pBack->size = { 1280.0f, 720.0f };
	m_pBack->color = { 1.0f,1.0f,1.0f,1.0f };

	m_loadState = LOAD_BEFORE;
	m_loadEnd = false;
}

CScene_Load::~CScene_Load()
{
	delete m_pBack;

	delete m_pSpriteManager;
}

void CScene_Load::Update()
{
	switch (m_loadState)
	{
	case CScene_Load::LOAD_BEFORE:
	{
		m_pBack->color.w += 0.03f;

		if (m_pBack->color.w >= 1.0f)
		{
			m_pBack->color.w = 1.0f;
			_GetXAudio2()->StopEngine();
			m_loadState = LOAD_LOADING;
		}
	}
	break;

	case CScene_Load::LOAD_LOADING:
	{
		if (m_loadEnd)
		{
			_GetXAudio2()->StartEngine();
			m_loadState = LOAD_AFTER;
		}
	}
	break;
	
	case CScene_Load::LOAD_AFTER:
	{
		m_pBack->color.w -= 0.03f;

		if (m_pBack->color.w <= 0.0f)
		{
			m_pBack->color.w = 0.0f;
			m_loadState = LOAD_NONE;
		}
	}
	break;
	}
}

void CScene_Load::Draw()
{
	EnableDepth(false);
	m_pBack->Draw();
	EnableDepth(true);
}



void CScene_Load::Reset()
{
	m_pBack->color.w = 0.0f;
	m_loadState = LOAD_BEFORE;
	m_loadEnd = false;
}

CScene_Load::LOADSCENE_STATE CScene_Load::GetLoadState()
{
	return m_loadState; 
}

void CScene_Load::LoadEnd() 
{
	m_loadEnd = true; 
}
