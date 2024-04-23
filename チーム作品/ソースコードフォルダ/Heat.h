#ifndef __HEAT_H__
#define __HEAT_H__

#include "ItemBase.h"
#include "BlockBase.h"
#include "Sound.h"

class CHeat : public CItemBase
{
public:
	CHeat(Stage_Base* MyStage, int PosX, int PosY);
	~CHeat();
	void Update();
	void Draw();
	void RefugeUpdate();

	int CheckLeft(int distance);	//�����Ƀu���b�N������΂����܂ł̋�����Ԃ�
	int CheckRight(int distance);	//�E���Ƀu���b�N������΂����܂ł̋�����Ԃ�

	int CheckLeftWater(int distance);		//���ɐ�������΂����܂ł̋�����Ԃ�
	int CheckRightWater(int distance);	//�E�ɐ�������΂����܂ł̋�����Ԃ�
	void CheckCollisionWater();
	void CheckCollisionMagma();
	void MoveHeat(int leftDis, int rightDis);	//���̏ꏊ�ֈړ�
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void FollowWater(); // ���ɂ��Ă���
	void MoveAngle();

	enum HEATSTATE
	{
		HEAT_IN,		// �}�b�v�z��̒��ɂ���
		HEAT_OUT
	};

private:
	bool m_bDrawPosMoveNow;	//Draw���W��ϊ����Ȃ�true�ɂ���Map���W��ϊ����Ȃ�
	HEATSTATE m_State;
	const float Down_Speed = 1 / 60;
	const float Move_Speed = 1 / 60;
	bool moving_right;
	bool moving_left;
	bool moving_angle_L;	//���ɌX���Ă�Œ�
	bool moving_angle_R;	//�E�ɌX���Ă�Œ�
	float m_angleZ;
	bool bWater_InFlg;
	bool bWaterFlg = false;
	bool moving_down;
	int m_PileLineNum;
	SE* m_pGet_HeetSE;
	SE* m_pBreak_HeetSE;
	bool m_BreakAniFrame = 0;
};

#endif // __HEAT_H__

