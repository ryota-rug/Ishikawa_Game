#ifndef __GAME_UI_H__
#define __GAME_UI_H__

#include "DirectX.h"
#include "SpriteManager.h"

class GameUI
{
public:
	GameUI();
	~GameUI();
	void Draw();

private:
	ID3D11ShaderResourceView* m_pNazoBar;
	SpriteManager* m_pSprite;

	DirectX::XMFLOAT2 m_Size;        // �摜�̑傫��
	DirectX::XMFLOAT2 m_DisplayPos;  // �摜�̕\���ʒu
	DirectX::XMFLOAT3 m_Pos;		    // �ʒu
	DirectX::XMFLOAT3 m_Scale;	    // �傫��
	DirectX::XMFLOAT3 m_Angle;	    // �p�x

};

#endif   __GAME_UI_H__