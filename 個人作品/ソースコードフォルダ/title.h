// TitleÉVÅ[Éì [title.h]
#pragma once
#include "scene.h"

class Title : public Scene
{
private:
	class Transition* m_Transition{};
	class Audio*		m_BGM{};

	float m_Time = 0.0f;
	float m_GeneTime = 0.01f;

public:
	void Init() override;
	void Update() override;

};
