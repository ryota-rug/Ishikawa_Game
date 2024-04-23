#include "BlockBase.h"
#include "StageBase.h"
#include "XboxKeyboard.h"

const float Block_Base::BlockSize = 50.0f;

Block_Base::Block_Base(Stage_Base* MyStage,int PosX,int PosY)
	:m_Type(BLOCK_NONE),
	m_pMyStage(MyStage),
	m_MapPos({PosX,PosY}),
	m_IsDestroy(false),
	m_Invincibility(false),	//無敵
	m_Slipped(false)			//すり抜け
{

}
Block_Base::~Block_Base()
{

}

//継承用の更新処理
void Block_Base::Update()
{

}

//継承用の描画処理
void Block_Base::Draw()
{

}

void Block_Base::Update_Refuge()
{

}

Block_Base::BLOCK_TYPE 	Block_Base::GetType()
{
	return m_Type;
}

//体力を持ってくる
int Block_Base::GetHP()
{
	return m_HP;
}

int Block_Base::GetDEF()
{
	return m_DEF;
}

int Block_Base::Damage(int Num)
{
	m_HP -= Num;
	return m_HP;
}

//マップの場所を持ってくる
IntPos Block_Base::GetMap()
{
	return m_MapPos;
}

//描画のポジションを持ってくる
FloatPos Block_Base::GetPos()
{
	return m_DrawPos;
}

void Block_Base::SetMap(int X, int Y)
{
	m_MapPos.X = X;
	m_MapPos.Y = Y;
}
//マップの場所を設定
void Block_Base::SetPos(float X, float Y,float Z)
{
	m_DrawPos.X = X;
	m_DrawPos.Y = Y;
	m_DrawPos.Z = Z;
}

void Block_Base::Destroy()
{
	m_IsDestroy = true;
}

bool Block_Base::Get_Invincibility()		//無敵判定
{
	return m_Invincibility;
}

bool Block_Base::Get_Slipped()				//すり抜け判定
{
	return m_Slipped;
}

//ブロックが杭に当たったときに呼ばれる
void Block_Base::CollisionNavigate()
{
	
}

//ブロックが杭に当たったときに呼ばれる
void Block_Base::CollisionBrock()
{
	m_pMyStage->GetBreakNum(1);
}

void Block_Base::Set_DidUpdate(bool Set)//アップデートするか
{
	m_DidUpdate	= Set;
}
bool Block_Base::Get_DidUpdate()	//今のフレームでアップデートしたか
{
	return m_DidUpdate;
}

bool Block_Base::Get_Destroy()
{
	return m_IsDestroy;
}

void Block_Base::Set_ModelManager(CModelManager* pModelManager)
{
	m_pModelManager = pModelManager;
}

void Block_Base::Set_CameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}