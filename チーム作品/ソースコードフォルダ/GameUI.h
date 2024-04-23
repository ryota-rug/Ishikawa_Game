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

	DirectX::XMFLOAT2 m_Size;        // 画像の大きさ
	DirectX::XMFLOAT2 m_DisplayPos;  // 画像の表示位置
	DirectX::XMFLOAT3 m_Pos;		    // 位置
	DirectX::XMFLOAT3 m_Scale;	    // 大きさ
	DirectX::XMFLOAT3 m_Angle;	    // 角度

};

#endif   __GAME_UI_H__