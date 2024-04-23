#include "Scene_Select.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "Game3D.h"
#include <time.h>

#include "Select_Data.h"


template<class T, class... args>
void MoveLeft(float speed, T image, args... images);
template<class T>
void MoveLeft(float speed, T image);

template<class T, class... args>
void MoveRight(float speed, T image, args... images);
template<class T>
void MoveRight(float speed, T image);


namespace
{
	bool isDetermine;	//����{�^���������t���O
	bool isBack;		//�߂�{�^���������t���O
	bool isReturn;		//�X�e�[�W����߂��Ă����t���O

	bool roboUp = true;		//�������p

	const float STAGE1_BGM_SPEED = 1.0f;
	const float STAGE2_BGM_SPEED = 1.1f;
	const float STAGE3_BGM_SPEED = 0.8f;
}



CScene_Select::CScene_Select(SCENE beforeScene)
{
	//�X�v���C�g�}�l�[�W��
	m_pSpriteManager = new SpriteManager();


	//�X�e�[�W1�w�i
	m_pGround1 = new Image2D{ "Assets/2D/select/stage1_Ground.png", m_pSpriteManager };
	m_pGround1->size = { 1280.0f, 720.0f };
	m_pGround1->color = { 1.3f,1.3f,1.3f,1.0f };
	m_pBack1 = new Image2D{ "Assets/2D/select/stage1_Back.png", m_pSpriteManager };
	m_pBack1->size = { 1280.0f, 720.0f };
	m_pBack1->color = { 1.4f,1.4f,1.4f,1.0f };

	//�X�e�[�W2�w�i
	m_pFront2 = new Image2D{ "Assets/2D/select/stage2_Front_ver2.png", m_pSpriteManager };	
	m_pFront2->size = { 1280.0f, 720.0f };
	m_pFront2->color = { 1.3f,1.3f,1.3f,1.0f };
	m_pGround2 = new Image2D{ "Assets/2D/select/stage2_Ground.png", m_pSpriteManager };	
	m_pGround2->size = { 1280.0f, 720.0f };
	m_pGround2->color = { 1.3f,1.3f,1.3f,1.0f };
	m_pBack2 = new Image2D{ "Assets/2D/select/stage2_Back.png", m_pSpriteManager };
	m_pBack2->size = { 1280.0f, 720.0f };
	m_pBack2->color = { 1.3f,1.3f,1.3f,1.0f };

	//�X�e�[�W3�w�i
	m_pFront3 = new Image2D{ "Assets/2D/select/stage3_Front.png", m_pSpriteManager };	
	m_pFront3->size = { 1280.0f, 720.0f };
	m_pFront3->color = { 1.2f,1.2f,1.2f,1.0f };
	m_pGround3 = new Image2D{ "Assets/2D/select/stage3_Ground.png", m_pSpriteManager };
	m_pGround3->size = { 1280.0f, 720.0f };
	m_pGround3->color = { 1.3f,1.3f,1.3f,1.0f };
	m_pBack3 = new Image2D{ "Assets/2D/select/stage3_Back.png", m_pSpriteManager };	
	m_pBack3->size = { 1280.0f, 720.0f };
	m_pBack3->color = { 1.2f,1.2f,1.2f,1.0f };


	//���{�b�g
	m_pRobo = new Image2D{ "Assets/2D/animation/robot.png", m_pSpriteManager };
	m_pRobo->SetTexScale(4, 1);
	m_pRobo->size = { 450.0f, 450.0f };
	if (beforeScene == SCENE_TITLE) //�^�C�g�����痈���獶���猻���
	{
		isReturn = false;
		m_pRobo->pos = { -100.0f, 600.0f };
		m_targetPos = SELECT1_POS_X;
		SelectState::SetSelect(SelectState::SELECT_1);
	}
	else //�����Ă����X�e�[�W����o�Ă���
	{
		isReturn = true;
		m_pRobo->pos.y = 560.0f;

		switch ((beforeScene - 3) % 5)
		{
		case 0: { m_pRobo->pos.x = SELECT1_POS_X; SelectState::SetSelect(SelectState::SELECT_1); } break;
		case 1: { m_pRobo->pos.x = SELECT2_POS_X; SelectState::SetSelect(SelectState::SELECT_2); } break;
		case 2: { m_pRobo->pos.x = SELECT3_POS_X; SelectState::SetSelect(SelectState::SELECT_3); } break;
		case 3: { m_pRobo->pos.x = SELECT4_POS_X; SelectState::SetSelect(SelectState::SELECT_4); } break;
		case 4: { m_pRobo->pos.x = SELECT5_POS_X; SelectState::SetSelect(SelectState::SELECT_5); } break;
		}
		m_targetPos = m_pRobo->pos.x;

		m_pRobo->color.w = 0.0f;
	}


	//�o����
	m_pHole = new Image2D{ "Assets/2D/select/hole.png", m_pSpriteManager };
	m_pHole->pos.y = 550.0f;
	m_pHole->size = { 150.0f, 200.0f };



	//BGM
	m_pBGM = new BGM("Assets/BGM/Title.wav", true);
	m_pBGM->SetVolume(m_bgmVolume = 0.6f);


	//SE
	m_pSESelect		= new SE("Assets/SE/Caterpillar.wav");	//�I��
	m_pSESelect->SetVolume(0.7f);
	m_pSEDetermine	= new SE("Assets/SE/Tate_Uti.wav");		//����
	m_pSECancel		= new SE("Assets/SE/Yoko_Uti.wav");		//�L�����Z��


	//�ݒ�
	switch (beforeScene)
	{
		case SCENE_TITLE:
		case SCENE_STAGE1_1:
		case SCENE_STAGE1_2:
		case SCENE_STAGE1_3:
		case SCENE_STAGE1_4:
		case SCENE_STAGE1_5:
		{
			m_pGround1->pos	= { 640, 360 };
			m_pBack1->pos	= { 640, 360 };

			m_pFront2->pos	= { 640 + 1280, 360 };
			m_pGround2->pos	= { 640 + 1280, 360 };
			m_pBack2->pos	= { 640 + 1280, 360 };
								      
			m_pFront3->pos	= { 640 + 2560, 360 };
			m_pGround3->pos	= { 640 + 2560, 360 };
			m_pBack3->pos	= { 640 + 2560, 360 };

			m_pBGM->SetPitch(STAGE1_BGM_SPEED);

			SelectState::SetStage(SelectState::STAGE_1);
		}
		break;
		case SCENE_STAGE2_1:
		case SCENE_STAGE2_2:
		case SCENE_STAGE2_3:
		case SCENE_STAGE2_4:
		case SCENE_STAGE2_5:
		{
			m_pGround1->pos	= { 640 - 1280, 360 };
			m_pBack1->pos	= { 640 - 1280, 360 };

			m_pFront2->pos	= { 640, 360 };
			m_pGround2->pos	= { 640, 360 };
			m_pBack2->pos	= { 640, 360 };

			m_pFront3->pos	= { 640 + 1280, 360 };
			m_pGround3->pos	= { 640 + 1280, 360 };
			m_pBack3->pos	= { 640 + 1280, 360 };

			m_pBGM->SetPitch(STAGE2_BGM_SPEED);
			SelectState::SetStage(SelectState::STAGE_2);
		}
		break;
		case SCENE_STAGE3_1:
		case SCENE_STAGE3_2:
		case SCENE_STAGE3_3:
		case SCENE_STAGE3_4:
		case SCENE_STAGE3_5:
		{
			m_pGround1->pos = { 640 - 2560, 360 };
			m_pBack1->pos	= { 640 - 2560, 360 };

			m_pFront2->pos	= { 640 - 1280, 360 };
			m_pGround2->pos = { 640 - 1280, 360 };
			m_pBack2->pos	= { 640 - 1280, 360 };

			m_pFront3->pos	= { 640, 360 };
			m_pGround3->pos = { 640, 360 };
			m_pBack3->pos	= { 640, 360 };

			m_pBGM->SetPitch(STAGE3_BGM_SPEED);
			SelectState::SetStage(SelectState::STAGE_3);
		}
		break;
	}

	//�X�e�[�W���
	m_pStageNum = new Select_StageNumber(m_pSpriteManager);
	m_pScore = new Select_Score(m_pSpriteManager);
	m_pBlock = new Select_Block(m_pSpriteManager, beforeScene);

	//�Z���N�g��ʂ̃A�j���[�V����
	m_pMole = new Select_Mole(m_pSpriteManager);
	m_pBat = new Select_Bat(m_pSpriteManager);


	//�t���O������
	m_isStageChange = false;


	//�{�^������������
	isDetermine = false;
	isBack = false;


	//BGM�Đ��J�n
	m_pBGM->Start();
}



