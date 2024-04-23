#ifndef __CAMERACLEAR_H__
#define __CAMERACLEAR_H__

#include "CameraBase.h"
#include "StageBase.h"
#include "Player.h"

class CameraClear : public CameraBase
{
public:
	CameraClear(Stage_Base* Stage);
	~CameraClear() {};
	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook) override;

private:
	void Interpolation();	//カメラが切り替わったときの補間	
	
	Stage_Base* m_pStage;
	constexpr static float m_pointY = 30.0f;
	constexpr static float m_pointZ = -80.0f;

	DirectX::XMFLOAT3 m_EndPos;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_EndLook;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_StartPos;	//ワールドカメラの開始地点
	DirectX::XMFLOAT3 m_StartLook;	//ワールドカメラの開始地点
	float m_time;
	float m_totalTime;
};


#endif // !__CAMERACLEAR_H__
