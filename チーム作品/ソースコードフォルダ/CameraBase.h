//#pragma once
#ifndef CAMERABASE
#define CAMERABASE
#include <DirectXMath.h>

//マクロ
#define Def_Pi (3.141592f)
#define Angle_To_Radion(Angle) (Angle * Def_Pi / 180.0f)

class CameraBase
{
public :
	CameraBase();
	virtual ~CameraBase();
	virtual void Update() = 0;
	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetLook();
	virtual void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook);
private:

protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	//ビュー行列の設定に必要な変数
	float m_fovy, m_aspect, m_near, m_far;	//プロジェクション行列の設定に必要な変数
};


#endif //CAMERABASE