CScene_Select::~CScene_Select()
{
	delete m_pSESelect;
	delete m_pSEDetermine;
	delete m_pSECancel;

	m_pBGM->Stop();
	delete m_pBGM;

	delete m_pMole;
	delete m_pBat;
	delete m_pStageNum;
	delete m_pScore;
	delete m_pBlock;

	delete m_pGround1;
	delete m_pBack1;
	delete m_pFront2;
	delete m_pGround2;
	delete m_pBack2;
	delete m_pFront3;
	delete m_pGround3;
	delete m_pBack3;

	delete m_pRobo;
	delete m_pHole;

	delete m_pSpriteManager;
}



void CScene_Select::Update()
{
	if (AutoUpdate() == true)	//���͂��󂯕t����ꍇ
	{
		InputUpdate(); //���͎�t�������X�V
	}

	//�X�e�[�W���X�V
	m_pStageNum->Update();
	m_pScore->Update();

	//�A�j���[�V����
	m_pMole->Update();
	m_pBat->Update();
}



bool CScene_Select::AutoUpdate()
{
	bool canInput = true;	//���͎�t�t���O

	//---����{�^����������
	if (isDetermine)
	{
		//�A�j���[�V����
		m_pRobo->UpdateAnimation(2, true);

		//�����O�܂ňړ�
		if (m_pRobo->pos.y > 560.0f)
		{
			m_pRobo->pos.y -= 2.0f;
			return false;	//���͂��󂯕t���Ȃ�
		}

		//���ɓ����Č����Ȃ��Ȃ�
		if (m_pRobo->color.w >= 0.0f)
		{
			m_pRobo->color.w -= 0.05f;
			return false;	//���͂��󂯕t���Ȃ�
		}

		//�V�[���ύX
		switch (SelectState::GetStage())
		{
		case SelectState::STAGE_1:
		{
			switch ((int)m_pRobo->pos.x)
			{
			case SELECT1_POS_X: SceneChange(SCENE_STAGE1_1);	break;
			case SELECT2_POS_X: SceneChange(SCENE_STAGE1_2);	break;
			case SELECT3_POS_X: SceneChange(SCENE_STAGE1_3);	break;
			case SELECT4_POS_X: SceneChange(SCENE_STAGE1_4);	break;
			case SELECT5_POS_X: SceneChange(SCENE_STAGE1_5);	break;
			}
		}
		break;
		case SelectState::STAGE_2:
		{
			switch ((int)m_pRobo->pos.x)
			{
			case SELECT1_POS_X: SceneChange(SCENE_STAGE2_1);	break;
			case SELECT2_POS_X: SceneChange(SCENE_STAGE2_2);	break;
			case SELECT3_POS_X: SceneChange(SCENE_STAGE2_3);	break;
			case SELECT4_POS_X: SceneChange(SCENE_STAGE2_4);	break;
			case SELECT5_POS_X: SceneChange(SCENE_STAGE2_5);	break;
			}
		}
		break;
		case SelectState::STAGE_3:
		{
			switch ((int)m_pRobo->pos.x)
			{
			case SELECT1_POS_X: SceneChange(SCENE_STAGE3_1);	break;
			case SELECT2_POS_X: SceneChange(SCENE_STAGE3_2);	break;
			case SELECT3_POS_X: SceneChange(SCENE_STAGE3_3);	break;
			case SELECT4_POS_X: SceneChange(SCENE_STAGE3_4);	break;
			case SELECT5_POS_X: SceneChange(SCENE_STAGE3_5);	break;
			}
		}
		break;
		}

		return false;
	}


	//---�K�^�K�^
	if (roboUp) //RoboUp
	{
		m_pRobo->pos.y += 0.5f;
		if (m_pRobo->pos.y >= 601.0f) { roboUp = false; }
	}
	else //RoboDown
	{
		m_pRobo->pos.y -= 0.5f;
		if (m_pRobo->pos.y <= 599.0f) { roboUp = true; }
	}


	//---���{�b�g�A��
	if (isReturn)
	{
		if (m_pRobo->color.w < 1.0f)
		{
			m_pRobo->color.w += 0.05f;
			return false;
		}
		if (m_pRobo->pos.y < 600.0f)
		{
			m_pRobo->pos.y += 2.0f;
			return false;
		}

		//�A�j���[�V����
		m_pRobo->UpdateAnimation(2, true);

		isReturn = false;
		canInput = false;
	}



	//--- ���{�b�g���E�ړ�
	if (m_pRobo->pos.x != m_targetPos)
	{
		//�E�Ɉړ�
		if (m_pRobo->pos.x < m_targetPos)
		{
			MoveRight(15.0f, m_pRobo);
			if (m_pRobo->pos.x > m_targetPos) { m_pRobo->pos.x = m_targetPos; }
		}

		//���Ɉړ�
		if (m_pRobo->pos.x > m_targetPos)
		{
			MoveLeft(15.5f, m_pRobo);
			if (m_pRobo->pos.x < m_targetPos) { m_pRobo->pos.x = m_targetPos; }

			if (m_pRobo->pos.x <= -200.0f) { SceneChange(SCENE_TITLE); }	//�߂�{�^���Ŗ߂�����^�C�g����ʂ�
		}

		//�A�j���[�V����
		m_pRobo->UpdateAnimation(2, true);

		canInput = false;	//���͂��󂯕t���Ȃ�
	}


	//--- �X�e�[�W���E�ړ�
	if (m_isStageChange)
	{
		//�O�̃X�e�[�W�ɖ߂�
		if (m_targetPos == SELECT5_POS_X)
		{
			MoveRight(20.0f, m_pGround1, m_pBack1, m_pFront2, m_pGround2, m_pBack2, m_pFront3, m_pGround3, m_pBack3); //�w�i�摜��S��������

			//BGM�̃t�F�[�h
			if(m_pRobo->pos.x <= 640.0f)
			{
				m_pBGM->SetVolume(m_bgmVolume -= 0.02f);
			}
			else if (m_bgmVolume < 0.6f)
			{
				m_pBGM->SetVolume(m_bgmVolume += 0.02f);
			}
			
			//�w�i�摜�����S�܂ŗ�����~�܂�
			switch (SelectState::GetStage())
			{
			case SelectState::STAGE_1:
			{
				if (m_pRobo->pos.x >= 640.0f)
				{
					m_pBGM->SetPitch(STAGE1_BGM_SPEED);
				}

				if (m_pGround1->pos.x >= 640)
				{
					m_isStageChange = false;
					m_pBGM->SetVolume(m_bgmVolume = 0.6f);
				}
			}
			break;
			case SelectState::STAGE_2:
			{
				if (m_pRobo->pos.x >= 640.0f)
				{
					m_pBGM->SetPitch(STAGE2_BGM_SPEED);
				}

				if (m_pFront2->pos.x >= 640)
				{
					m_isStageChange = false;
					m_pBGM->SetVolume(m_bgmVolume = 0.6f);
				}
			}
			break;
			}
		}


		//���̃X�e�[�W�ɐi��
		if (m_targetPos == SELECT1_POS_X)
		{
			MoveLeft(20.0f, m_pGround1, m_pBack1, m_pFront2, m_pGround2, m_pBack2, m_pFront3, m_pGround3, m_pBack3); //�w�i�摜��S��������
			
			//BGM�̃t�F�[�h
			if (m_pRobo->pos.x >= 640.0f)
			{
				m_pBGM->SetVolume(m_bgmVolume -= 0.02f);
			}
			else if (m_bgmVolume < 0.6f)
			{
				m_pBGM->SetVolume(m_bgmVolume += 0.02f);
			}

			//�w�i�摜�����S�܂ŗ�����~�܂�
			switch (SelectState::GetStage())
			{
			case SelectState::STAGE_2:
			{
				if (m_pRobo->pos.x <= 640.0f)
				{
					m_pBGM->SetPitch(STAGE2_BGM_SPEED);
				}

				if (m_pFront2->pos.x <= 640)
				{
					m_isStageChange = false;
					m_pBGM->SetVolume(m_bgmVolume = 0.6f);
				}
			}
			break;
			case SelectState::STAGE_3:
			{
				if (m_pRobo->pos.x <= 640.0f)
				{
					m_pBGM->SetPitch(STAGE3_BGM_SPEED);
				}

				if (m_pFront3->pos.x <= 640)
				{
					m_isStageChange = false;
					m_pBGM->SetVolume(m_bgmVolume = 0.6f);
				}
			}
			break;
			}
		}

		return false;
	}


	//�u���b�N����
	if (!m_pBlock->BreakBlock())
	{
		return false;
	}

	return canInput;
}



