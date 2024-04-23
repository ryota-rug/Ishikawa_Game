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
	SpriteManager* m_pSpriteManager;			//�`��֌W
	CModelManager* m_ModelManager;				//���f�����
	C_CameraManager* m_pCameraManager;			//�J���������܂Ƃ߂����
};

#endif // !SCENE_H



