#include "Camera_Manager.h"

//継承したコンストラクタでブロックの配列を作る
C_CameraManager::C_CameraManager(SCENE_CAMERA_TYPE NowType)
	:m_ChangeNow(false)				//次のフレームで変えるか否か
	,m_pSceneCamera(nullptr)		//継承した後に合う型によって作る
	,m_pCameraIndex(nullptr)		//継承した後に作る
	,m_NowType(NowType)				//今の型
{

}

C_CameraManager::~C_CameraManager()
{

}

void C_CameraManager::Update()
{
	//カメラのアップデート
	m_pSceneCamera->Update();

	//カメライベントだった場合
	if (m_NowType == _CAMERA_ALL_EVENT)
	{
		if (m_EventCamera.IsEvent())
		{
			m_ChangeNow = true;
		}
	}

	//イベントカメラの場合
	if(m_ChangeNow)
	{
		//型を変える
		m_NowType = m_NextType;
		//カメラの情報を入れる
		m_pSceneCamera = m_pCameraIndex[m_NextType];
		m_pSceneCamera->ChangeCamera_Init({999.0,999.0,999.0 }, { 999.9,999.9,999.9 });
		m_ChangeNow = false;
	}
}

void C_CameraManager::AddCamera(SCENE_CAMERA_TYPE AddType, CameraBase* AddCamera)
{
	//カメラの情報が無かったら
	if (!m_pCameraIndex[AddType])
	{
		m_pCameraIndex[AddType] = AddCamera;
	}
}

//更新を勝手にするためにアドレスを入れた変数のアドレスを持ってくる
CameraBase** C_CameraManager::Get_SceneCamera()
{
	return &m_pSceneCamera;
}

//今のカメラの情報をもらう
CameraBase* C_CameraManager::Get_NowCamera()
{
	return m_pSceneCamera;
}

//今のカメラのタイプをもらう
C_CameraManager::SCENE_CAMERA_TYPE C_CameraManager::Get_NowType()
{
	return m_NowType;
}

//入れた型のカメラ情報をもらってくる
CameraBase* C_CameraManager::Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE Type)
{
	return m_pCameraIndex[Type];
}

//カメラの種類を変える
void C_CameraManager::ChangeTypeCamera(C_CameraManager::SCENE_CAMERA_TYPE NextType)
{
	m_NowType = NextType;
	m_pSceneCamera = m_pCameraIndex[m_NowType];
	m_pSceneCamera->ChangeCamera_Init({ 999.0f,999.0f,999.0f }, { 999.9f,999.9f,999.9f });
}

//イベントカメラを入れた場合
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

//カメラをまとめた配列を持ってくる(とりあえず作ったけど多分使わん)
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

	//ビューマトリクスを持ってくる
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

	//ビュー変換とプロジェクション変換
	World_Pos = XMVector3Transform(World_Pos, g_View);
	World_Pos = XMVector3Transform(World_Pos, g_Projection);

	XMFLOAT3 temp;
	XMStoreFloat3(&temp, World_Pos);
	//zで割って-1～1の範囲に収める
	//スクリーン変換
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