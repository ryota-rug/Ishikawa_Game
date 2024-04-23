//#pragma once
#ifndef CAMERA_EVENT
#define CAMERA_EVENT
#include "CameraBase.h"
#include "Main.h"

class CameraEvent :public CameraBase
{
public:
	CameraEvent() : m_start(0.0f, 0.0f, 0.0f), m_end(0.0f, 0.0f, 0.0f), m_time(0.0f), m_totalTime(0.0f) {}
	~CameraEvent() {}
	void Update() {

		if (!IsEvent()) { return; }	//���Ԃ��߂��Ă�����I������
		
		m_time += 1.0f / 60.0f;

		float x = m_time / m_totalTime;

		//float Intermediary = -(cos(3.141592f * (m_time / m_totalTime)) - 1.0f)/2.0f;	//�}��ϐ�(���ԁA�p�[�Z���e�[�W�Ȃ�)
		float Intermediary = x < 0.5f ? 2 * pow(x, 2) : 1 - pow(-2 * x + 2, 3) / 2;	//�}��ϐ�(���ԁA�p�[�Z���e�[�W�Ȃ�)
		
		//���(���W)
		DirectX::XMFLOAT3 lerp = { (m_end.x - m_start.x) * Intermediary + m_start.x
								,(m_end.y - m_start.y) * Intermediary + m_start.y
								,(m_end.z - m_start.z) * Intermediary + m_start.z};

		//�����_�����ƂɃJ�����̈ʒu�����߂�
		m_pos = lerp;		//���W�͕�Ԃ̒l(start����end�Ɍ������Ă�����W)
		m_look = m_start;	//�����_�͍ŏ��̍��W
	}

	void SetEvent(DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float time)
	{
		m_start = startPos;
		m_end = endPos;
		m_time = 0.0f;
		m_totalTime = time;
	}
	bool IsEvent() {
		return m_time < m_totalTime;
	}

private :
	DirectX::XMFLOAT3 m_start;
	DirectX::XMFLOAT3 m_end;
	float m_time;
	float m_totalTime;
};

#endif	//CAMERA_EVENT

