// Titleシーン [title.cpp]
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "audio.h"
#include "title.h"
#include "game.h"
#include "shader.h"
#include "sprite.h"
#include "transition.h"
#include "movesprite.h"
#include "rand.h"
#include "pressenter.h"


void Title::Init()
{
	GameObject* titleground = AddGameObject<GameObject>(3);
	titleground->AddComponent<Shader>()->Load("shader/unlitTextureVS.cso", "shader/unlitTexturePS.cso");
	titleground->AddComponent<Sprite>()->Init(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/Ground.jpg");

	GameObject* titlelogo = AddGameObject<GameObject>(3);
	titlelogo->AddComponent<Shader>()->Load("shader/unlitTextureVS.cso", "shader/unlitTexturePS.cso");
	titlelogo->AddComponent<Sprite>()->Init(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/TitleLogo.png");

	PressEnterButton* pressenter = AddGameObject<PressEnterButton>(3);
	pressenter->SetPos(DirectX::XMFLOAT2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 200.0f));
	pressenter->SetSize(DirectX::XMFLOAT2A(500.0f, 500.0f));

	m_BGM = AddGameObject<GameObject>(1)->AddComponent<Audio>();
	m_BGM->Load("asset/audio/title.wav");
	m_BGM->Play(true);	// ループ再生

	m_Transition = AddGameObject<Transition>(4);
	m_Transition->FadeIn();
}

void Title::Update()
{
	if (m_Transition->GetState() == Transition::State::Stop)
	{
		if (Input::GetKeyTrigger(VK_RETURN) || Input::GetKeyTrigger(VK_SPACE))
		{
			m_Transition->FadeOut();
		}

		/*if (m_Time >= m_GeneTime)
		{
			GameObject* obj = AddGameObject<GameObject>(3);
			obj->SetUIFlag();
			obj->SetLocalPos(DirectX::XMFLOAT2(SCREEN_WIDTH / 2.0f - 25.0f, SCREEN_HEIGHT - 125.0f));
			obj->SetLocalSize(DirectX::XMFLOAT2(50.0f, 50.0f));
			float x = (float)rnd(-1.0f, 1.0f);
			float y = (float)rnd(-3.0f, -1.0f);
			obj->SetLocalVelocity(DirectX::XMFLOAT2(x, y));
			obj->AddComponent<Shader>()->Load("shader/unlitTextureVS.cso", "shader/unlitTexturePS.cso");
			obj->AddComponent<MoveSprite>()->Init(obj->GetLocalPos(), obj->GetLocalSize(), "asset/texture/smoke.png");

			m_Time = 0.0f;
		}*/
	}
	if (m_Transition->GetState() == Transition::State::Finish)
	{
		Manager::SetScene<Game>();
	}

	//m_Time += 1.0f / 60.0f;
}
