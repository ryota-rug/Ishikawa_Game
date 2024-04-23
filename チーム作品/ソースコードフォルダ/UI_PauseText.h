//#pragma once
#ifndef UI_PAUSE_TEXT_H
#define UI_PAUSE_TEXT_H
#include <DirectXMath.h>
#include "DirectX.h"
#include "SpriteManager.h"

class UI_Pause_Text
{
public:

	UI_Pause_Text();
	~UI_Pause_Text();
	void Update();
	void Draw();
	void SetTexture(const char* pTextureName);
	void SetTransform(DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size);

private:
	DirectX::XMFLOAT2 m_Size;                  // ‰æ‘œ‚Ì‘å‚«‚³
	DirectX::XMFLOAT2 m_Pos;            // ‰æ‘œ‚Ì•\¦ˆÊ’u
	DirectX::XMFLOAT3 m_Scale;	        // ‘å‚«‚³
	DirectX::XMFLOAT3 m_Angle;	        // Šp“x
	ID3D11ShaderResourceView* m_pTexture;    // –¢Šl“¾UI‚Ìî•ñ
	SpriteManager* m_pSprite;
};

#endif // !UI_PAUSE_TEXT_H
