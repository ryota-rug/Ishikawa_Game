#include "ObjectRenderer.h"

ObjectRenderer::ObjectRenderer(CModelManager* pmodelmanger)
{
	m_pModelManager = pmodelmanger;
}

ObjectRenderer::~ObjectRenderer()
{

}

void ObjectRenderer::Update()
{
	ObjectUpdate();
}

void ObjectRenderer::Draw()
{
	ObjectDraw();
}

void ObjectRenderer::SetModel(std::string modelName)
{
	m_ModelName = modelName;
}

void ObjectRenderer::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void ObjectRenderer::SetSize(DirectX::XMFLOAT3 size)
{
	m_size = size;
}

void ObjectRenderer::SetRotate(DirectX::XMFLOAT3 rotate)
{
	m_rotate = rotate;
}

void ObjectRenderer::SetModelManger(CModelManager * pmodelManager)
{
	m_pModelManager = pmodelManager;
}

void ObjectRenderer::SetStage(Stage_Base * pStage)
{
	m_pStage = pStage;
}
