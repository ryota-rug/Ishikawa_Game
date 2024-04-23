#ifndef ___SCENE_SELECT_H___
#define ___SCENE_SELECT_H___

#include "Scene.h"
#include "Image2D.h"
#include "Sound.h"
#include "Game3D.h"

#include "Select_StageNumber.h"
#include "Select_Score.h"
#include "Select_Mole.h"
#include "Select_Bat.h"
#include "Select_Block.h"



class CScene_Select : public CScene
{
public:
	CScene_Select(SCENE beforeScene);
	~CScene_Select() override;
	void Update() override;
	void Draw() override;

private:
	Image2D* m_pGround1;	//地面1
	Image2D* m_pBack1;		//背景1

	Image2D* m_pFront2;		//前景2
	Image2D* m_pGround2;	//地面2
	Image2D* m_pBack2;		//背景2

	Image2D* m_pFront3;		//前景3
	Image2D* m_pGround3;	//地面3
	Image2D* m_pBack3;		//背景3

	Image2D* m_pRobo;
	Image2D* m_pHole;	//ステージ入口

	Select_StageNumber* m_pStageNum;	//ステージ番号
	Select_Score* m_pScore;	//ステージ情報
	Select_Mole* m_pMole;	//モグラ
	Select_Bat* m_pBat;		//コウモリ
	Select_Block* m_pBlock;


	BGM* m_pBGM;
	float m_bgmVolume;

	SE* m_pSESelect;
	SE* m_pSEDetermine;
	SE* m_pSECancel;

	float m_targetPos;
	bool m_isStageChange;

private:
	bool AutoUpdate();
	void InputUpdate();
};

#endif // !___SCENE_SELECT_H___