void CScene_Select::InputUpdate()
{
	DirectX::XMFLOAT2 Keypos = GetPressStick();

	//Enter�L�[�������ꂽ��X�e�[�W�ɓ���
	if (IsKeyPress(VK_RETURN) || InputPressKey(LEFT_TRIGGER) || InputPressKey(A_BUTTON))
	{
		if (m_pBlock->IsPlayable())
		{
			isDetermine = true;

			//���艹
			m_pSEDetermine->Play();
			return;
		}
	}


	//ESC�L�[�������ꂽ��^�C�g���ɖ߂�
	if (IsKeyPress(VK_ESCAPE) || InputPressKey(BACK_BUTTON) || InputPressKey(B_BUTTON))
	{
		isBack = true;
		m_targetPos = -200.0f;
		m_pRobo->Reverse(true, false);

		m_pSECancel->Play();
		return;
	}


	//���E�������͂��Ă��牽�����Ȃ�
	if (IsKeyPress(VK_LEFT) && IsKeyPress(VK_RIGHT) || (InputPressKey(LEFT_BUTTON) && InputPressKey(RIGHT_BUTTON))
		|| (InputPressKey(LEFT_STICK) && Keypos.x < 0.0f && Keypos.x > 0.0f)) { return; }


	//������
	if (IsKeyPress(VK_LEFT) || InputPressKey(LEFT_BUTTON) 
		|| (InputPressKey(LEFT_STICK) && Keypos.x < 0.0f))
	{
		switch ((int)m_pRobo->pos.x)
		{
		case SELECT1_POS_X:
		{
			if (SelectState::GetStage() != SelectState::STAGE_1)
			{
				m_targetPos = SELECT5_POS_X;
				SelectState::SetSelect(SelectState::SELECT_5); 

				m_isStageChange = true;	//�X�e�[�W�ύX���ɂ���
				SelectState::SetStage((SelectState::STAGE)(SelectState::GetStage() - 1));	//�I�𒆂̃X�e�[�W��ύX
			}
			else return;
		}
		break;

		case SELECT2_POS_X: { m_targetPos = SELECT1_POS_X; SelectState::SetSelect(SelectState::SELECT_1); }	break;
		case SELECT3_POS_X: { m_targetPos = SELECT2_POS_X; SelectState::SetSelect(SelectState::SELECT_2); }	break;
		case SELECT4_POS_X: { m_targetPos = SELECT3_POS_X; SelectState::SetSelect(SelectState::SELECT_3); }	break;
		case SELECT5_POS_X: { m_targetPos = SELECT4_POS_X; SelectState::SetSelect(SelectState::SELECT_4); }	break;
		}

		//���{�b�g���������ɂ���
		m_pRobo->Reverse(true, false);

		//�ړ����鉹
		m_pSESelect->Play();
	}


	//�E����
	if (IsKeyPress(VK_RIGHT) || InputPressKey(RIGHT_BUTTON)
		|| (InputPressKey(LEFT_STICK) && Keypos.x > 0.0f))
	{
		switch ((int)m_pRobo->pos.x)
		{
		case SELECT1_POS_X: { m_targetPos = SELECT2_POS_X; SelectState::SetSelect(SelectState::SELECT_2); }	break;
		case SELECT2_POS_X: { m_targetPos = SELECT3_POS_X; SelectState::SetSelect(SelectState::SELECT_3); }	break;
		case SELECT3_POS_X: { m_targetPos = SELECT4_POS_X; SelectState::SetSelect(SelectState::SELECT_4); }	break;
		case SELECT4_POS_X: { m_targetPos = SELECT5_POS_X; SelectState::SetSelect(SelectState::SELECT_5); }	break;

		case SELECT5_POS_X:
		{
			if (SelectState::GetStage() != SelectState::STAGE_3)
			{
				m_targetPos = SELECT1_POS_X;
				SelectState::SetSelect(SelectState::SELECT_1);

				m_isStageChange = true;	//�X�e�[�W�ύX���ɂ���
				SelectState::SetStage((SelectState::STAGE)(SelectState::GetStage() + 1));	//�I�𒆂̃X�e�[�W��ύX
			}
			else return;
		}
		break;
		}

		//���{�b�g���E�����ɂ���
		m_pRobo->Reverse(false, false);

		//�ړ����鉹
		m_pSESelect->Play();
	}
}



