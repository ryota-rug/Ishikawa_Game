//#pragma once
#ifndef BLOCK_BASE_H
#define BLOCK_BASE_H
#include "StageBase.h"
#include "Position_struct.h"
#include "CameraBase.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"

#define ADDMODEL_SENDDATA(name, path) { m_pModelManager->c_AddModel(name, path); }
#define MODELDRAW_SENDDATA(name, pos, size, angle) { m_pModelManager->c_ModelDraw(name, pos.X, pos.Y, pos.Z, size.X, size.Y, size.Z, angle[0], angle[1], angle[2]); }

class Stage_Base;

class Block_Base
{
public:
	enum BLOCK_TYPE
	{
		BLOCK_NONE = 0,	 //�u���b�N����

		BLOCK_CLAY,		 // �S�y
		BLOCK_SOIL,		 // �y
		BLOCK_STONE,	 // ��
		BLOCK_CONCRETE,	 // �R���N���[�g
		BLOCK_BEDROCK,	 // ���
		BLOCK_SAND,		 // ��
		BLOCK_ICE,		 // �X
		BLOCK_WATER,	 // ��
		BLOCK_MAGMA,	 // �}�O�}
		BLOCK_GAS,		 // �K�X
		BLOCK_INVINCIBLE,// ���G
		BLOCK_JEWELY,	 // ���
		BLOCK_MAX
	};

public:
	static const float BlockSize;	//�������̃u���b�N�̃T�C�Y
	Block_Base(Stage_Base* MyStage,int PosX,int PosY);
	virtual ~Block_Base();
	virtual void Update();
	virtual void Draw();
	virtual void Update_Refuge();

	BLOCK_TYPE GetType();
	int GetHP();
	int GetDEF();
	int Damage(int Num);
	IntPos GetMap();
	FloatPos GetPos();
	void SetMap(int X,int Y);
	void SetPos(float X, float Y,float Z);
	void Destroy();
	bool Get_Invincibility();		//���G����
	bool Get_Slipped();				//���蔲������
	virtual void CollisionNavigate();	//�Y�����̃u���b�N�ɓ��������Ƃ��ɌĂ΂��
	void CollisionBrock();
	void Set_DidUpdate(bool Set);				//�A�b�v�f�[�g���邩
	bool Get_DidUpdate();			//���̃t���[���ŃA�b�v�f�[�g������
	bool Get_Destroy();
	void Set_ModelManager(CModelManager* pModelManager);
	void Set_CameraManager(C_CameraManager* pCameraManager);

private:
	bool m_DidUpdate;

protected:
	BLOCK_TYPE m_Type;		//�u���b�N�̎��
	Stage_Base* m_pMyStage;
	int m_HP;				//�ϋv�l
	int m_DEF;				//�͌����l
	IntPos m_MapPos;		//�}�b�v���
	FloatPos m_DrawPos;		//�`�悷��|�W�V����
	bool m_IsDestroy;
	CameraBase* m_pCamera;
	bool m_Invincibility;	//���G
	bool m_Slipped;			//���蔲��
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
};


#endif // !BLOCK_BASE_H
