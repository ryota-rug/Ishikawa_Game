// Spriteコンポーネント [sprite.h]
#pragma once

#include "renderer.h"
#include "component.h"

class Sprite : public Component
{

private:
	ID3D11Buffer*				m_VertexBuffer{};
	ID3D11ShaderResourceView*	m_Texture{};
	
	MATERIAL					m_Material{};

	DirectX::XMFLOAT2 pos;
	DirectX::XMFLOAT2 size;

public:

	using Component::Component;

	void Init(float x, float y, float Width, float Height, const char* TextureName = nullptr);
	void Uninit() override;
	void Draw() override;

	void SetMaterial(MATERIAL Material) { m_Material = Material; }

};
