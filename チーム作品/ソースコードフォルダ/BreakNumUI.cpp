#include "BreakNumUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

//********** �萔��` **********
#define MAX_BREAK_UI        (2)   // UI�̌���
#define ANIM_BREAK_FRAME    (2)   // �A�j���[�V������1�R�}�̃t���[����
#define ANIM_BREAK_SPLIT_X (11)	  // �摜�̕������i���j
#define ANIM_BREAK_SPLIT_Y  (1)   // �摜�̕������i�c�j


//--------------------
// �R���X�g���N�^
//--------------------
BreakNumUI::BreakNumUI()
{
	m_pSprite = new SpriteManager;
	

	for (int i = 0; i < MAX_BREAK_UI; i++)
	{
		// �摜�̈ʒu
		g_BreakUI[i].m_Pos = { 130.0f + (i * 60.0f), 657.0f };
		//g_BreakUI[i].m_Pos = { 1113.0f, 360.0f - (i * 50.0f) };

		// �摜�̃T�C�Y
		g_BreakUI[i].m_Size = { 65.0f, -70.0f };

		// �摜�̊p�x
		g_BreakUI[i].m_Angle = { 0.0f, 0.0f, 0.0f };

		// �摜�̊g�k
		g_BreakUI[i].m_Scale = { 1.0f, 1.0f, 1.0f };

		// �摜�̍����UV���W
		g_BreakUI[i].posTexCoord = { 0.0f, 0.0f };

		// �摜�̕�����
		g_BreakUI[i].sizeTexCoord.x = 1.0f / (float)ANIM_BREAK_SPLIT_X;
		g_BreakUI[i].sizeTexCoord.y = 1.0f;

		// �摜�̎g�p���
		g_BreakUI[i].use = true;

		// �t���[����
		g_BreakUI[i].frame = 0;

		// �摜�̉��R�}�ڂ�
		g_BreakUI[i].currentAnimNo = 0;

		// �e�N�X�`���ǂݍ���
		LoadTextureFromFile("Assets/2D/number_blue.png", &g_BreakUI[i].m_pBreakUI);
	}

	// �ł��t���񐔏�����
	m_BreakCnt = 0;
}


//--------------------
// �f�X�g���N�^
//--------------------
BreakNumUI::~BreakNumUI()
{
	for (int i = 0; i < MAX_BREAK_UI; i++)
	{
		g_BreakUI[i].m_pBreakUI->Release();
	}

	delete m_pSprite;
}


//--------------------
// �`��
//--------------------
void BreakNumUI::Draw()
{
	for (int i = 0; i < MAX_BREAK_UI; i++)
	{
		m_pSprite->Draw(
			g_BreakUI[i].m_Pos, g_BreakUI[i].m_Size, g_BreakUI[i].m_Angle,
			g_BreakUI[i].posTexCoord, g_BreakUI[i].sizeTexCoord,
			{ 1.4f,1.4f,1.4f,1.0f },
			g_BreakUI[i].m_pBreakUI);
	}

	Sprite::SetUVPos({ 0.0f, 0.0f });
	Sprite::SetUVScale({ 1.0f, 1.0f });
}


//--------------------------------------
// �j�󐔑���
// �����Fint num  �j�󂵂��u���b�N�̐�
//--------------------------------------
void BreakNumUI::AddNum(int num)
{

		m_BreakCnt += 1;

		// ����␳
		if (99 < m_BreakCnt)
		{
			m_BreakCnt = 99;
		}

		// �e�N�X�`�����W�X�V
		BreakNumUI::UpdateTexCoord();

}



//----------------------------------
// �摜��UV���W�X�V
//----------------------------------
void BreakNumUI::UpdateTexCoord()
{
	int tmp = m_BreakCnt;

	for (int i = MAX_BREAK_UI - 1; 0 <= i; i--)
	{
		// tmp�̒l�̉��ꌅ�擾
		g_BreakUI[i].currentAnimNo = tmp % 10;

		// �e�N�X�`�����W�X�V
		g_BreakUI[i].posTexCoord.x = g_BreakUI[i].sizeTexCoord.x *
			(g_BreakUI[i].currentAnimNo % ANIM_BREAK_SPLIT_X);

		g_BreakUI[i].posTexCoord.y = g_BreakUI[i].sizeTexCoord.y *
			(g_BreakUI[i].currentAnimNo / ANIM_BREAK_SPLIT_X);

		// �����Ƃ�
		tmp /= 10;
	}
}


//----------------------------------
// �u���b�N�j�󐔎擾
//----------------------------------
int BreakNumUI::GetBreckCnt()
{
	return m_BreakCnt;
}
