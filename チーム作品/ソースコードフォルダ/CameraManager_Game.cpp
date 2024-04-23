#include "CameraManager_Game.h"
#include "CameraDebug.h"
#include "CameraAdmission.h"
#include "CameraMain.h"
#include "CameraWorld.h"
#include "CameraPile.h"
#include "CameraClear.h"
#include "CameraMiss.h"

C_Camera_Game::C_Camera_Game(SCENE_CAMERA_TYPE NowType, Stage_Base* pStage)
	:C_CameraManager(NowType)
{
	m_pCameraIndex = new CameraBase*[C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_END]{nullptr};

	//ÉJÉÅÉâÇäeé©çÏÇ¡ÇƒÇ¢Ç≠---------------------------------------------------------
	m_pCameraIndex[_CAMERA_GAME_DEBUG] = new CameraDebug();
	m_pCameraIndex[_CAMERA_GAME_ADMISSION] = new CameraAdmission(pStage);
	m_pCameraIndex[_CAMERA_GAME_MAIN] = new CameraMain(pStage);
	m_pCameraIndex[_CAMERA_GAME_WORLD] = new CameraWorld(pStage);
	m_pCameraIndex[_CAMERA_GAME_PILE] = new CameraPile(pStage);
	m_pCameraIndex[_CAMERA_GAME_CLEAR] = new CameraClear(pStage);
	m_pCameraIndex[_CAMERA_GAME_MISS] = new CameraMiss(pStage);
	//-------------------------------------------------------------------------------

	//ç≈èâÇÃÉJÉÅÉâèÓïÒ
	m_pSceneCamera = m_pCameraIndex[NowType];
}
C_Camera_Game::~C_Camera_Game()
{
	for (int i = 0; i < _CAMERA_GAME_END; i++)
	{
		if (m_pCameraIndex[i] != nullptr)
		{
			delete m_pCameraIndex[i];
		}
	}

	if (m_pCameraIndex != nullptr)
	{
		delete m_pCameraIndex;
	}
}