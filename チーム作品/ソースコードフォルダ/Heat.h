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

	int CheckLeft(int distance);	//左下にブロックがあればそこまでの距離を返す
	int CheckRight(int distance);	//右下にブロックがあればそこまでの距離を返す

	int CheckLeftWater(int distance);		//左に水があればそこまでの距離を返す
	int CheckRightWater(int distance);	//右に水があればそこまでの距離を返す
	void CheckCollisionWater();
	void CheckCollisionMagma();
	void MoveHeat(int leftDis, int rightDis);	//水の場所へ移動
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void FollowWater(); // 水についていく
	void MoveAngle();

	enum HEATSTATE
	{
		HEAT_IN,		// マップ配列の中にある
		HEAT_OUT
	};

private:
	bool m_bDrawPosMoveNow;	//Draw座標を変換中ならtrueにしてMap座標を変換しない
	HEATSTATE m_State;
	const float Down_Speed = 1 / 60;
	const float Move_Speed = 1 / 60;
	bool moving_right;
	bool moving_left;
	bool moving_angle_L;	//左に傾いてる最中
	bool moving_angle_R;	//右に傾いてる最中
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