void CScene_Select::Draw()
{
	EnableDepth(false);

	//�w�i
	m_pBack1->Draw();
	m_pBack2->Draw();
	m_pBack3->Draw();

	if (!m_isStageChange)
	{
		//����
		m_pHole->pos.x = SELECT1_POS_X; m_pHole->Draw();
		m_pHole->pos.x = SELECT2_POS_X; m_pHole->Draw();
		m_pHole->pos.x = SELECT3_POS_X; m_pHole->Draw();
		m_pHole->pos.x = SELECT4_POS_X; m_pHole->Draw();
		m_pHole->pos.x = SELECT5_POS_X; m_pHole->Draw();
	}

	//����
	m_pGround1->Draw();
	m_pGround2->Draw();
	m_pGround3->Draw();

	if (!m_isStageChange)
	{
		//�ǂ���
		m_pBlock->Draw();

		//�A�j���[�V����
		m_pMole->BeyondDraw();
	}

	//���{�b�g
	m_pRobo->Draw();
	
	if (!m_isStageChange)
	{
		//�X�e�[�W���
		m_pScore->Draw();

		//�A�j���[�V����
		m_pMole->FrontDraw();
		m_pBat->Draw();

		m_pStageNum->Draw();
	}
	else
	{
		m_pBat->ResetPos();
	}

	//��O��
	m_pFront2->Draw();
	m_pFront3->Draw();
}




template<class T, class... args> 
void MoveLeft(float speed, T image, args... images)
{
	image->pos.x -= speed;
	MoveLeft(speed, images...);
}

template<class T>
void MoveLeft(float speed, T image)
{
	image->pos.x -= speed;
}



template<class T, class... args>
void MoveRight(float speed, T image, args... images)
{
	image->pos.x += speed;
	MoveRight(speed, images...);
}

template<class T>
void MoveRight(float speed, T image)
{
	image->pos.x += speed;
}