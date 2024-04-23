#include "knockUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

//********** �萔��` **********
#define MAX_KNOCK_UI     (2)   // UI�̌���
#define ANIM_FRAME    (2)   // �A�j���[�V������1�R�}�̃t���[����
#define ANIM_SPLIT_X (11)	// �摜�̕������i���j
#define ANIM_SPLIT_Y  (1)   // �摜�̕������i�c�j


//--------------------
// �R���X�g���N�^
//--------------------
KnockUI::KnockUI()
{
	m_pSprite = new SpriteManager;

	for (int i = 0; i < MAX_KNOCK_UI; i++)
	{
		// �摜�̈ʒu
		g_KnockUI[i].m_Pos = { 340.0f + (i * 60.0f), 657.0f };
		//g_KnockUI[i].m_Pos = { 1113.0f, 498.0f  - (i * 50.0f) };

		// �摜�̃T�C�Y
		g_KnockUI[i].m_Size = { 65.0f, -70.0f };

		// �摜�̊p�x
		g_KnockUI[i].m_Angle = { 0.0f, 0.0f, 0.0f };

		// �摜�̊g�k
		g_KnockUI[i].m_Scale = { 1.0f, 1.0f, 1.0f };

		// �摜�̍����UV���W
		g_KnockUI[i].posTexCoord = { 0.0f, 0.0f };

		// �摜�̕�����
		g_KnockUI[i].sizeTexCoord.x = 1.0f / (float)ANIM_SPLIT_X;
		g_KnockUI[i].sizeTexCoord.y = 1.0f;

		// �摜�̎g�p���
		g_KnockUI[i].use = true;

		// �t���[����
		g_KnockUI[i].frame = 0;

		// �摜�̉��R�}�ڂ�
		g_KnockUI[i].currentAnimNo = 0;

		// �e�N�X�`���ǂݍ���
		LoadTextureFromFile("Assets/2D/number_blue.png", &g_KnockUI[i].m_pKnockUI);
	}

	// �ł��t���񐔏�����
	m_KnockCnt = 0;


}


//--------------------
// �f�X�g���N�^
//--------------------
KnockUI::~KnockUI()
{
	for (int i = 0; i < MAX_KNOCK_UI; i++)
	{
		g_KnockUI[i].m_pKnockUI->Release();
	}
	
	delete m_pSprite;
}


//--------------------
// �`��
//--------------------
void KnockUI::Draw()
{
	for (int i = 0; i < MAX_KNOCK_UI; i++)
	{
		// Sprite��UV���𑗂�
		Sprite::SetUVPos(g_KnockUI[i].posTexCoord);
		Sprite::SetUVScale(g_KnockUI[i].sizeTexCoord);

		m_pSprite->Draw(
			g_KnockUI[i].m_Pos, g_KnockUI[i].m_Size, g_KnockUI[i].m_Angle,
			g_KnockUI[i].posTexCoord, g_KnockUI[i].sizeTexCoord, { 1.5f,1.5f,1.5f,1.0f },
			g_KnockUI[i].m_pKnockUI);
	}

	Sprite::SetUVPos({ 0.0f, 0.0f });
	Sprite::SetUVScale({1.0f, 1.0f});
}


//----------------------------------
// �ł��t���񐔑���
// �����Fint num  �ł��t������
//----------------------------------
void KnockUI::AddKnock(int num)
{
	m_KnockCnt += num;

	// ����␳
	if (99 < m_KnockCnt)
	{
		m_KnockCnt = 99;
	}

	// �e�N�X�`�����W�X�V
	KnockUI::UpdateTexCoord();
}


//----------------------------------
// �摜��UV���W�X�V
//----------------------------------
void KnockUI::UpdateTexCoord()
{
	int tmp = m_KnockCnt;

	for (int i = MAX_KNOCK_UI - 1; 0 <= i; i--)
	{
		// tmp�̒l�̉��ꌅ�擾
		g_KnockUI[i].currentAnimNo = tmp % 10;

		// �e�N�X�`�����W�X�V
		g_KnockUI[i].posTexCoord.x = g_KnockUI[i].sizeTexCoord.x *
			(g_KnockUI[i].currentAnimNo % ANIM_SPLIT_X);

		g_KnockUI[i].posTexCoord.y = g_KnockUI[i].sizeTexCoord.y *
			(g_KnockUI[i].currentAnimNo / ANIM_SPLIT_X);

		// �����Ƃ�
		tmp /= 10;
	}
}


//----------------------------------
// �ł��t���񐔎擾
//----------------------------------
int KnockUI::GetKnockCnt()
{
	return m_KnockCnt;
}
