#include "Area1BackObject.h"

Area1BackObject::Area1BackObject(CModelManager* pmodelmanger)
	:ObjectRenderer(pmodelmanger)
{
	m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_rotate = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_pModelManager->c_AddModel("Stage1", "Assets/steage/steage1/steage1.fbx", "steage1.png");
	m_pModelManager->c_AddModel("Stage1_Deppari", "Assets/steage/steage1/steage1_deppari.fbx", "steage1_deppari.png");
}

Area1BackObject::~Area1BackObject()
{

}

void Area1BackObject::ObjectUpdate()
{

}

void Area1BackObject::ObjectDraw()
{
	DirectX::XMFLOAT3 LEFT_DEPPARI_POS = { -928.0f,2.0f,-9.0f };
	DirectX::XMFLOAT3 RIGHT_DEPPARI_POS = { -85.0f,2.0f,-9.0f };

	LEFT_DEPPARI_POS.x -= m_pStage->GetStageLength().X * 0.5f;
	RIGHT_DEPPARI_POS.x += m_pStage->GetStageLength().X * 0.5f;

	m_pModelManager->c_ModelDraw("Stage1", 
		217.0 + m_pos.x, 170.0f + m_pos.y, 242.0f + m_pos.z, 
		10.7f * m_size.x, 10.7f * m_size.y, 10.7f * m_size.z, 
		0.0f + m_rotate.x, 180.0f + m_rotate.y, 0.0f + m_rotate.z);
	m_pModelManager->c_ModelDraw("Stage1_Deppari",
		RIGHT_DEPPARI_POS.x + m_pos.x, RIGHT_DEPPARI_POS.y + m_pos.y, RIGHT_DEPPARI_POS.z + m_pos.z,
		10.1f * m_size.x, 10.1f * m_size.y, 10.1f * m_size.z, 
		0.0f + m_rotate.x, 180.0f + m_rotate.y, 0.0f + m_rotate.z);
	m_pModelManager->c_ModelDraw("Stage1_Deppari", 
		LEFT_DEPPARI_POS.x + m_pos.x, LEFT_DEPPARI_POS.y + m_pos.y, LEFT_DEPPARI_POS.z + m_pos.z,
		10.1f * m_size.x, 10.1f * m_size.y, 10.1f * m_size.z,
		0.0f + m_rotate.x, 180.0f + m_rotate.y, 0.0f + m_rotate.z);
}
