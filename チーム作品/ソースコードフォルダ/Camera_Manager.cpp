#include "Camera_Manager.h"

//�p�������R���X�g���N�^�Ńu���b�N�̔z������
C_CameraManager::C_CameraManager(SCENE_CAMERA_TYPE NowType)
	:m_ChangeNow(false)				//���̃t���[���ŕς��邩�ۂ�
	,m_pSceneCamera(nullptr)		//�p��������ɍ����^�ɂ���č��
	,m_pCameraIndex(nullptr)		//�p��������ɍ��
	,m_NowType(NowType)				//���̌^
{

}

C_CameraManager::~C_CameraManager()
{

}

void C_CameraManager::Update()
{
	//�J�����̃A�b�v�f�[�g
	m_pSceneCamera->Update();

	//�J�����C�x���g�������ꍇ
	if (m_NowType == _CAMERA_ALL_EVENT)
	{
		if (m_EventCamera.IsEvent())
		{
			m_ChangeNow = true;
		}
	}

	//�C�x���g�J�����̏ꍇ
	if(m_ChangeNow)
	{
		//�^��ς���
		m_NowType = m_NextType;
		//�J�����̏�������
		m_pSceneCamera = m_pCameraIndex[m_NextType];
		m_pSceneCamera->ChangeCamera_Init({999.0,999.0,999.0 }, { 999.9,999.9,999.9 });
		m_ChangeNow = false;
	}
}

void C_CameraManager::AddCamera(SCENE_CAMERA_TYPE AddType, CameraBase* AddCamera)
{
	//�J�����̏�񂪖���������
	if (!m_pCameraIndex[AddType])
	{
		m_pCameraIndex[AddType] = AddCamera;
	}
}

//�X�V������ɂ��邽�߂ɃA�h���X����ꂽ�ϐ��̃A�h���X�������Ă���
CameraBase** C_CameraManager::Get_SceneCamera()
{
	return &m_pSceneCamera;
}

//���̃J�����̏������炤
CameraBase* C_CameraManager::Get_NowCamera()
{
	return m_pSceneCamera;
}

//���̃J�����̃^�C�v�����炤
C_CameraManager::SCENE_CAMERA_TYPE C_CameraManager::Get_NowType()
{
	return m_NowType;
}

//���ꂽ�^�̃J��������������Ă���
CameraBase* C_CameraManager::Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE Type)
{
	return m_pCameraIndex[Type];
}

//�J�����̎�ނ�ς���
void C_CameraManager::ChangeTypeCamera(C_CameraManager::SCENE_CAMERA_TYPE NextType)
{
	m_NowType = NextType;
	m_pSceneCamera = m_pCameraIndex[m_NowType];
	m_pSceneCamera->ChangeCamera_Init({ 999.0f,999.0f,999.0f }, { 999.9f,999.9f,999.9f });
}

//�C�x���g�J��������ꂽ�ꍇ
void C_CameraManager::ChangeEventCamera(C_CameraManager::SCENE_CAMERA_TYPE NextType, DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float time)
{
	m_EventCamera.SetEvent(startPos, endPos, time);
	m_pSceneCamera = &m_EventCamera;
	m_ChangeNow = false;
	m_NextType = NextType;
}

void C_CameraManager::ChangeCameraNew(SCENE_CAMERA_TYPE NextType, DirectX::XMFLOAT3 YetPos, DirectX::XMFLOAT3 YetLook)
{
	DirectX::XMFLOAT3 tempCameraPos = m_pSceneCamera->GetPos();
	DirectX::XMFLOAT3 tempCameraLook = m_pSceneCamera->GetLook();

	m_NowType = NextType;

	m_pSceneCamera = m_pCameraIndex[m_NowType];
	m_pSceneCamera->ChangeCamera_Init(tempCameraPos,tempCameraLook);
}

//�J�������܂Ƃ߂��z��������Ă���(�Ƃ肠������������Ǒ����g���)
CameraBase** C_CameraManager::Get_CameraIndex()
{
	return m_pCameraIndex;
}

DirectX::XMFLOAT2 C_CameraManager::ChangeScreenPos(FloatPos _3DPos)
{
	using namespace DirectX;
	const unsigned int SCREEN_WIDTH = 1280;
	const unsigned int SCREEN_HEIGHT = 720;

	XMFLOAT3 FLOAT3_3DPos = XMFLOAT3(_3DPos.X, _3DPos.Y, _3DPos.Z);
	XMVECTOR World_Pos = XMLoadFloat3(&FLOAT3_3DPos);

	//�r���[�}�g���N�X�������Ă���
	XMFLOAT3 camera_pos = m_pSceneCamera->GetPos();
	XMFLOAT3 camera_look = m_pSceneCamera->GetLook();
	XMVECTOR Eye = XMLoadFloat3(&camera_pos);
	XMVECTOR At = XMLoadFloat3(&camera_look);
	XMVECTOR Up = XMVectorSet(0.0f,1.0f,0.0f,0.0f);
	XMMATRIX g_View = XMMatrixLookAtLH(Eye, At, Up);

	XMMATRIX g_Projection = XMMatrixPerspectiveFovLH(80.0f * 3.14f / 180.0f,SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1f,1000.0f);

	float w = SCREEN_WIDTH / 2.0f;
	float h = SCREEN_HEIGHT / 2.0f;
	XMMATRIX viewport = {
		w,0,0,0,
		0,-h,0,0,
		0,0,1,0,
		w,h,0,1
	};

	//�r���[�ϊ��ƃv���W�F�N�V�����ϊ�
	World_Pos = XMVector3Transform(World_Pos, g_View);
	World_Pos = XMVector3Transform(World_Pos, g_Projection);

	XMFLOAT3 temp;
	XMStoreFloat3(&temp, World_Pos);
	//z�Ŋ�����-1�`1�͈̔͂Ɏ��߂�
	//�X�N���[���ϊ�
	const XMVECTOR view_vec = XMVectorSet(temp.x / temp.z,
		temp.y / temp.z, 1.0f, 1.0f);
	XMVECTOR Vector_2DPos = XMVector3Transform(view_vec, viewport);

	XMFLOAT3 FLOAT3_2DPos;
	XMStoreFloat3(&FLOAT3_2DPos,Vector_2DPos);

	XMFLOAT2 FLOAT2_2DPos = XMFLOAT2(FLOAT3_2DPos.x, FLOAT3_2DPos.y);

	return FLOAT2_2DPos;
}
DirectX::XMFLOAT2 C_CameraManager::ChangeScreenPos(DirectX::XMFLOAT3 _3DPos)
{
	FloatPos tempPos;
	tempPos.X = _3DPos.x;
	tempPos.Y = _3DPos.y;
	tempPos.Z = _3DPos.z;

	return ChangeScreenPos(tempPos);
}