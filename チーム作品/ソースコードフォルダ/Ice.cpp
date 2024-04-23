#include "Ice.h"
#include "ModelManager.h"
#include "PileBankerBase.h"
#include "Water.h"
#include "Effect_Manager.h"

using namespace std;


CIce::CIce(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY)
{
	m_Type = BLOCK_ICE;
	m_HP = 1;
	m_DEF = 1;

	m_isChangeBlock = false;

	ADDMODEL_SENDDATA("Ice", "Assets/New_Block/koori/blocks_koori.fbx");
}

CIce::~CIce()
{
	Effect_Manager::GetManager()->StopEffect(m_IceHandle);
}

void CIce::Update()
{
	if (m_nEffeckFrame % 100 == 0)
	{
		m_IceHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("IceFog"),
			m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z + 20.0f);
		Effect_Manager::GetManager()->SetScale(m_IceHandle,12.0f, 12.0f, 12.0f);
	}
	m_nEffeckFrame++;
	auto CheckLava = [this](int posX, int posY)
	{
		if (posX > 0 && m_pMyStage->GetStageWidthNum().X >= posX &&
			posY > 0 && m_pMyStage->GetStageWidthNum().Y >= posY)
		{
			if (m_pMyStage->GetBlockInfo(posX, posY) == nullptr) { return false; }
			return m_pMyStage->GetBlockInfo(posX, posY)->GetType() == Block_Base::BLOCK_MAGMA;
		}

		return false;
	};
	
	bool TouchOnLava =	CheckLava(m_MapPos.X + 1,	m_MapPos.Y    ) ||
						CheckLava(m_MapPos.X - 1,	m_MapPos.Y    ) ||
						CheckLava(m_MapPos.X    ,	m_MapPos.Y + 1) ||
						CheckLava(m_MapPos.X    ,	m_MapPos.Y - 1);

	//—nŠâ‚ÉG‚ê‚Ä‚¢‚½‚ç
	if (TouchOnLava || m_isChangeBlock)
	{
		m_bEffectFlg = false;
		CWater* pWater = new CWater(m_pMyStage, m_MapPos.X, m_MapPos.Y);
		m_pMyStage->ChangeBlock(pWater);
	}
}

void CIce::Draw()
{
	FloatSize size = { 0.5f, 0.5f, 0.5f };
	float angle[3] = { 0.0f, 0.0f, 0.0f };

	MODELDRAW_SENDDATA("Ice", m_DrawPos, size, angle);
}

void CIce::CollisionNavigate()
{
	if (m_pMyStage->GetPileBanker()->GetHeet())
	{
		m_bEffectFlg = false;
		m_isChangeBlock = true;
		m_Slipped = true;
	}
}
