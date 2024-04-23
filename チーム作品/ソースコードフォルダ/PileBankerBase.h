//#pragma once
#ifndef PILE_BANKER_H
#define PILE_BANKER_H
#include "Position_struct.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "Sound.h"

class Stage_Base;

class PileBanker
{
public:
	enum PileDirection
	{
		UP = 0,
		RIGHT,
		DOWN,
		LEFT
	};

	enum PileSelect
	{
		PILE_PREPARATION = 0,
		PILE_CHAGE,
		PILE_IN,
		PILE_HITSTOP,
		PILE_INTERPOLATION,
		PILE_ATTACK,
		PILE_STOP,
		PILE_BACK,
		PILE_GAMEOVER,
		PILE_DESTROY,
		MAX
	};

	enum PileDrawTYPE
	{
		PILE_DEFAULT = 0,
		PILE_BIBLATION
	};

public:
	PileBanker(Stage_Base* MyStage);
	virtual ~PileBanker();
	virtual void Update();
	virtual void Draw();
	virtual void UIDraw();
	IntPos GetMap();
	FloatPos GetDraw();
	bool GetHeet();
	int GetAttack();
	float GetSpeed();
	FloatPos GetBasePos();
	PileSelect Get_PileState();
	int Get_Line();
	bool GetDestroy();
	PileDirection GetDirection();
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
	void StopBanker();

protected:
	//ステータス-----------------------------
	int m_Attack;
	float m_TempAttack;
	int m_StopCount;
	bool m_Heet;
	const int m_MaxAttack;
	//動き面---------------------------------
	PileSelect PileState;	//今やっている動き
	const float m_Block_BunkerDistance;	//ブロックと杭の間の長さ
	const FloatPos m_BasePosition;	//杭の一番左で一番下のポジションとなるベースポジション
	float m_ShotSpeed;	//杭を打つスピード
	float m_PullSpeed;	//杭を打つスピード
	float m_CountSpeed;	//ブロックのサイズを超えたらマップを1移動している
	int m_LineNum;		//今どこのレーンを選んでいるか
	FloatPos m_DrawPos;	//描画するポジション
	IntPos m_MapPos;	//マップ上のポジション
	Stage_Base* m_pMyStage;	//ステージ情報を入れる
	PileDirection m_Direction;	//打っている方向
	bool m_Destory;	//消すか
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
	bool Collision_Check_EXE;
	FloatPos m_OldPos;
	int m_HitStopCount;
	PileDrawTYPE m_PileDrawState;

	SE* m_pChageSE;
	SE* m_pUtuSE;
	SE* m_pAttackSE;
	SE* m_pStopSE;
};

#endif // !PILE_BANKER_H
