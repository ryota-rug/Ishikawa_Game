#include "Scene_Stage1_1.h"
#include "Timer.h"
#include "Game3D.h"
#include "Geometory.h"
#include "CameraDebug.h"
#include "DebugConsole.h"
#include "PileBankerBase.h"
#include "StageBase.h"
#include "Camera_Manager.h"
#include "CameraManager_Game.h"
#include "Input.h"
#include "Effect_Manager.h"
#include "CameraStartEvent.h"
#include "XboxKeyboard.h"
#include "BillBoard.h"

CStage1_1::CStage1_1()
{
	SetStageScene(SCENE::SCENE_STAGE1_1);

	const int X = 5, Y = 8;
	int BlockInfo[X * Y] =
	{
		4, 4, 4, 4, 4,
		2, 2, 2, 2, 2,
		2, 2, 2, 2, 2,
		2, 2, 2, 3, 2,
		2, 2, 2, 2, 2,
		2, 2, 2, 2, 2,
		2, 2, 2, 2, 2,
		2, 2, 2, 2, 2
	};

	int JewelyInfo[X * Y] =
	{
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 0,
	};

	int HeetInfo[X * Y] =
	{
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,

	};


	CreateStage(X, Y, BlockInfo, JewelyInfo, HeetInfo, false);
	SetBGM("Assets/BGM/Stage1.wav");
	SetBackGround(BACKOBJECT::AREA_1);
	//ëÄçÏê‡ñæâÊëú
	SetTutorialImage("Assets/2D/tutorial/tutorial1.png");

	//ÉQÅ[ÉÄèÛë‘ÇÃê›íË
	if(!m_SaveData.AgainStage)
	{
		SetState(GAME_STATE::STATE0_TUTORIAL);
	}
	else
	{
		SetState(GAME_STATE::STATE1_STARTEVENT);
	}

}

CStage1_1::~CStage1_1()
{

}
