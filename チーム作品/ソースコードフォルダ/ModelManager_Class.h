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
		Model *model;			//���f���������Ă����ϐ�
		std::map<std::string,Model::AnimeNo> Animetion;	//�A�j���[�V������o�^
		bool AnimeNow = false;
	};

public:
	CModelManager(CameraBase** Model_pCamera);
	~CModelManager();

	static void c_ModelManager_Init();
	static void c_ModelManager_Uninit();
	static void c_AddModel(const std::string CharName, const char* FileName);			//���f����ǉ�����
	static void c_AddModel(const std::string CharName, const char* FileName,const char* TextureName);			//���f����ǉ�����
	static void c_AddAnimetion(const std::string AnimeName,const char* AnimeFileName, const std::string CharName,float StartFrames = 0.0f);		//�A�j���[�V������ǉ�����
	static void c_SetAnimetion(const std::string CharName, const std::string AnimeName, bool Repeat);
	static void c_AllDelete();			//�S�Ẵ��f����������
	void c_ModelDraw(const std::string CharName);	//�J�������Ⴄ����ÓI�ł͂Ȃ�
	void c_ModelDraw(const std::string CharName, float PosX, float PosY, float PosZ, float ScaleX, float ScaleY, float ScaleZ, float AngleX, float AngleY, float AngleZ);
	void c_SetCamera(CameraBase* NewPointer);
	CameraBase* c_GetCamera();

private:
	CameraBase** m_ppCamera;
	//�A�z�z��
	static std::map < std::string, c_MODEL_INFORMATION> m_Model_Information;
	static VertexShader* m_pVS_ModelManager;		//���_�V�F�[�_�[
	static ConstantBuffer* m_pWVP_ModelManager;	//�萔�o�b�t�@�[
};
#endif // !MODELMANAGER_CLASS_H

