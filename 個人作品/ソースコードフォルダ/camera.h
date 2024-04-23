#pragma once
#include "gameObject.h"


class Camera : public GameObject
{

private:

	DirectX::XMFLOAT3	m_Target{};
	DirectX::XMFLOAT4X4	m_ViewMatrix{};
	DirectX::XMFLOAT3 m_up{};
	int m_mode = 0;

public:
	void Init() override;
	void Update() override;
	void Draw() override;

	DirectX::XMFLOAT4X4 GetViewMatrix() { return m_ViewMatrix; }
};
