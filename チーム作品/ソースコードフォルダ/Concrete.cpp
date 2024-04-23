#include "Concrete.h"
#include "ModelManager.h"
#include "PileBankerBase.h"

using namespace std;

CConcrete::CConcrete(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY)
{
	m_Type = BLOCK_CONCRETE;
	m_HP = 200;
	m_DEF = 50;
	ADDMODEL_SENDDATA("Concrete","Assets/New_Block/konnkurito/blocks_konnkurito.fbx");
	CModelManager::c_AddModel("ConcreteDamage1", "Assets/New_Block/konnkurito/blocks_konnkurito.fbx", "base_konnkuri-to1.png");
	CModelManager::c_AddModel("ConcreteDamage2", "Assets/New_Block/konnkurito/blocks_konnkurito.fbx", "base_konnkuri-to2.png");
	CModelManager::c_AddModel("ConcreteDamage3", "Assets/New_Block/konnkurito/blocks_konnkurito.fbx", "base_konnkuri-to3.png");
}

CConcrete::~CConcrete()
{

}

void CConcrete::Update()
{

}

void CConcrete::Draw()
{
	FloatSize size = { 0.5f, 0.5f, 0.5f };
	float angle[3] = { 0.0f, 270.0f, 0.0f };

	if (m_HP > 150)
	{
		MODELDRAW_SENDDATA("Concrete", m_DrawPos, size, angle);
		return;
	}

	if (m_HP > 100)
	{
		MODELDRAW_SENDDATA("ConcreteDamage1", m_DrawPos, size, angle);
		return;
	}

	if (m_HP > 50)
	{
		MODELDRAW_SENDDATA("ConcreteDamage2", m_DrawPos, size, angle);
		return;
	}

	if (m_HP > 0)
	{
		MODELDRAW_SENDDATA("ConcreteDamage3", m_DrawPos, size, angle);
		return;
	}
}

void CConcrete::CollisionNavigate()
{

}
