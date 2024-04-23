//#pragma once
#ifndef SCENE_H
#define SCENE_H
#include "CameraBase.h"
#include "SpriteManager.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"

class CScene
{
public :



public :
	CScene();
	virtual ~CScene();
	virtual void Update();
	virtual void Draw();
	virtual void ChangeCamera();
protected:
	SpriteManager* m_pSpriteManager;			//•`‰æŠÖŒW
	CModelManager* m_ModelManager;				//ƒ‚ƒfƒ‹î•ñ
	C_CameraManager* m_pCameraManager;			//ƒJƒƒ‰î•ñ‚ğ‚Ü‚Æ‚ß‚½‚â‚Â
};

#endif // !SCENE_H



