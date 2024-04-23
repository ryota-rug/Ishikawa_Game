#ifndef __CAMERAMISS_H__
#define __CAMERAMISS_H__

#include "CameraBase.h"
#include "StageBase.h"
#include "Player.h"

class CameraMiss : public CameraBase
{
public:
	CameraMiss(Stage_Base* Stage);
	~CameraMiss() {};
	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook) override;
	void Set(DirectX::XMFLOAT3 yetPos);
private:
	void Interpolation();	//カメラが切り替わったときの補間	

private:
	Stage_Base* m_pStage;
	Stage_Base::GAMEOVER_TYPE m_eType;
	constexpr static float m_pointZ = -200.0f;

	DirectX::XMFLOAT3 m_EndPos;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_EndLook;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_StartPos;	//ワールドカメラの開始地点
	DirectX::XMFLOAT3 m_StartLook;	//ワールドカメラの開始地点
	float m_time;
	float m_totalTime;

};




#endif // !__CAMERAMISS_H__
