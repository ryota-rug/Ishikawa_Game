#include "Scene_Stage3_2.h"
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


CStage3_2::CStage3_2()
{
	SetStageScene(SCENE::SCENE_STAGE3_2);

	const int X = 7, Y = 8;
	int BlockInfo[X * Y] =
	{
		 4, 4, 4, 4, 4, 4, 4,
		 3, 3, 2, 2, 2, 2, 2,
		 2, 3, 2, 2, 3, 2, 2,
		 3, 3, 2,10, 2, 2, 2,
		10, 2, 2,10, 3, 2, 2,
		 2, 2, 2, 2, 2, 2, 2,
		 2, 2, 2, 2, 2, 2, 2,
		 2, 2, 2, 2, 2, 2, 2,
	};

	int JewelyInfo[X * Y] =
	{
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
	};

	int HeetInfo[X * Y] =
	{
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		2, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 0, 0, 0, 2,
		2, 0, 0, 0, 0, 0, 2,
	};

	CreateStage(X, Y, BlockInfo, JewelyInfo, HeetInfo, true);
	SetBGM("Assets/BGM/Stage3.wav");
	SetBackGround(BACKOBJECT::AREA_3);
	//ëÄçÏê‡ñæâÊëú
	SetTutorialImage("Assets/2D/tutorial/tutorial3.png");

	//ÉQÅ[ÉÄèÛë‘ÇÃê›íË
	SetState(GAME_STATE::STATE1_STARTEVENT);
}


CStage3_2::~CStage3_2()
{
	
}
