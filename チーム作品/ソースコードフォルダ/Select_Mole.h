#ifndef ___SELECT_MOLE_H___
#define ___SELECT_MOLE_H___

#include "Image2D.h"
#include <vector>

class Select_Mole
{
public:
	Select_Mole(SpriteManager* pSM);
	~Select_Mole();
	void Update();
	void FrontDraw();	//プレイヤーの前に描画
	void BeyondDraw();	//プレイヤーの奥に描画

private:
	enum State
	{
		STATE_RAND,		//出るかどうか抽選
		STATE_POPUP,	//出きるまで
		STATE_WAIT,		//出きっている間
		STATE_MONOLOGUE,	//下がっていく
		STATE_RESET		//初期化してRANDに戻す
	};

	struct MOLE
	{
		Image2D* m_pMole;	//モグラ
		int	m_nFrame;
		int m_nGuaranteeFrame;
		State m_State;
		bool m_bAround;	//前か後ろか、trueで前にします
	};

	std::vector<MOLE> m_Mole;
	constexpr static int MAX_MOLE = 2;		//同時に出現するモグラ最大数
	constexpr static int ANIME_Frame = 7;	//コマ送りにする間隔フレーム
	constexpr static int WAIT_FullFrame = 60;	//モグラが出きっているフレーム
	constexpr static int SELECTED_Frame = 14;	//抽選を行う間隔フレーム
	constexpr static int PRPBABILITY = 100;	//モグラが出現する確率(1 / X)を"SELECTED_Frame"フレームごとに抽選
	constexpr static int PRPBABILITY_GUARANTEE = 300;	//モグラ出現の天井回数
};


#endif // !___SELECT_MOLE_H___
