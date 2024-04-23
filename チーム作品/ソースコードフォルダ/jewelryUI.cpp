#include "jewelryUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

#define MAX_JEWELRY     (3)
#define MAX_CUREECTCNT (55)

//---------------------------------
// �R���X�g���N�^
//---------------------------------
JewelryUI::JewelryUI()
	: m_UINum(0),
	  tmp(0)
{
	m_pSprite = new SpriteManager;
	//m_pPlayer = new C_Player;
	
	for (int i = 0; i < MAX_JEWELRY * 2; i++)
	{
		g_Jewelry[i].m_Pos         = { 0.0f, 0.0f};
		g_Jewelry[i].m_Size        = { 0.0f, 0.0f };
		g_Jewelry[i].m_Angle       = { 0.0f,   0.0f,  0.0f };
		g_Jewelry[i].m_StartPos    = { 0.0f, 0.0f };
		g_Jewelry[i].m_EndPos      = { 0.0f, 0.0f };
		g_Jewelry[i].m_ControlPos1 = { 0.0f, 0.0f };
		g_Jewelry[i].m_ControlPos2 = { 0.0f, 0.0f };
		g_Jewelry[i].CurrentCnt = 0;
		g_Jewelry[i].MaxCnt = 90;
		g_Jewelry[i].GetJewelry = false;
		g_Jewelry[i].Use = false;
		g_Jewelry[i].AnimeFlg = false;
	}

}


//--------------------
// �f�X�g���N�^
//--------------------
JewelryUI::~JewelryUI()
{
	for (int i = 0; i < m_UINum; i++)
	{
		g_Jewelry[i].m_pJewelryGet->Release();
		g_Jewelry[i].m_pJewelryNot->Release();
	}
	
	//delete m_pPlayer;
	delete m_pSprite;
}


//----------------------------------------
// ��΂��쐬
// �����Fint num �쐬������UI�̐�
//----------------------------------------
void JewelryUI::MakeJewelryUI(int Num)
{
	// �ۑ��p�ϐ��ɍ쐬����UI�̐�����
	m_UINum = Num;

	for (int i = 0; i < Num * 2; i++)
	{
		if (i < Num)
		{
			g_Jewelry[i].m_Pos = { 1110.0f, 200.0f - (i * 75.0f) };
		}
		else
		{
			g_Jewelry[i].m_Pos = { -1500.0f, 800.0f };
		}

		g_Jewelry[i].m_Size  = { 80.0f, -70.0f };
		g_Jewelry[i].m_Angle = { 0.0f,   0.0f,  10.0f };
		g_Jewelry[i].GetJewelry = false;

		LoadTextureFromFile("Assets/2D/�_�C��_���l��.png", &g_Jewelry[i].m_pJewelryNot);
		LoadTextureFromFile("Assets/2D/�_�C��_�l��.png", &g_Jewelry[i].m_pJewelryGet);
	}

}


//----------------------------------------
// ��΂�UI��؂�ւ���
//----------------------------------------
void JewelryUI::GetJewelryUI()
{
	g_Jewelry[tmp + m_UINum].GetJewelry = true;	
	tmp++;
}


