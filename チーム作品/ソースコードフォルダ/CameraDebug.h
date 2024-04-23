//#pragma once
#ifndef CAMERADEBUG
#define CAMERADEBUG
#include "Input.h"
#include "CameraBase.h"


void BiblationCameraDebug();

class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug() {};
	void Update();
private:
	constexpr static int LIMIT_TOP_ANGLE = 30;	//縦アングルの上限
	constexpr static int LIMIT_BOTTOM_ANGLE = 150;	//横アングルの上限
	constexpr static float UD_ANGLE_SPEED = 2.0f;	//縦アングルスピード
	constexpr static float RL_ANGLE_SPEED = 2.0f;	//横アングルスピード
	DirectX::XMFLOAT3 f3Flont;		//vFlontの受け箱
	float m_AngleXZ, m_AngleYFlont;	//度角
	float m_radXZ, m_radY;	//ラジアン角
	float m_lateXZ, m_lateYFlont;	//目的位置に対してどれだけ遅れて追いつくか
	
	//あとで絶対消してね！！！！
	DirectX::XMFLOAT3 HINANPOS;
};


#endif //CAMERADEBUG