#ifndef __JEWELY_H__
#define __JEWELY_H__

#include "ItemBase.h"
#include "BlockBase.h"
#include "Sound.h"
#include "Effect_Manager.h"

// 宝石UI
#include "jewelryUI.h"

class CJewely : public CItemBase
{
public:
	CJewely(Stage_Base* MyStage, int PosX, int PosY);
	~CJewely();
	void Update();
	void Draw();
	void RefugeUpdate();

	int CheckLeft(int distance);	//左下にブロックがあればそこまでの距離を返す
	int CheckRight(int distance);	//右下にブロックがあればそこまでの距離を返す

	int CheckLeftWater(int distance);		//左に水があればそこまでの距離を返す
	int CheckRightWater(int distance);	//右に水があればそこまでの距離を返す
	void CheckCollisionWater();
	void CheckCollisionMagma();
	void MoveJewely(int leftDis, int rightDis);	//水の場所へ移動
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void FollowWater(); // 水についていく
	void MoveAngle();

	enum JEWELYSTATE
	{
		JEWELY_IN,
		JEWELY_OUT
	};

	/*enum ENVIRONMENT_JEWELY
	{
		ENVIRONMENT_JEWELYDOWN,
		ENVIRONMENT__JEWELYBOTH_SIDES,
		ENVIRONMENT_JEWELYRIGHT,
		ENVIRONMENT_JEWELYLEFT,
		ENVIRONMENT_JEWELYNO,
		ENVIRONMENT_JEWELYMAX
	};*/

private:
	int m_nFrame;
	JEWELYSTATE m_State;
	const float m_DownSpeed;
	const float m_MoveSpeed;
	bool bMovingRight;	//  右に動いている最中か
	bool bMovingLeft;	// 左に動いている最中か
	bool bWater_InFlg;		// 水と重なっている最中か
	bool bWaterFlg = false;
	bool bMovingDown;	// 下に動いている最中か
	bool bMovingAngleL;	//左に傾いてる最中
	bool bMovingAngleR;	//右に傾いてる最中
	bool bMagmaFlg = false;
	int m_AniFrame = 0;
	int m_BreakAniFrame = 0;
	int m_nRand = 0;
	float m_angleZ;
	int m_PileLineNum;
	DirectX::XMFLOAT3 m_size = {0.6f,0.6f,0.6f};
	float m_width = 5.0f; // アイテムをかぶせる際の幅

	// SE
	SE* m_pGet_JewelySE;
	SE* m_pBreak_JewelySE;
	Effekseer::Handle m_JewelyHandle;
	Effekseer::ManagerRef m_efkManager;
};

#endif // __JEWELY_H__

