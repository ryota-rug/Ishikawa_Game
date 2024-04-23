#ifndef __WATER_H__
#define __WATER_H__

#include "BlockBase.h"
#include "Effect_Manager.h"
#include "Sound.h"

class CWater : public Block_Base
{
public:
	CWater(Stage_Base* MyStage, int PosX, int PosY);
	~CWater();

	void Update() override;
	void Draw() override;
	void Update_Refuge() override;
public:
	enum ENVIRONMENT
	{
		ENVIRONMENT_DOWN,
		ENVIRONMENT_BOTH_SIDES,
		ENVIRONMENT_RIGHT,
		ENVIRONMENT_LEFT,
		ENVIRONMENT_NO,	//�����Ă��Ȃ�
		ENVIRONMENT_DESTROY,	//�폜
		ENVIRONMENT_FLOW,	//��ԉ��ŗ����Ă���
		ENVIRONMENT_MAX
	};
	enum GO
	{
		GO_STAY,
		GO_RIGHT,
		GO_LEFT
	};
private:
	void EnvironmentTrans();
	void DrawPosMove();
	void AccumulatesAnime();	//���̗��܂��Ă���A�j��
	void FlowAnime();			//Player�̏ꏊ�ɐ���������
private:
	constexpr static DirectX::XMFLOAT3 m_scale = {0.5f,0.5f,0.5f};
	Block_Base* CheckRight;
	Block_Base* CheckLeft;
	Block_Base* CheckUnder;
	Block_Base* CheckOver;
	DirectX::XMFLOAT3 m_scaleCorrVal;
	DirectX::XMFLOAT3 m_DrawPosCorrVal;	//���̗��܂��Ă��鎞�̕␳�l
	ENVIRONMENT env;
	GO go;
	const static int m_MoveFrame = 40;	//�ړ��ɂ�����t���[�� 
	bool m_bOneCheck;
	bool m_bDrawPosMoveNow;	//Draw���W��ϊ����Ȃ�true�ɂ���Map���W��ϊ����Ȃ�
	bool m_bFlow;	//
	int m_nFrame;
	int m_nFrameDest;	//�}�O�}�ƐڐG����
	int m_nFrameEffect = 0;
	int m_nLengthR;
	int m_nLengthL;
	bool m_bHoleR;
	bool m_bHoleL;
	Effekseer::Handle m_MoveHandle;
	SE* m_pHitSE;
	bool m_TurnHit;
	Effekseer::Handle m_SorkHandle;
};


#endif // !__WATER_H__
