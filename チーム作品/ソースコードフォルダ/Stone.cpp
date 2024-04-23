#include "Stone.h"
#include "ModelManager.h"
#include "PileBankerBase.h"

using namespace std;


CStone::CStone(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY)
{
	m_Type = BLOCK_STONE;
	m_HP = 200;
	m_DEF = 50;
	ADDMODEL_SENDDATA("Stone", "Assets/New_Block/isi/blocks_isi.fbx");
	m_pModelManager->c_AddModel("StoneDamage1", "Assets/New_Block/isi/blocks_isi.fbx", "base_isi1.png");
	m_pModelManager->c_AddModel("StoneDamage2", "Assets/New_Block/isi/blocks_isi.fbx", "base_isi2.png");
	m_pModelManager->c_AddModel("StoneDamage3", "Assets/New_Block/isi/blocks_isi.fbx", "base_isi3.png");
}

CStone::~CStone()
{

}

void CStone::Update()
{

}

void CStone::Draw()
{
	FloatSize size = { 0.5f, 0.5f, 0.5f };
	float angle[3] = { 0.0f, 270.0f, 0.0f };

	if (m_HP > 150)
	{
		MODELDRAW_SENDDATA("Stone", m_DrawPos, size, angle);
		return;
	}

	if (m_HP > 150)
	{
		MODELDRAW_SENDDATA("StoneDamage1", m_DrawPos, size, angle);
		return;
	}

	if (m_HP > 100)
	{
		MODELDRAW_SENDDATA("StoneDamage2", m_DrawPos, size, angle);
		return;
	}

	if (m_HP > 0)
	{
		MODELDRAW_SENDDATA("StoneDamage3", m_DrawPos, size, angle);
		return;
	}

}

void CStone::CollisionNavigate()
{

}
