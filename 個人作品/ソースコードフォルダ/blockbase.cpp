#include "blockbase.h"
#include "shadow.h"
#include "shader.h"
#include "modelRenderer.h"

void BlockBase::Init()
{
	//AddComponent<Shadow>()->SetSize(2.0f);
}

void BlockBase::SetBlock(DirectX::XMFLOAT3 pos, BlockType type)
{
	
	m_Type = type;
	// ‚±‚±‚Å•\Ž¦‚·‚éƒ‚ƒfƒ‹‚ð•Ï‚¦‚é
	switch (m_Type)
	{
	case 0:
		m_Destroy = true;
		return;
		break;
	case 1:
		AddComponent<Shader>()->Load("shader/vertexLightingVS.cso",
			"shader/vertexLightingPS.cso");
		AddComponent<ModelRenderer>()->Load("asset/model/block.obj");
		break;
	case 2:
		AddComponent<Shader>()->Load("shader/vertexLightingVS.cso",
			"shader/vertexLightingPS.cso");
		AddComponent<ModelRenderer>()->Load("asset/model/block.obj");
		break;
	}

	SetPosition(pos);
	AddComponent<Shadow>()->SetSize(1.0f);

	SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
}
