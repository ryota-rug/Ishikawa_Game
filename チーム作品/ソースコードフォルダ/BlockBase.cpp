#include "BlockBase.h"
#include "StageBase.h"
#include "XboxKeyboard.h"

const float Block_Base::BlockSize = 50.0f;

Block_Base::Block_Base(Stage_Base* MyStage,int PosX,int PosY)
	:m_Type(BLOCK_NONE),
	m_pMyStage(MyStage),
	m_MapPos({PosX,PosY}),
	m_IsDestroy(false),
	m_Invincibility(false),	//���G
	m_Slipped(false)			//���蔲��
{

}
Block_Base::~Block_Base()
{

}

//�p���p�̍X�V����
void Block_Base::Update()
{

}

//�p���p�̕`�揈��
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

//�̗͂������Ă���
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

//�}�b�v�̏ꏊ�������Ă���
IntPos Block_Base::GetMap()
{
	return m_MapPos;
}

//�`��̃|�W�V�����������Ă���
FloatPos Block_Base::GetPos()
{
	return m_DrawPos;
}

void Block_Base::SetMap(int X, int Y)
{
	m_MapPos.X = X;
	m_MapPos.Y = Y;
}
//�}�b�v�̏ꏊ��ݒ�
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

bool Block_Base::Get_Invincibility()		//���G����
{
	return m_Invincibility;
}

bool Block_Base::Get_Slipped()				//���蔲������
{
	return m_Slipped;
}

//�u���b�N���Y�ɓ��������Ƃ��ɌĂ΂��
void Block_Base::CollisionNavigate()
{
	
}

//�u���b�N���Y�ɓ��������Ƃ��ɌĂ΂��
void Block_Base::CollisionBrock()
{
	m_pMyStage->GetBreakNum(1);
}

void Block_Base::Set_DidUpdate(bool Set)//�A�b�v�f�[�g���邩
{
	m_DidUpdate	= Set;
}
bool Block_Base::Get_DidUpdate()	//���̃t���[���ŃA�b�v�f�[�g������
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