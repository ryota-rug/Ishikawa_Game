#include "Scene_Stage3_5.h"
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

CStage3_5::CStage3_5()
{
	SetStageScene(SCENE::SCENE_STAGE3_5);

	const int X = 9, Y = 8;
	int BlockInfo[X * Y] =
	{
		2, 2, 2, 2, 2, 2, 2, 2, 2,
		8, 2, 3, 2, 9, 3, 7, 2, 1,
		1,10, 2, 2, 2, 2, 2, 3, 2,
		1,10, 2, 2, 2, 2,10, 3, 2,
		1, 3, 2, 2, 2, 2,10, 3, 2,
		1, 3, 2, 2, 2, 2, 2, 3, 1,
		1, 3, 2, 2, 2, 2, 2, 3, 1,
		1, 3, 2, 2, 2, 2, 2, 3, 1
	};

	int JewelyInfo[X * Y] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 1, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	int HeetInfo[X * Y] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 2,
		0, 0, 0, 2, 2, 2, 0, 0, 2,
		0, 0, 2, 0, 0, 0, 0, 0, 2,
		0, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
	};


	CreateStage(X, Y, BlockInfo, JewelyInfo, HeetInfo, true);
	SetBGM("Assets/BGM/Stage3.wav");
	SetBackGround(BACKOBJECT::AREA_3);
	//操作説明画像
	SetTutorialImage("Assets/2D/tutorial/tutorial3.png");
	//ゲーム状態の設定
	SetState(GAME_STATE::STATE1_STARTEVENT);
	
	//これが最後のステージなのを設定する
	SetLastStage();
}

CStage3_5::~CStage3_5()
{

}
