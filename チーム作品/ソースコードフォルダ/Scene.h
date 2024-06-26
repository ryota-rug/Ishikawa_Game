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
	SpriteManager* m_pSpriteManager;			//描画関係
	CModelManager* m_ModelManager;				//モデル情報
	C_CameraManager* m_pCameraManager;			//カメラ情報をまとめたやつ
};

#endif // !SCENE_H



