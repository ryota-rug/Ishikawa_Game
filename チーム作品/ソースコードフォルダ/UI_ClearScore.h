//#pragma once
#ifndef UI_CLEARSCORE
#define UI_CLEARSCORE
#include "SpriteManager.h"
#include "Position_struct.h"
#include <DirectXMath.h>

class UI_ClearScore
{
public:
	UI_ClearScore();
	~UI_ClearScore();
	void Update();
	void Draw(int Score = 0);
	void SetPos(DirectX::XMFLOAT2 pos);

private:

	typedef struct
	{
		DirectX::XMFLOAT2 m_pos;			//ç¿ïW
		DirectX::XMFLOAT2 m_size;			//ëÂÇ´Ç≥

	}UItransform;

private:
	SpriteManager* m_pSprite;
	UItransform m_Transform;
	ID3D11ShaderResourceView* m_pScoreTexture;
	DirectX::XMINT2 m_TextureNum;
	DirectX::XMFLOAT2 m_TextureSize;
};


#endif // !UI_CLEARSCORE
