#include "Scene_Stage2_3.h"
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

CStage2_3::CStage2_3()
{
	SetStageScene(SCENE::SCENE_STAGE2_3);
	const int X = 7, Y = 8;
	int BlockInfo[X * Y] =
	{
		4, 4, 4, 4, 4, 4, 4,
		9, 1, 1, 1, 2, 1, 8,
		1, 2, 2, 2, 5, 2, 2,
		1, 2, 8, 2, 2, 2, 2,
		1, 2, 2, 2, 2, 2, 2,
		1, 2, 9, 2, 2, 2, 8,
		1, 2, 2, 2, 2, 2, 3,
		1, 2, 2, 2, 2, 2, 3,
	};

	int JewelyInfo[X * Y] =
	{
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0,
		0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
	};

	int HeetInfo[X * Y] =
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
	};

	CreateStage(X, Y, BlockInfo, JewelyInfo, HeetInfo, true);
	SetBGM("Assets/BGM/Stage2.wav");
	SetBackGround(BACKOBJECT::AREA_2);
	//ëÄçÏê‡ñæâÊëú
	SetTutorialImage("Assets/2D/tutorial/tutorial2.png");

	//ÉQÅ[ÉÄèÛë‘ÇÃê›íË
	SetState(GAME_STATE::STATE1_STARTEVENT);
}


CStage2_3::~CStage2_3()
{
	
}
