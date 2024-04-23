//#pragma once
#ifndef H_CAMERA_MANAGER
#define H_CAMERA_MANAGER

#include "CameraBase.h"
#include "CameraEvent.h"
#include <DirectXMath.h>
#include "Position_struct.h"

class C_CameraManager
{
public:

	//�����ɃJ�����̏�������Ă���
	enum SCENE_CAMERA_TYPE
	{
		_CAMERA_TITLE_FIRST = -1,
		_CAMERA_TITLE_END,
		
		_CAMERA_GAME_FIRST = -1,
		_CAMERA_GAME_ADMISSION,	//�@�@�@����J�������[�N
		_CAMERA_GAME_MAIN,		//�A�[�@�Q�[�����̃v���C���[��������{(R�X�e�B�b�N�ɂ��㉺�ړ�)
		_CAMERA_GAME_WORLD,		//�A�[�A�S�̂�������(R�g���K�[�������Ă����)
		_CAMERA_GAME_PILE,		//�B �@�p�C���o���J�[�ɂ��Ă���(�ł��t������)
		_CAMERA_GAME_CLEAR,		//�C�[�@�N���A��̃_���X�{�ޏ�J�������[�N
		_CAMERA_GAME_MISS,		//�C�[�A�Q�[���I�[�o�[�̃A�j���[�V�����p
		_CAMERA_GAME_STARTEVENT,
		
		_CAMERA_GAME_DEBUG,
		_CAMERA_GAME_END,
		_CAMERA_ALL_FIRST = 100,
		_CAMERA_ALL_EVENT,
		
	};

public:
	C_CameraManager(SCENE_CAMERA_TYPE NowType);	//�p���������Index�����
	virtual ~C_CameraManager();
	void Update();
	void AddCamera(SCENE_CAMERA_TYPE AddType,CameraBase* AddCamera);
	CameraBase** Get_SceneCamera();					//�J�����|�C���^�[�̃A�h���X�����炤
	CameraBase* Get_NowCamera();					//���̃J�����̏������炤
	SCENE_CAMERA_TYPE Get_NowType();					//���̃J�����̃^�C�v�����炤
	CameraBase* Get_TypeCamera(SCENE_CAMERA_TYPE Type);	//���ꂽ�^�̃J��������������Ă���
	void ChangeTypeCamera(SCENE_CAMERA_TYPE NextType);	//���̃t���[���ň����J�������w��
	void ChangeEventCamera(SCENE_CAMERA_TYPE NextType, DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float time);
	void ChangeCameraNew(SCENE_CAMERA_TYPE NextType, DirectX::XMFLOAT3 YetPos, DirectX::XMFLOAT3 YetLook);
	CameraBase** Get_CameraIndex();					//�J�������܂Ƃ߂��z��������Ă���(�Ƃ肠������������Ǒ����g���)
	DirectX::XMFLOAT2 ChangeScreenPos(FloatPos _3DPos);
	DirectX::XMFLOAT2 ChangeScreenPos(DirectX::XMFLOAT3 _3DPos);

protected:
	bool m_ChangeNow;				//�J������񂪍��̃t���[���ŕς�����
	CameraBase* m_pSceneCamera;		//�V�[���̃J�����̏��A���̒���ς��邱�ƂŃJ������؂�ւ���
	CameraBase** m_pCameraIndex;	//�J�����̏����܂Ƃ߂��ϐ��A�p����������ɍ��
	CameraEvent m_EventCamera;
	SCENE_CAMERA_TYPE m_NowType;		//���̃J����
	SCENE_CAMERA_TYPE m_NextType;		//���̃J����
};


#endif // !H_CAMERA_MANAGER
