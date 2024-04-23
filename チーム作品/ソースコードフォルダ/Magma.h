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
		ENVIRONMENT_NO,	//あいていない
		ENVIRONMENT_TO_STONE,	//石になる
		ENVIRONMENT_FLOW,	//一番下で落ちていく
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
	void AccumulatesAnime();	//水の溜まっているアニメ
	void FlowAnime();			//Playerの場所に水が落ちる
private:
	constexpr static DirectX::XMFLOAT3 m_scale = { 0.5f,0.5f,0.5f };
	Block_Base* CheckRight;
	Block_Base* CheckLeft;
	Block_Base* CheckUnder;
	Block_Base* CheckOver;
	DirectX::XMFLOAT3 m_scaleCorrVal;
	DirectX::XMFLOAT3 m_DrawPosCorrVal;	//水の溜まっている時の補正値
	ENVIRONMENT env;
	GO go;
	ICE_RLUO ice;
	const static int m_MoveFrame = 40;	//移動にかかるフレーム 
	const static int m_n = 8;	//Flowに入ってからプレイヤーとの判定を取るフレームの修正用
	bool m_bOneCheck;
	bool m_bDrawPosMoveNow;	//Draw座標を変換中ならtrueにしてMap座標を変換しない
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
