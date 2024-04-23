#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

#include "Sprite.h"
#include "DirectX.h"
#include "BlendState.h"
#include "MeshBuffer.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "SamplerState.h"
#include <map>
#include <string>
#include <DirectXMath.h>

#include "CameraBase.h"


class SpriteManager
{
public:

public:
	SpriteManager();
	~SpriteManager();

	static void Init();
	static void TextureRelease(ID3D11ShaderResourceView* pptex);

	void Draw
	(
		DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 angle,
		DirectX::XMFLOAT2 uvPos, DirectX::XMFLOAT2 uvScale,
		DirectX::XMFLOAT4 color,
		ID3D11ShaderResourceView* pptex
	);

	void DrawBillBoard
	(
		DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 size,
		DirectX::XMFLOAT2 uvPos, DirectX::XMFLOAT2 uvScale,
		DirectX::XMFLOAT4 color,
		ID3D11ShaderResourceView* pptex,
		CameraBase* pCamera
	);

private:
	Sprite* m_pSprite;
	static BlendState* m_pBlend;
	SamplerState* m_pSampler;

	const char* fileName;
	ID3D11ShaderResourceView* ppTex;

	bool m_bInit;
};
#endif   // __SPRITE_MANAGER_H__#pragma once
