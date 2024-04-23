#include "Scene_Stage3_4.h"
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

CStage3_4::CStage3_4()
{
	SetStageScene(SCENE::SCENE_STAGE3_4);

	const int X = 7, Y = 8;
	int BlockInfo[X * Y] =
	{
		4, 4, 4, 4, 4, 4, 4,
		2, 2, 9, 3, 2, 8, 2,
		7, 2, 2, 2, 2, 5, 2,
		2, 2, 2,10, 5, 5, 2,
		6, 2, 2,10, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2
	};

	int JewelyInfo[X * Y] =
	{
		0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
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
		0, 2, 0, 0, 2, 2, 2,
		0, 2, 0, 0, 0, 0, 0,
		0, 2, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
	};


	CreateStage(X, Y, BlockInfo, JewelyInfo, HeetInfo, true);
	SetBGM("Assets/BGM/Stage3.wav");
	SetBackGround(BACKOBJECT::AREA_3);
	//ëÄçÏê‡ñæâÊëú
	SetTutorialImage("Assets/2D/tutorial/tutorial3.png");

	//ÉQÅ[ÉÄèÛë‘ÇÃê›íË
	SetState(GAME_STATE::STATE1_STARTEVENT);
}

CStage3_4::~CStage3_4()
{

}
