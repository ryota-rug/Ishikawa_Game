#include "UI_Tutorial.h"

//----------------------------
// �R���X�g���N�^
//----------------------------
UI_Tutorial::UI_Tutorial()
	:m_alpha(1.0f),
	 AlphaCnt(0.02f)
{
	m_pSpriteManager = new SpriteManager;

	m_pXbox = new Image2D("Assets/2D/tutorial/Lbutton.png", m_pSpriteManager);
	m_pXbox->pos   = { 950.0f, 620.0f };
	m_pXbox->size  = { 400.0f, 80.0f };
	m_pXbox->color = { 1.0f, 1.0f, 1.0f, 1.0f };


	m_pPC = new Image2D("Assets/2D/tutorial/TAB.png", m_pSpriteManager);
	m_pPC->pos   = { 950.0f, 620.0f };
	m_pPC->size  = { 400.0f, 80.0f };
	m_pPC->color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// UI�؂�ւ��悤�ϐ�������
	m_UIFlg = false;
}


//----------------------------
// �f�X�g���N�^
//----------------------------
UI_Tutorial::~UI_Tutorial()
{
	delete m_pPC;
	delete m_pXbox;

	delete m_pSpriteManager;
}


//----------------------------
// �X�V
//----------------------------
void UI_Tutorial::Update()
{
	m_alpha -= AlphaCnt;

	if (m_UIFlg == false && m_alpha <= 0.0f)
	{
		m_UIFlg = true;
		AlphaCnt = -0.02f;
	}
	else if (m_UIFlg == true && m_alpha <= 0.0f)
	{
		m_UIFlg = false;
		AlphaCnt = -0.02f;
	}

	if (1.0f <= m_alpha)
	{
		AlphaCnt = 0.02f;
	}
}


//----------------------------
// �`��
//----------------------------
void UI_Tutorial::Draw()
{
	if (m_UIFlg == false)
	{
		m_pXbox->color = { 1.0f, 1.0f, 1.0f, m_alpha };
		m_pXbox->Draw();
	}
	else
	{
		m_pPC->color = { 1.0f, 1.0f, 1.0f, m_alpha };
		m_pPC->Draw();
	}
}
