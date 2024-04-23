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
	Image2D* m_pGround1;	//�n��1
	Image2D* m_pBack1;		//�w�i1

	Image2D* m_pFront2;		//�O�i2
	Image2D* m_pGround2;	//�n��2
	Image2D* m_pBack2;		//�w�i2

	Image2D* m_pFront3;		//�O�i3
	Image2D* m_pGround3;	//�n��3
	Image2D* m_pBack3;		//�w�i3

	Image2D* m_pRobo;
	Image2D* m_pHole;	//�X�e�[�W����

	Select_StageNumber* m_pStageNum;	//�X�e�[�W�ԍ�
	Select_Score* m_pScore;	//�X�e�[�W���
	Select_Mole* m_pMole;	//���O��
	Select_Bat* m_pBat;		//�R�E����
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

