//#pragma once
#ifndef CAMERAMANAGER_GAME_H
#define CAMERAMANAGER_GAME_H
#include "Camera_Manager.h"
#include "StageBase.h"

class C_Camera_Game : public C_CameraManager
{
public:
	C_Camera_Game(SCENE_CAMERA_TYPE NowType,Stage_Base* pStage);
	~C_Camera_Game();
};

#endif // !CAMERAMANAGER_GAME_H
