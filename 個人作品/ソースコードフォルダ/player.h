// Playerオブジェクト [player.h]
#pragma once

//#include "gameObject.h"
#include "character.h"

class Player : public Character
{
private:
	bool CheckColissionBlock();
	DirectX::XMFLOAT3	m_Velocity{};
	//class Audio*		m_SE;
	//class AnimationModel* m_Model;
	int     m_AnimFrame = 0;
	float	m_Blend = 0.0f;
	bool m_bWalkFlg = false;
	bool m_bJumpFlg = false;
	bool m_bOldWalk = false;
public:
	void Init() override;
	void Update() override;
	void PreDraw() override;
};
