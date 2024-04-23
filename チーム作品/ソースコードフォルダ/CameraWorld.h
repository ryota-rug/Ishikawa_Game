#ifndef __CAMERAWORLD_H__
#define __CAMERAWORLD_H__

#include "CameraBase.h"
#include "StageBase.h"

class CameraWorld :public CameraBase
{
public:
	CameraWorld (Stage_Base* Stage);
	~CameraWorld() {};
	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook);

private:
	void Interpolation();	//カメラが切り替わったときの補間	
	DirectX::XMFLOAT3 m_EndPos;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_EndLook;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_StartPos;	//ワールドカメラの開始地点
	DirectX::XMFLOAT3 m_StartLook;	//ワールドカメラの開始地点
	float m_time;
	float m_totalTime;

	Stage_Base* m_pStage;
	constexpr static float m_Const = -45.0f;

};


#endif // !__CAMERAWORLD_H__
