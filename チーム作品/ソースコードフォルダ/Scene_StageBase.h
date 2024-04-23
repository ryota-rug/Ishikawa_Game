#pragma once
#include "Scene.h"
#include "StageBase.h"
#include "ModelManager_Class.h"
#include "Sound.h"

#include "GameClearEvent.h"
#include "GameStartEvent.h"
#include "GameOverEvent.h"
#include "GamePause.h"
#include "GameOver.h"
#include "GameClear.h"

#include "Image2D.h"

#include "KnockUI.h"
#include "BreakNumUI.h"
#include "UI_OverPeople.h"
#include "UI_Tutorial.h"

#include "ObjectRenderer.h"

class Scene_StageBase : public CScene
{
protected:
	enum GAME_STATE
	{
		STATE0_TUTORIAL,	//��������\��
		STATE1_STARTEVENT,	//�Q�[���J�n�A�j��
		STATE2_GAME,		//�Q�[�����
		STATE3_PAUSE,		//�|�[�Y���
		STATE4_CLEARANIME,	//�Q�[���N���A�A�j��
		STATE5_CLEAR,		//�N���A���
		STATE6_OVERANIME,	//�Q�[���I�[�o�[�A�j��
		STATE7_GAMEOVER,	//�Q�[���I�[�o�[���
		STATE8_LASTCLEAR,	//���ׂăN���A�����Ƃ��̉��
		STATEMAX,
	};	//�Q�[����ʂ̏��

	enum BACKOBJECT
	{
		AREA_1 = 0,
		AREA_2,
		AREA_3,
		MAX
	};

public:
	Scene_StageBase();
	~Scene_StageBase() override;
	void Update() override;
	void Draw() override;

protected:

	//�X�e�[�W�������֌W
	void CreateStage(int Width, int Height, int* BlockMapData,int* JewelyMapData,int* HeetMapData,bool usePilebanker);	//�X�e�[�W�̍쐬
	void SetState(GAME_STATE nextState);						//���̏����̐ݒ�
	void SetBGM(std::string bgmName);							//BGM�̐ݒ�
	void SetStageScene(SCENE nowScene);							//���̃V�[�������Ԗڂ̃X�e�[�W�Ȃ̂��ݒ�
	void SetBackGround(BACKOBJECT area);						//�w�i�I�u�W�F�N�g�̐ݒ�
	void SetTutorialImage(const char* Filepath);				//�`���[�g���A���Ɏg���摜�̐ݒ�
	void SetLastStage();										//�Ō�̃X�e�[�W�̎��ɌĂԊ֐�

	//�A�b�v�f�[�g�֌W
	virtual void UpdateTutorial();								//�`���[�g���A��
	virtual void UpdateStartEvent();							//�X�e�[�W�J�n�C�x���g
	virtual void UpdateGame();									//�Q�[��
	virtual void UpdatePause();									//�|�[�Y
	virtual void UpdateClearAnime();							//�N���A�����Ƃ��̃C�x���g
	virtual void UpdateOverAnime();								//�I�[�o�[�����Ƃ��̃C�x���g
	virtual void UpdateClear();									//�N���A�̑I��
	virtual void UpdateOver();									//�I�[�o�[�̑I��
	virtual void UpdateLastStageClear();						//�ŏI�X�e�[�W�̃N���A������̃C�x���g

	//�`��֌W
	virtual void DrawTutorial();
	virtual void DrawStartEvent();
	virtual void DrawGame();
	virtual void DrawPause();
	virtual void DrawClearAnime();
	virtual void DrawOverAnime();
	virtual void DrawClear();
	virtual void DrawOver();
	virtual void DrawLastStageClear();

private:
	Stage_Base* m_pStage = nullptr;
	GAME_STATE m_gameState;
	SCENE m_NowScene;
	SCENE m_NextScene;
	SaveElea m_SaveSlot;
	bool m_bLastStage = false;

	BGM* m_pBGM = nullptr;

	ObjectRenderer* m_pBackObject = nullptr;

	Game_StartEvent* m_pGameStartEvent = nullptr;
	GameClearEvent* m_pGameClearEvent = nullptr;
	GameOverEvent* m_pGameOverEvent = nullptr;
	GamePause* m_pGamePause = nullptr;
	GameClear* m_pGameClear = nullptr;
	GameOver* m_pGameOver = nullptr;

	//�摜
	Image2D* m_pPauseBack = nullptr;
	Image2D* m_pGameBack = nullptr;
	Image2D* m_pInf = nullptr;
	Image2D* m_pAllClearImage = nullptr;	//�S�N���A�����Ƃ��̉摜������
	Image2D* m_pButton = nullptr;			//�S�N���A�����Ƃ��̃{�^���摜
	float m_Alpha = 0.0f;
	UI_OverPeople* m_pPeople = nullptr;
	UI_Tutorial* m_pTutorial = nullptr;

protected:
	SaveData m_SaveData;
};