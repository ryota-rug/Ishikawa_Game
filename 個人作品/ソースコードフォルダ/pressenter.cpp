#include "pressenter.h"
#include "shader.h"
#include "CreateTexture.h"
#include "renderer.h"
#include "movesprite.h"

void PressEnterButton::Init()
{
	GameObject::Init();

	AddComponent<Shader>()->Load("shader/unlitTextureVS.cso",
		"shader/unlitTexturePS.cso");

	AddComponent<MoveSprite>()->Init(
		&m_pos, &m_size, "asset/texture/PRESS_ENTER.png");
}

void PressEnterButton::Update()
{
	GameObject::Update();

	if (m_size.x > m_bigsize.x)
	{
		m_state = State::DownSize;
	}
	else if (m_size.x < m_smallsize.x)
	{
		m_state = State::UpSize;
	}

	switch (m_state)
	{
	case PressEnterButton::UpSize:
		m_size.x += m_speed * m_deltaTime;
		m_size.y += m_speed * m_deltaTime;
		break;
	case PressEnterButton::DownSize:
		m_size.x -= m_speed * m_deltaTime;
		m_size.y -= m_speed * m_deltaTime;
		break;
	default:
		break;
	}
}

void PressEnterButton::SetSize(DirectX::XMFLOAT2 size)
{
	m_size = size;
	m_smallsize = size;
	m_bigsize.x = m_size.x * 1.5f;
	m_bigsize.y = m_size.y * 1.5f;
}
