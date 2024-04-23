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
	void FrontDraw();	//�v���C���[�̑O�ɕ`��
	void BeyondDraw();	//�v���C���[�̉��ɕ`��

private:
	enum State
	{
		STATE_RAND,		//�o�邩�ǂ������I
		STATE_POPUP,	//�o����܂�
		STATE_WAIT,		//�o�����Ă����
		STATE_MONOLOGUE,	//�������Ă���
		STATE_RESET		//����������RAND�ɖ߂�
	};

	struct MOLE
	{
		Image2D* m_pMole;	//���O��
		int	m_nFrame;
		int m_nGuaranteeFrame;
		State m_State;
		bool m_bAround;	//�O����납�Atrue�őO�ɂ��܂�
	};

	std::vector<MOLE> m_Mole;
	constexpr static int MAX_MOLE = 2;		//�����ɏo�����郂�O���ő吔
	constexpr static int ANIME_Frame = 7;	//�R�}����ɂ���Ԋu�t���[��
	constexpr static int WAIT_FullFrame = 60;	//���O�����o�����Ă���t���[��
	constexpr static int SELECTED_Frame = 14;	//���I���s���Ԋu�t���[��
	constexpr static int PRPBABILITY = 100;	//���O�����o������m��(1 / X)��"SELECTED_Frame"�t���[�����Ƃɒ��I
	constexpr static int PRPBABILITY_GUARANTEE = 300;	//���O���o���̓V���
};


#endif // !___SELECT_MOLE_H___
