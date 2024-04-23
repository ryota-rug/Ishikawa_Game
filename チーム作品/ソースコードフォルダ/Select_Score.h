#ifndef ___SELECT_SCORE_H___
#define ___SELECT_SCORE_H___

#include "Image2D.h"
#include "SpriteManager.h"
#include "SaveLoad.h"

class Select_Score
{
public:
	Select_Score(SpriteManager* pSM);
	~Select_Score();
	void Update();
	void Draw();

private:
	Image2D* m_pStage;	//�X�e�[�W���j�^�[
	Image2D* m_pLetterUTITUKESUU;	//���́u�E�`�c�P�X�E�v
	Image2D* m_pLetterBEST;			//���́u�x�X�g�v
	Image2D* m_pLetterHAKAISUU;		//���́u�n�J�C�X�E�v
	Image2D* m_pNumber;	//����

	SaveData m_data[15];
};


#endif // !___SELECT_SCORE_H___
