#pragma once
#include "gameObject.h"
class PressEnterButton : public GameObject
{
public:
	enum State
	{
		UpSize,
		DownSize,
	};
	void Init() override;
	void Update() override;
	void SetPos(DirectX::XMFLOAT2 pos) { m_pos = pos; }
	void SetSize(DirectX::XMFLOAT2 size);
private:

	State m_state = State::UpSize;
	float m_speed = 200.0f;
	DirectX::XMFLOAT2 m_pos;
	DirectX::XMFLOAT2 m_size;
	DirectX::XMFLOAT2 m_bigsize;
	DirectX::XMFLOAT2 m_smallsize;
};