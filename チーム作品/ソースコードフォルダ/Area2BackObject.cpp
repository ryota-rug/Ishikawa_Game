#include "Area2BackObject.h"

Area2BackObject::Area2BackObject(CModelManager* pmodelmanger)
	:ObjectRenderer(pmodelmanger)
{
	m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_rotate = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_pModelManager->c_AddModel("Stage2", "Assets/steage/steage2/steage2.fbx", "steage2.png");
	m_pModelManager->c_AddModel("Stage2_Deppari", "Assets/steage/steage2/steage2_deppari.fbx", "steage2_deppari.png");
}

Area2BackObject::~Area2BackObject()
{

}

void Area2BackObject::ObjectUpdate()
{

}

void Area2BackObject::ObjectDraw()
{
	DirectX::XMFLOAT3 LEFT_DEPPARI_POS = { -792.0f,-233.0f,-8.0f };
	DirectX::XMFLOAT3 RIGHT_DEPPARI_POS = { -230.0f,-233.0f,-8.0f };

	LEFT_DEPPARI_POS.x -= m_pStage->GetStageLength().X * 0.5f;
	RIGHT_DEPPARI_POS.x += m_pStage->GetStageLength().X * 0.5f;

	m_pModelManager->c_ModelDraw("Stage2",
		118.0f + m_pos.x, 168.0f + m_pos.x, 536.0f + m_pos.x,
		10.7f * m_size.x, 10.7f * m_size.y, 10.7f * m_size.z,
		0.0f + m_rotate.x, 180.0f + m_rotate.y, 0.0f + m_rotate.z);
	m_pModelManager->c_ModelDraw("Stage2_Deppari", 
		LEFT_DEPPARI_POS.x + m_pos.x, LEFT_DEPPARI_POS.y + m_pos.y, LEFT_DEPPARI_POS.z + m_pos.z,
		28.4f * m_size.x, 28.4f * m_size.y, 28.4f * m_size.z,
		29.8f + m_rotate.x, 0.0f + m_rotate.y, 0.0f + m_rotate.z);
	m_pModelManager->c_ModelDraw("Stage2_Deppari",
		RIGHT_DEPPARI_POS.x + m_pos.x, RIGHT_DEPPARI_POS.y + m_pos.y, RIGHT_DEPPARI_POS.z + m_pos.z,
		28.4f * m_size.x, 28.4f * m_size.y, 28.4f * m_size.z,
		29.8f + m_rotate.x, 0.0f + m_rotate.y, 0.0f + m_rotate.z);
}
