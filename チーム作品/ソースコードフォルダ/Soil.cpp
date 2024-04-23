#include "Soil.h"
#include "ModelManager.h"
#include "PileBankerBase.h"

using namespace std;


CSoil::CSoil(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY)
{
	m_Type = BLOCK_SOIL;
	m_HP = 50;
	m_DEF = 10;
	ADDMODEL_SENDDATA("Soil", "Assets/New_Block/tuti/blocks_tuti.fbx");
}

CSoil::~CSoil()
{

}

void CSoil::Update()
{

}

void CSoil::Draw()
{
	FloatSize size = { 0.5f, 0.5f, 0.5f };
	float angle[3] = { 0.0f, 0.0f, 0.0f };

	MODELDRAW_SENDDATA("Soil", m_DrawPos, size, angle);
}

void CSoil::CollisionNavigate()
{
}
