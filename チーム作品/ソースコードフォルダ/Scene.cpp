#include "Scene.h"

CScene::CScene()
	:m_ModelManager(nullptr)
	,m_pSpriteManager(nullptr)
{

}
CScene::~CScene()
{
	if (!m_pSpriteManager)
	{
		delete m_pSpriteManager;
	}

	if (!m_ModelManager)
	{
		delete m_ModelManager;
	}
}
void CScene::Update()
{

}
void CScene::Draw()
{

}

void CScene::ChangeCamera()
{

}