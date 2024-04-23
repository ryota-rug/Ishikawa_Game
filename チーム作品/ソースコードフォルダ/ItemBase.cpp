#include "ItemBase.h"


const float CItemBase::ItemSize = 40.0f;
int CItemBase::m_AngleNum = 0;

CItemBase::CItemBase(Stage_Base * MyStage, int PosX, int PosY)
	:m_pMyStage(MyStage),
	m_MapPos({ PosX,PosY }),
	m_IsDestroy(false),
	m_pModelManager(nullptr),
	m_pCameraManager(nullptr),m_Angle(ITEM_ANGLE::RIGHT)
{

}

CItemBase::~CItemBase()
{
}

//マップの場所を持ってくる
IntPos CItemBase::GetMap()
{
	return m_MapPos;
}

//描画のポジションを持ってくる
FloatPos CItemBase::GetPos()
{
	return m_DrawPos;
}

void CItemBase::SetMap(int X, int Y)
{
	m_MapPos.X = X;
	m_MapPos.Y = Y;
}

//マップの場所を設定
void CItemBase::SetPos(float X, float Y, float Z)
{
	m_DrawPos.X = X;
	m_DrawPos.Y = Y;
	m_DrawPos.Z = Z;
}

void CItemBase::Destroy()
{
	m_IsDestroy = true;
}

bool CItemBase::Get_Destroy()
{
	return m_IsDestroy;
}

CItemBase::ITEM_TYPE CItemBase::GetType()
{
	return m_Type;
}

CItemBase::ITEM_ANGLE CItemBase::GetAngle()
{
	return m_Angle;
}
void CItemBase::SetAngle(ITEM_ANGLE num)
{
	m_Angle = num;
}

void CItemBase::CheckCollisionMagma()
{
	// 上にマグマがあったら
	if (m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y - 1)->GetType() == Block_Base::BLOCK_MAGMA)
	{
		Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y - 1);
		if (m_DrawPos.Y + CItemBase::ItemSize * 0.5f > pBlock->GetPos().Y - pBlock->BlockSize * 0.5f)
		{
			m_IsDestroy = true;
		}
	}

	// 下にマグマがあったら
	if (m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y + 1)->GetType() == Block_Base::BLOCK_MAGMA)
	{
		Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X, m_MapPos.Y + 1);
		if (m_DrawPos.Y - CItemBase::ItemSize * 0.5f < pBlock->GetPos().Y + pBlock->BlockSize * 0.5f)
		{
			m_IsDestroy = true;
		}
	}

	// 右にマグマがあったら
	if (m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA)
	{
		Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X + 1, m_MapPos.Y);
		if (m_DrawPos.X + CItemBase::ItemSize * 0.5f > pBlock->GetPos().X - pBlock->BlockSize * 0.5f)
		{
			m_IsDestroy = true;
		}
	}

	// 左にマグマがあったら
	if (m_pMyStage->GetBlockInfo(m_MapPos.X - 1, m_MapPos.Y)->GetType() == Block_Base::BLOCK_MAGMA)
	{
		Block_Base* pBlock = m_pMyStage->GetBlockInfo(m_MapPos.X - 1, m_MapPos.Y);
		if (m_DrawPos.X - CItemBase::ItemSize * 0.5f < pBlock->GetPos().X + pBlock->BlockSize * 0.5f)
		{
			m_IsDestroy = true;
		}
	}
}

void CItemBase::Set_DidUpdate(bool Set)				//アップデートするか
{
	m_DidUpdate = Set;
}

bool CItemBase::Get_DidUpdate()			//今のフレームでアップデートしたか
{
	return m_DidUpdate;
}

void CItemBase::Set_ModelManager(CModelManager* pModelManager)
{
	m_pModelManager = pModelManager;
}

void CItemBase::Set_CameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}