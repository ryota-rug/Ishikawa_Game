#ifndef __MAGMA_H__
#define __MAGMA_H__

#include "BlockBase.h"
#include "Effect_Manager.h"


class CMagma : public Block_Base
{
public:
	CMagma(Stage_Base* MyStage, int PosX, int PosY);
	~CMagma();

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
		ENVIRONMENT_TO_STONE,	//�΂ɂȂ�
		ENVIRONMENT_FLOW,	//��ԉ��ŗ����Ă���
		ENVIRONMENT_MAX
	};
	enum GO
	{
		GO_STAY,
		GO_RIGHT,
		GO_LEFT
	};
	enum ICE_RLUO
	{
		NO,
		RIGHT,
		LEFT,
		UNDER,
		OVER
	};
private:
	void EnvironmentTrans();
	void DrawPosMove();
	void AccumulatesAnime();	//���̗��܂��Ă���A�j��
	void FlowAnime();			//Player�̏ꏊ�ɐ���������
private:
	constexpr static DirectX::XMFLOAT3 m_scale = { 0.5f,0.5f,0.5f };
	Block_Base* CheckRight;
	Block_Base* CheckLeft;
	Block_Base* CheckUnder;
	Block_Base* CheckOver;
	DirectX::XMFLOAT3 m_scaleCorrVal;
	DirectX::XMFLOAT3 m_DrawPosCorrVal;	//���̗��܂��Ă��鎞�̕␳�l
	ENVIRONMENT env;
	GO go;
	ICE_RLUO ice;
	const static int m_MoveFrame = 40;	//�ړ��ɂ�����t���[�� 
	const static int m_n = 8;	//Flow�ɓ����Ă���v���C���[�Ƃ̔�������t���[���̏C���p
	bool m_bOneCheck;
	bool m_bDrawPosMoveNow;	//Draw���W��ϊ����Ȃ�true�ɂ���Map���W��ϊ����Ȃ�
	bool m_bFlow;	//
	int m_nFrame;
	int m_nFrameCha;
	int m_nLengthR;
	int m_nLengthL;
	bool m_bHoleR;
	bool m_bHoleL;

	bool m_bPlayerHit;
	int m_nEffeckFrame = 0;
	Effekseer::Handle m_MagmaHandle;
	Effekseer::Handle m_MoveHandle;
};

#endif //!__MAGMA_H__
