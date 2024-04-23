//#pragma once
#ifndef MODELMANAGER_CLASS_H
#define MODELMANAGER_CLASS_H
#include "Model.h"
#include <map>
#include <string>
#include "CameraBase.h"
#include  "ConstantBuffer.h"
class CModelManager
{
public:
	struct c_MODEL_INFORMATION
	{
		Model *model;			//モデル情報を入れておく変数
		std::map<std::string,Model::AnimeNo> Animetion;	//アニメーションを登録
		bool AnimeNow = false;
	};

public:
	CModelManager(CameraBase** Model_pCamera);
	~CModelManager();

	static void c_ModelManager_Init();
	static void c_ModelManager_Uninit();
	static void c_AddModel(const std::string CharName, const char* FileName);			//モデルを追加する
	static void c_AddModel(const std::string CharName, const char* FileName,const char* TextureName);			//モデルを追加する
	static void c_AddAnimetion(const std::string AnimeName,const char* AnimeFileName, const std::string CharName,float StartFrames = 0.0f);		//アニメーションを追加する
	static void c_SetAnimetion(const std::string CharName, const std::string AnimeName, bool Repeat);
	static void c_AllDelete();			//全てのモデル情報を消す
	void c_ModelDraw(const std::string CharName);	//カメラが違うから静的ではない
	void c_ModelDraw(const std::string CharName, float PosX, float PosY, float PosZ, float ScaleX, float ScaleY, float ScaleZ, float AngleX, float AngleY, float AngleZ);
	void c_SetCamera(CameraBase* NewPointer);
	CameraBase* c_GetCamera();

private:
	CameraBase** m_ppCamera;
	//連想配列
	static std::map < std::string, c_MODEL_INFORMATION> m_Model_Information;
	static VertexShader* m_pVS_ModelManager;		//頂点シェーダー
	static ConstantBuffer* m_pWVP_ModelManager;	//定数バッファー
};
#endif // !MODELMANAGER_CLASS_H

