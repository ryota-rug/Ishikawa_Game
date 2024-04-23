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
		ENVIRONMENT_NO,	//あいていない
		ENVIRONMENT_DESTROY,	//削除
		ENVIRONMENT_FLOW,	//一番下で落ちていく
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
	void AccumulatesAnime();	//水の溜まっているアニメ
	void FlowAnime();			//Playerの場所に水が落ちる
private:
	constexpr static DirectX::XMFLOAT3 m_scale = {0.5f,0.5f,0.5f};
	Block_Base* CheckRight;
	Block_Base* CheckLeft;
	Block_Base* CheckUnder;
	Block_Base* CheckOver;
	DirectX::XMFLOAT3 m_scaleCorrVal;
	DirectX::XMFLOAT3 m_DrawPosCorrVal;	//水の溜まっている時の補正値
	ENVIRONMENT env;
	GO go;
	const static int m_MoveFrame = 40;	//移動にかかるフレーム 
	bool m_bOneCheck;
	bool m_bDrawPosMoveNow;	//Draw座標を変換中ならtrueにしてMap座標を変換しない
	bool m_bFlow;	//
	int m_nFrame;
	int m_nFrameDest;	//マグマと接触時の
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
