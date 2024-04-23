#include "Area3BackObject.h"

Area3BackObject::Area3BackObject(CModelManager* pmodelmanger)
	:ObjectRenderer(pmodelmanger)
{
	m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_rotate = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_pModelManager->c_AddModel("Stage3", "Assets/steage/steage3/steage3.fbx", "steage3.png");
	m_pModelManager->c_AddModel("Stage3_Deppari", "Assets/steage/steage3/steage3_deppari.fbx", "steage3_deppari.png");
}

Area3BackObject::~Area3BackObject()
{

}

void Area3BackObject::ObjectUpdate()
{

}

void Area3BackObject::ObjectDraw()
{
	DirectX::XMFLOAT3 LEFT_DEPPARI_POS = { 644.0f,332.0f,320.0f };
	DirectX::XMFLOAT3 RIGHT_DEPPARI_POS = { 1212.0f,332.0f,320.0f };

	LEFT_DEPPARI_POS.x -= m_pStage->GetStageLength().X * 0.5f;
	RIGHT_DEPPARI_POS.x += m_pStage->GetStageLength().X * 0.5f;

	m_pModelManager->c_ModelDraw("Stage3",
		334.0f + m_pos.x, 308.1f + m_pos.y, 604.0f + m_pos.z,
		10.7f * m_size.x, 10.7f * m_size.y, 10.7f * m_size.z,
		0.0f + m_rotate.x, 180.0f + m_rotate.y, 0.0f + m_rotate.z);
	m_pModelManager->c_ModelDraw("Stage3_Deppari", 
		LEFT_DEPPARI_POS.x + m_pos.x, LEFT_DEPPARI_POS.y + m_pos.y, LEFT_DEPPARI_POS.z + m_pos.z,
		79.9f * m_size.x, 79.9f * m_size.y, 79.9f * m_size.z,
		60.0f + m_rotate.x, 0.0f + m_rotate.y, 0.0f + m_rotate.z);
	m_pModelManager->c_ModelDraw("Stage3_Deppari",
		RIGHT_DEPPARI_POS.x + m_pos.x, RIGHT_DEPPARI_POS.y + m_pos.y, RIGHT_DEPPARI_POS.z + m_pos.z,
		79.9f * m_size.x, 79.9f * m_size.y, 79.9f * m_size.z,
		60.0f + m_rotate.x, 0.0f + m_rotate.y, 0.0f + m_rotate.z);
}
