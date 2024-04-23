#include "Clay.h"
#include "ModelManager.h"
#include "PileBankerBase.h"

using namespace std;


CClay::CClay(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY)
{
	m_Type = BLOCK_CLAY;
	m_HP = 1;
	m_DEF = 1;
	ADDMODEL_SENDDATA("Clay", "Assets/New_Block/nendo/blocks_nendo.fbx");
}

CClay::~CClay()
{

}

void CClay::Update()
{

}

void CClay::Draw()
{
	FloatSize size = { 0.5f, 0.5f, 0.5f };
	float angle[3] = { 0.0f, 0.0f, 0.0f };

	MODELDRAW_SENDDATA("Clay", m_DrawPos, size, angle);
}

void CClay::CollisionNavigate()
{

}
