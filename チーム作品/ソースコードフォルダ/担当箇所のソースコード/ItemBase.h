#ifndef __ITEM_BASE__
#define __ITEM_BASE__
#include "StageBase.h"
#include "Position_struct.h"
#include "CameraBase.h"
#include "BlockBase.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"

class Stage_Base;

class CItemBase
{
public :
	// �A�C�e���̎��
	enum ITEM_TYPE
	{
		NONE,
		JEWELY,
		HEAT
	};
	// �X�e�[�W�z��̒����O��
	enum ITEMSTATE
	{
		ITEM_IN,
		ITEM_OUT
	};
	// �A�C�e���̌X��
	enum ITEM_ANGLE
	{
		RIGHT,
		LEFT
	};
	// �����ꏊ�ɂ���A�C�e���̐�
	enum ITEM_COINCIDE
	{
		ONE,
		DOUBLE,
		TRIPLE
	};

public:
	static const float ItemSize;	//�������̃A�C�e���̃T�C�Y
	CItemBase(Stage_Base* MyStage, int PosX, int PosY);
	virtual ~CItemBase();
	virtual void Update() {}
	virtual void Draw() {}
	virtual void RefugeUpdate() {}
	IntPos GetMap();			// �}�b�v��(StageBase�̃}�b�v�z��)�ł̃|�W�V�����擾�֐�
	FloatPos GetPos();			// �`���ł̃|�W�V�����擾�֐�
	void SetMap(int X, int Y);
	void SetPos(float X, float Y, float Z);
	void Destroy();
	bool Get_Destroy();			// �j��t���O�擾�֐�
	ITEM_TYPE GetType();		// �A�C�e���̎�ގ擾�֐�
	ITEM_ANGLE GetAngle();		// �A�C�e���̌X���擾�֐�
	void SetAngle(ITEM_ANGLE num);		// �Z�b�g�֐�
	void CheckCollisionMagma();	// �}�O�}�Ƃ̓����蔻��
	void Set_DidUpdate(bool Set);				//�A�b�v�f�[�g���邩
	bool Get_DidUpdate();			//���̃t���[���ŃA�b�v�f�[�g������
	void Set_ModelManager(CModelManager* pModelManager);
	void Set_CameraManager(C_CameraManager* pCameraManager);
	void AddCoinCide(int num) { m_CoinCide += num; }
	int GetCoinCide() { return m_CoinCide; }

private:
	bool m_DidUpdate;

protected:
	ITEM_TYPE m_Type;		//�A�C�e���̎��
	ITEM_ANGLE m_Angle;		// �A�C�e���̌X��
	Stage_Base* m_pMyStage;
	IntPos m_MapPos;		//�}�b�v���
	FloatPos m_DrawPos;		//�`�悷��|�W�V����
	bool m_IsDestroy;
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
	static int m_AngleNum; // 0�͉E��1�͍��ɌX������
	int m_CoinCide = 1; // �����ꏊ�ɂ���A�C�e����
};

#endif //__ITEM_BASE__