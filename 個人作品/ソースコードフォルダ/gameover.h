// ResultƒV[ƒ“ [result.h]
#pragma once
#include "scene.h"

class GameOver : public Scene
{
private:
	class Transition* m_Transition{};
	class Audio*		m_BGM{};

public:
	void Init() override;
	void Update() override;
};
