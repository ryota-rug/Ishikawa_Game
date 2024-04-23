#include "Scene_Stage1_3.h"
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

CStage1_3::CStage1_3()
{
	SetStageScene(SCENE::SCENE_STAGE1_3);

	const int X = 5, Y = 8;
	int BlockInfo[X * Y] =
	{
		4, 4, 4, 4, 4,
		8, 2, 2, 2, 2,
		8, 2, 2, 2, 2,
		8, 2, 2, 8, 2,
		2, 6, 2, 2, 2,
		2, 6, 6, 2, 2,
		2, 6, 2, 2, 2,
		2, 2, 2, 2, 2,
	};

	int JewelyInfo[X * Y] =
	{
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
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

	//ÉQÅ[ÉÄèÛë‘ÇÃê›íË
	SetState(GAME_STATE::STATE1_STARTEVENT);
}

CStage1_3::~CStage1_3()
{

}
