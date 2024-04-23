// Explosionオブジェクト [explosion.h]
#pragma once

#include "renderer.h"
#include "gameObject.h"
#include "fieldmanager.h"

class Explosion : public GameObject
{
private:
	static ID3D11Buffer*                m_VertexBuffer;
	static ID3D11ShaderResourceView*    m_Texture;

	int m_Count;
	FieldManager::Info* m_NowInfo;
public:
	static void Load();
	static void Unload();

	void Init() override;
	void Update() override;
	void Draw() override;
	void SetInfo(FieldManager::Info* info) { m_NowInfo = info; }
};
