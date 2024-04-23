#ifndef __CAMERAMAIN_H__
#define __CAMERAMAIN_H__

#include "CameraDebug.h"
#include "XboxKeyboard.h"
#include "StageBase.h"
#include "Player.h"

class CameraMain : public CameraBase
{
public:
	CameraMain(Stage_Base* stage);
	~CameraMain() {};

	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook);
	void MovePlayerCamera();

private:
	void Interpolation();	//カメラが切り替わったときの補間	
	DirectX::XMFLOAT3 m_EndPos;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_EndLook;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_StartPos;	//ワールドカメラの開始地点
	DirectX::XMFLOAT3 m_StartLook;	//ワールドカメラの開始地点
	float m_time;
	float m_totalTime;
	Stage_Base* m_pStage;
	float MinPosX = -300.0f;   //カメラが移動できるX軸下限
	float MaxPosX = 600.0f;    //カメラが移動できるX軸上限
	float MinPosY = -300.0f;   //カメラが移動できるY軸下限
	float MaxPosY = 450.0f;    //カメラが移動できるY軸上限
	float AddposX = 0.0f;
	float AddposY = 0.0f;
	float AddposZ = 0.0f;
	float OldAddX = 0.0f;
	bool m_b;	//プレイヤーと同じ座標にいるか
	bool m_b2;	//WASDが押されてからプレイヤーと同じ座標に戻るまで
	bool m_b3;
	float m_time2;
	float m_totalTime2;
	DirectX::XMFLOAT3 a;
	constexpr static float m_posZ = -160.0f;
	constexpr static float m_posY = 60.0f;
	int m_AddMove;
};



#endif // !__CAMERAMAIN_H__

