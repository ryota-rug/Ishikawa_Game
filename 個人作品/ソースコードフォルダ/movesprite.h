#pragma once
#include "component.h"
#include "renderer.h"
class MoveSprite : public Component
{
private:
	ID3D11Buffer*				m_VertexBuffer{};
	ID3D11ShaderResourceView*	m_Texture{};

	MATERIAL					m_Material{};

	DirectX::XMFLOAT2* pos;
	DirectX::XMFLOAT2* size;
	DirectX::XMFLOAT4* diffuse;
public:

	using Component::Component;

	void Init(DirectX::XMFLOAT2* pPos, DirectX::XMFLOAT2* pSize, const char* TextureName = nullptr);
	void Uninit() override;
	void Draw() override;

	void SetMaterial(MATERIAL Material) { m_Material = Material; }

};

