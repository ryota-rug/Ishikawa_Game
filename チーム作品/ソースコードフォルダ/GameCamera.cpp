#include "GameCamera.h"
#include "CameraBase.h"
#include "CameraDebug.h"
#include "CameraEvent.h"
#include "StageBase.h"
#include "Geometory.h"



CameraBase* m_pCamera[MAX_CAMERA];
CameraKind m_mainCamera;


void InitGameCamera()
{
	m_mainCamera = CAM_DEBUG;									//ゲーム開始時に使うカメラを決める
	m_pCamera[CAM_DEBUG] = new CameraDebug();					//デバッグカメラの生成
	CameraEvent* pEvent = new CameraEvent();					//イベントカメラの生成
	pEvent->SetEvent(DirectX::XMFLOAT3(10.0f, 15.0f, 9.0f), DirectX::XMFLOAT3(-5.0f, 15.0f, 5.0f), 10.0f);
	m_pCamera[CAM_EVENT] = pEvent;
}

void UninitGameCamera()
{
	for (int i = 0; i < MAX_CAMERA; i++)
	{
		delete m_pCamera[i];
	}
}

void UpdateGameCamera()
{
	CameraKind camera = m_mainCamera;
	
	if (IsKeyPress('C'))
	{
		if (IsKeyTrigger('1')) camera = CAM_DEBUG;
		//if (IsKeyTrigger('2')) camera = CAM_PLAYER;
		if (IsKeyTrigger('2')) camera = CAM_EVENT;
	}
	
	if (m_mainCamera != camera)
	{
		m_mainCamera = camera;
	}
	
	if (m_mainCamera == CAM_EVENT)
	{
		CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[CAM_EVENT]);
		if (!pEvent->IsEvent()) {
			m_mainCamera = CAM_DEBUG;
		}
	}
	
	m_pCamera[m_mainCamera]->Update();
}

void DrawGameCamera()
{
	//ステージ用の行列
	SetGeometoryVPMatrix(
		m_pCamera[m_mainCamera]->GetViewMatrix(),
		m_pCamera[m_mainCamera]->GetProjectionMatrix());
}

DirectX::XMFLOAT4X4 Get_ProtMat()
{
	return m_pCamera[m_mainCamera]->GetProjectionMatrix();
}

DirectX::XMFLOAT4X4 Get_ViewMat()
{
	return m_pCamera[m_mainCamera]->GetViewMatrix();
}
