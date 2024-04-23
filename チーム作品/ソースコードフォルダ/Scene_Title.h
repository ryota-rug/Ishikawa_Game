#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene.h"
#include "Image2D.h"
#include "Sound.h"

class CScene_Title : public CScene
{
public:
	CScene_Title();
	~CScene_Title();
	void Update();
	void Draw();


private:
	enum SELECT
	{
		SELECT_STAGESELECT = 125,
		SELECT_END = 215
	};

	Image2D* m_pMoveBack[2]; //�w�i (��������)
	Image2D* m_pBack;		 //�w�i (�����Ȃ�����)

	Image2D* m_pLogo;	 //�^�C�g�����S
	Image2D* m_pSelect;	 //���

	Image2D* m_pLetterSelect;		 //���́u�X�e�[�W�Z���N�g�v
	Image2D* m_pLetterOwaru;		 //���́u�I�����v
	Image2D* m_pLetterSOUUTITUKE;	 //���́u�\�E�E�`�c�P�X�E�v
	Image2D* m_pLetterSOUHAKAI;		 //���́u�\�E�n�J�C�X�E�v

	Image2D* m_pRobo;	//���{�b�g
	Image2D* m_pNum;	//����

	BGM* m_pBGM;
	SE* m_pSESelect;
	SE* m_pSEDetermine;

	bool m_determine;
};

#endif // !SCENE_TITLE_H