//----------------------------------------
// ��Ύ擾���̃A�j���[�V�����X�V
//----------------------------------------
void JewelryUI::GetMoveJewelry()
{
	for (int i = m_UINum; i < m_UINum * 2; i++)
	{
		// ��΂��擾���Ă����ꍇ
		if (g_Jewelry[i].GetJewelry && !g_Jewelry[i].AnimeFlg)
		{
			// ��x������鏈��
			if (g_Jewelry[i].Use == false)
			{
				//�����̍��W����X�N���[�����W�ɕϊ�����
				m_2DJewelyPos = m_pCameraManager->ChangeScreenPos(m_pPlayer->GetPos());
				// �v���C���[�̌��ݍ��W���擾
				g_Jewelry[i].m_Pos = m_2DJewelyPos;

				// �J�n�n�_�̐ݒ�
				g_Jewelry[i].m_StartPos = m_2DJewelyPos;

				// �I���n�_
				g_Jewelry[i].m_EndPos = g_Jewelry[i - m_UINum].m_Pos;

				// ����_�P
				g_Jewelry[i].m_ControlPos1 = {
					(g_Jewelry[i].m_EndPos.x - g_Jewelry[i].m_StartPos.x) * 0.4f,
					(g_Jewelry[i].m_EndPos.y - g_Jewelry[i].m_StartPos.y) * 0.15f
				};

				// ����_�Q
				g_Jewelry[i].m_ControlPos2 = {
				(g_Jewelry[i].m_EndPos.x - g_Jewelry[i].m_StartPos.x) * 0.3f,
				(g_Jewelry[i].m_EndPos.y - g_Jewelry[i].m_StartPos.y) * 0.03f
				};

				// �t���O�؂�ւ�
				g_Jewelry[i].Use = true;
			}
		

			// �J�E���^�̍X�V
			g_Jewelry[i].CurrentCnt++;

			float Bzier0 = pow(1 - (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt, 3);
			float Bzier1 = 
				 pow(3 * (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt * 
				(pow(1 - (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt, 2)), 3);

			float Bzier2 = 
				 pow(3 * (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt, 2) *
				(1 - (float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt);
			float Bzier3 = pow((float)g_Jewelry[i].CurrentCnt / g_Jewelry[i].MaxCnt, 3);

			// ���W�̍X�V
			g_Jewelry[i].m_Pos.x = (g_Jewelry[i].m_StartPos.x    * Bzier0) +
				                   (g_Jewelry[i].m_ControlPos1.x * Bzier1) +
								   (g_Jewelry[i].m_ControlPos2.x * Bzier2) +
				                   (g_Jewelry[i].m_EndPos.x      * Bzier3);

			g_Jewelry[i].m_Pos.y = (g_Jewelry[i].m_StartPos.y    * Bzier0) +
				                   (g_Jewelry[i].m_ControlPos1.y * Bzier1) +
							       (g_Jewelry[i].m_ControlPos2.y * Bzier2) +
				                   (g_Jewelry[i].m_EndPos.y      * Bzier3);

			// �I������
			if (g_Jewelry[i].m_EndPos.x - 25.0f <= g_Jewelry[i].m_Pos.x &&
				g_Jewelry[i].m_EndPos.x + 25.0f >= g_Jewelry[i].m_Pos.x)
			{
				if (g_Jewelry[i].m_EndPos.y - 25.0f <= g_Jewelry[i].m_Pos.y &&
					g_Jewelry[i].m_EndPos.y + 25.0f >= g_Jewelry[i].m_Pos.y)
				{
					// �ړ����Ɏg�p����UI����ʊO��
					g_Jewelry[i].m_Size = { 0.0f, 0.0f };
					g_Jewelry[i].m_Pos = { 1500.0f, 800.0f };
					g_Jewelry[i].AnimeFlg = true;

					// �l�����̕��UI�̕\��
					g_Jewelry[i - m_UINum].GetJewelry = true;

				}
			}
		}

	}

}


//--------------------
// �`��
//--------------------
void JewelryUI::Draw()
{
	for (int i = 0; i < m_UINum * 2; i++)
	{
		// ��΂����l���̏ꍇ
		if (g_Jewelry[i].GetJewelry == false)
		{
			m_pSprite->Draw(g_Jewelry[i].m_Pos, g_Jewelry[i].m_Size, g_Jewelry[i].m_Angle,
							{ 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, 
							g_Jewelry[i].m_pJewelryNot);
		}

		// ��΂��l�����Ă���ꍇ
		if (g_Jewelry[i].GetJewelry == true)
		{
			m_pSprite->Draw(g_Jewelry[i].m_Pos, g_Jewelry[i].m_Size, g_Jewelry[i].m_Angle,
							{ 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, 
							g_Jewelry[i].m_pJewelryGet);
		}
	
	}
}


//---------------------------------------
// ��΂��l��
// �����Fint num ��΂̊l����
//---------------------------------------
int AddJewelry(int num)
{
	return 0;
}

void JewelryUI::SetPlayer(C_Player* pPlayer)
{
	m_pPlayer = pPlayer;
}

void JewelryUI::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}