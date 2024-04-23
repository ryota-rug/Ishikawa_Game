#include "Bedrock.h"
#include "ModelManager.h"
#include "PileBankerBase.h"

using namespace std;


CBedrock::CBedrock(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY)
{
	m_Type = BLOCK_BEDROCK;
	m_HP = 9999;
	m_DEF = 100;
	ADDMODEL_SENDDATA("Bedrock", "Assets/New_Block/ganban/blocks_ganban.fbx");
}

CBedrock::~CBedrock()
{

}

void CBedrock::Update()
{

}

void CBedrock::Draw()
{
	FloatSize size = { 0.5f, 0.5f, 0.5f };
	float angle[3] = { 0.0f, 0.0f, 0.0f };

	MODELDRAW_SENDDATA("Bedrock", m_DrawPos, size, angle);
}

void CBedrock::CollisionNavigate()
{

}
