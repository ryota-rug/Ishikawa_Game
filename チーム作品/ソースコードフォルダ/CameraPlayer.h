//#pragma once
#ifndef H_CAMERAPLAYER
#define H_CAMERAPLAYER

#include "CameraBase.h"
#include "Player.h"

class CameraPlayer :public CameraBase
{
public :
	CameraPlayer(Player* pPlayer): m_pPlayer(pPlayer),m_rotation(0.0f,0.0f),m_lateX(0.0f),m_lateY(0.0f){}
	~CameraPlayer(){}
	void Update()
	{
		//注点の設定
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = -10.0f;

		m_look.x = 0.0f;
		m_look.y = 0.0f;
		m_look.z = 0.0f;
		//遅れて、ついていく場合の角度を計算
		DirectX::XMFLOAT2 Now_Angle;
		m_lateX = (m_rotation.x - m_lateX) * 0.03f + m_lateX;
		m_lateY = (m_rotation.y - m_lateY) * 0.03f + m_lateY;

		//遅れた角度でカメラの位置を求める
		//入れた角度の位置にカメラが移動する
		m_pos.y = (sin(Angle_To_Radion(m_lateY)) * 5.0f) + m_look.y;

		//カメラのズーム
		if (IsKeyPress('U')) { m_fovy -= 0.1f; }		//アップ
		if (IsKeyPress('I')) { m_fovy += 0.1f; }		//ダウン
	}

	void PlayerN()
	{

	}

private :
	const float RotationSpeed = 1.0f;
	Player *m_pPlayer;
	DirectX::XMFLOAT2 m_rotation;	//着くべき角度を入れる
	float m_lateX, m_lateY;	//目的一に対して遅れてついていく角度(現在の角度)
};

#endif //H_CAMEARAPLAYER