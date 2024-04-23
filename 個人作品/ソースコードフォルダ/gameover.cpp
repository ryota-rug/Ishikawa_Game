// Resultシーン [result.cpp]
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gameover.h"
#include "title.h"
#include "shader.h"
#include "sprite.h"
#include "transition.h"
#include "pressenter.h"
#include "audio.h"

void GameOver::Init()
{
	GameObject* OverBackGround = AddGameObject<GameObject>(3);
	OverBackGround->AddComponent<Shader>()->Load("shader/unlitTextureVS.cso", "shader/unlitTexturePS.cso");
	OverBackGround->AddComponent<Sprite>()->Init(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/gameover.jpg");

	GameObject* OverLogo = AddGameObject<GameObject>(3);
	OverLogo->AddComponent<Shader>()->Load("shader/unlitTextureVS.cso", "shader/unlitTexturePS.cso");
	OverLogo->AddComponent<Sprite>()->Init(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/OverLetter.png");

	PressEnterButton* pressenter = AddGameObject<PressEnterButton>(3);
	pressenter->SetPos(DirectX::XMFLOAT2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f + 200.0f));
	pressenter->SetSize(DirectX::XMFLOAT2A(500.0f, 500.0f));

	m_BGM = AddGameObject<GameObject>(1)->AddComponent<Audio>();
	m_BGM->Load("asset/audio/gameover.wav");
	m_BGM->Play(true);	// ループ再生

	m_Transition = AddGameObject<Transition>(4);
	m_Transition->FadeIn();
}

void GameOver::Update()
{
	if (m_Transition->GetState() == Transition::State::Stop)
	{
		if (Input::GetKeyTrigger(VK_RETURN) || Input::GetKeyTrigger(VK_SPACE))
		{
			m_Transition->FadeOut();
		}
	}
	if (m_Transition->GetState() == Transition::State::Finish)
	{
		Manager::SetScene<Title>();
	}
}
