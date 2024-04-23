#include "LoadScreen.h"
#include "Input.h"

#define STAGE_HEIGHT	(50.0f)
#define STAGE_LOW		(630.0f)
#define STAGE_RIGHT		(1180.0f)	//�ő�1280.0f
#define STAGE_LEFT		(100.0f)		//�ŏ�0.0f

//�R���X�g���N�^�[
cLoadScreen::cLoadScreen()
	:m_State(LOADSCREEN_STATE::SCREEN_FEEDOUT),
	m_end(false),
	m_pSpriteManager(nullptr),
	m_pPlayer(nullptr),
	m_LoadEnd(false)
{
	m_pSpriteManager = new SpriteManager();

	//�w�i
	for (int i = 0; i < 2; i++)
	{
		m_pBackGround[i] = new Image2D("Assets/2D/Title/title_move.png", m_pSpriteManager);
		m_pBackGround[i]->pos = { 640.0f + i * 1280.0f, 370.0f };
		m_pBackGround[i]->size = { 1280.0f, 720.0f };
		m_pBackGround[i]->color.w = 0.0f;
	}

	//�v���C���[
	m_pPlayer = new Image2D("Assets/2D/animation/robot.png", m_pSpriteManager);
	m_pPlayer->SetTexScale(4, 1);
	m_pPlayer->pos = { -200.0f, 630.0f };
	m_pPlayer->size = { 450.0f, 450.0f };
	m_pPlayer->color.w = 0.0f;

	//���̉摜
	m_pBlack = new Image2D("Assets / 2D / Black.png", m_pSpriteManager);
	m_pBlack->pos = { 640.0f, 360.0f };
	m_pBlack->size = { 1280.0f, 720.0f };
	m_pBlack->color = { 1.0f,1.0f,1.0f,0.0f };

	m_State = LOADSCREEN_STATE::SCREEN_FEEDOUT;
}

//�f�X�g���N�^�[
cLoadScreen::~cLoadScreen()
{
	delete m_pBlack;
	delete m_pPlayer;
	for (int i = 0; i < 2; i++)
	{
		delete m_pBackGround[i];
	}
	delete m_pSpriteManager;
}

//�A�b�v�f�[�g
void cLoadScreen::Update()
{
	switch (m_State)
	{
	case cLoadScreen::SCREEN_FEEDOUT:
		
		//�ǂ�ǂ񖾂邭���Ă���
		m_pBlack->color.w -= 1.0f / (1.0f * 60.0f);

		if (m_pBlack->color.w < 0.0f)
		{
			m_pBlack->color.w = 0.0f;
			m_State = LOADSCREEN_STATE::SCREEN_DRAW;
		}
		break;
	case cLoadScreen::SCREEN_DRAW:
		//���ʂɕ`��
		if (m_LoadEnd)
		{
			m_State = LOADSCREEN_STATE::SCREEN_FEEDIN;
		}
		{
			//�A�j���[�V�����X�V
			m_pPlayer->UpdateAnimation(10.0f);

			//�w�i�X�V
			const float speed = 0.1f;
			for (int i = 0; i < 2; i++)
			{
				m_pBackGround[i]->pos.x -= speed;
			}

			//�ꖇ�ڂ��o��������
			if (m_pBackGround[0]->pos.x < -640.0f)
			{
				for (int i = 0; i < 2; i++)
				{
					//�����ʒu�ɖ߂�
					m_pBackGround[i]->pos.x = 640.0f + i * 1280.0f;
				}
			}
		}

		break;
	case cLoadScreen::SCREEN_FEEDIN:
		//�ǂ�ǂ�Â����Ă���
		m_pBlack->color.w += 1.0f / (1.0f * 60.0f);

		if (m_pBlack->color.w > 1.0f)
		{
			m_pBlack->color.w = 0.0f;
			m_pPlayer->color.w = 0.0f;
			for (int i = 0; i < 2; i++)
			{
				m_pBackGround[i]->color.w = 0.0f;
			}
			m_end = true;
		}

		break;
	default:
		break;
	}
}

//�`��
void cLoadScreen::Draw()
{
	EnableDepth(false);
	for (int i = 0; i < 2; i++)
	{
		m_pBackGround[i]->Draw();
	}
	m_pPlayer->Draw();
	m_pBlack->Draw();
	EnableDepth(true);
}

//���������ŉ������Ă���̂���Ԃ�
cLoadScreen::LOADSCREEN_STATE cLoadScreen::GetState()
{
	return m_State;
}

//�������̏������I���������Ԃ�
bool cLoadScreen::GetEND()
{
	return m_end;
}

//���[�h���I���������ݒ�
void cLoadScreen::SetLoadEnd(bool End)
{
	m_LoadEnd = End;
}

//������������
void cLoadScreen::Init()
{
	m_State = LOADSCREEN_STATE::SCREEN_FEEDOUT;
	m_end = false;
	m_LoadEnd = false;
	m_pPlayer->pos = { -200.0f,630.0f };

	for (int i = 0; i < 2; i++)
	{
		m_pBackGround[i]->pos.x = 640.0f + i * 1280.0f;
		m_pBackGround[i]->color.w = 1.0f;
	}
	m_pBlack->color.w = 1.0f;
	m_pPlayer->color.w = 1.0f;
}