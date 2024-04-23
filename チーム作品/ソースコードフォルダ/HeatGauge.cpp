#include "HeatGauge.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

using namespace DirectX;

const float MinAngle = 0.0f;    // �j�̍Œ�p�x
const float MaxAngle = 90.0f;   // �j�̍ő�p�x
const int MaxHeatItem = 6;      // �q�[�g�A�C�e���̍ő吔

//--------------------
// �R���X�g���N�^
//--------------------
HeatGauge::HeatGauge()
	:m_Size(330.0f, -330.0f), m_DisplayPos(1260.0f, 705.0f),
	 m_Scale(1.0f, 1.0f, 1.0f), m_Angle(0.0f, 0.0f, 0.0f),
	m_Meter(0.0f),  m_UINum(0)
{
	m_pSprite = new SpriteManager;
	
	// �e�N�X�`���ǂݍ���
	LoadTextureFromFile("Assets/2D/�j.png", &m_pHeatGauge);

	for (int i = 0; i < MaxHeatItem; i++)
	{
		m_HeatItem[i].m_Pos = { -500.0f, 800.0f };
		m_HeatItem[i].Size = { 100.0f, -100.0f };
		m_HeatItem[i].Angle = { 0.0f, 0.0f, 0.0f };
		m_HeatItem[i].m_StartPos = { 0.0f, 0.0f };
		m_HeatItem[i].m_EndPos = { 980.0f, 660.0f };
		m_HeatItem[i].CurrentCnt = 0;
		m_HeatItem[i].MaxCnt = 30;
		m_HeatItem[i].GetItem = false;
		m_HeatItem[i].Use = false;
		m_HeatItem[i].AnimeFlg = false;
		LoadTextureFromFile("Assets/2D/�q�[�g�A�C�e��.png", &m_HeatItem[i].m_pHeatItem);
	}

}


//--------------------
// �f�X�g���N�^
//--------------------
HeatGauge::~HeatGauge()
{
	for (int i = 0; i < MaxHeatItem; i++)
	{
		m_HeatItem[i].m_pHeatItem->Release();
	}

	m_pHeatGauge->Release();
	delete m_pSprite;
}


//--------------------
// �X�V
//--------------------
void HeatGauge::Update()
{	
	for (int i = 0; i < MaxHeatItem; i++)
	{
		// �q�[�g�A�C�e�����擾���Ă����ꍇ
		if (m_HeatItem[i].GetItem && !m_HeatItem[i].AnimeFlg)
		{
			// ��x������鏈��
			if (!m_HeatItem[i].Use)
			{
				// �v���C���[�̌��ݍ��W���擾
				m_2DItemPos = m_pCameraManager->ChangeScreenPos(m_3DItemPos);
				m_HeatItem[i].m_Pos = m_2DItemPos;

				// �J�n���W�Z�b�g
				m_HeatItem[i].m_StartPos = m_2DItemPos;

				// �t���O�؂�ւ�
				m_HeatItem[i].Use = true;
			}

			// �A�j���[�V�����J�E���^�̍X�V
			m_HeatItem[i].CurrentCnt++;

			// ���W�̍X�V
			m_HeatItem[i].m_Pos.x = m_HeatItem[i].m_StartPos.x +
				(m_HeatItem[i].m_EndPos.x - m_HeatItem[i].m_StartPos.x) *
				((float)m_HeatItem[i].CurrentCnt / m_HeatItem[i].MaxCnt);

			m_HeatItem[i].m_Pos.y = m_HeatItem[i].m_StartPos.y +
				(m_HeatItem[i].m_EndPos.y - m_HeatItem[i].m_StartPos.y) *
				((float)m_HeatItem[i].CurrentCnt / m_HeatItem[i].MaxCnt);

			// �ړ����̕�΂���]������
			m_HeatItem[i].Angle.z += 1.5f;

			// �I������
			if (m_HeatItem[i].m_EndPos.x - 10.0f <= m_HeatItem[i].m_Pos.x &&
				m_HeatItem[i].m_EndPos.x + 10.0f >= m_HeatItem[i].m_Pos.x)
			{
				if (m_HeatItem[i].m_EndPos.y - 10.0f <= m_HeatItem[i].m_Pos.y &&
					m_HeatItem[i].m_EndPos.y + 10.0f >= m_HeatItem[i].m_Pos.y)
				{
					// UI����ʊO�ֈړ�
					m_HeatItem[i].m_Pos = { -500.0f, 800.0f };

					// �g��Ȃ�UI�̃t���O�؂�ւ�
					m_HeatItem[i].GetItem = false;
					m_HeatItem[i].AnimeFlg = true;
				}
			}
		}

		
		// �Q�[�W����
		if (m_Angle.z < m_Meter * 30.0f)
		{
			if (m_Meter <= 3)
			{
				m_Angle.z += 0.3f;
			}
		}
		// �Q�[�W����
		else
		{
			m_Angle.z -= 0.5f;
		}
		
	}

}


//--------------------
// �Q�[�W����
//--------------------
void HeatGauge::IncreaseHeat(float gauge)
{
	// �q�[�g�A�C�e���擾
	m_HeatItem[m_UINum].GetItem = true;
	m_UINum++;

	m_Meter++;

}


//--------------------
// �Q�[�W����
//--------------------
void HeatGauge::DecreaseHeat(float gauge)
{
	m_Meter = gauge;

	for (int i = 0; i < MaxHeatItem; i++)
	{
		m_HeatItem[i].m_Pos = { -500.0f, 800.0f };
		m_HeatItem[i].m_StartPos = { 0.0f, 0.0f };
		m_HeatItem[i].CurrentCnt = 0;
		m_HeatItem[i].GetItem = false;
		m_HeatItem[i].Use = false;
		m_HeatItem[i].AnimeFlg = false;
	}

	m_UINum = 0;
}


//--------------------
// �`��
//--------------------
void HeatGauge::Draw()
{
	m_pSprite->Draw(m_DisplayPos, m_Size, m_Angle, { 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, m_pHeatGauge);

	// �A�j���[�V�����pUI
	for (int i = 0; i < MaxHeatItem; i++)
	{
		if (!m_HeatItem[i].GetItem)
		{
			continue;
		}

		m_pSprite->Draw(m_HeatItem[i].m_Pos, m_HeatItem[i].Size, m_HeatItem[i].Angle,
			{ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f,1.0f,1.0f,1.0f },
			m_HeatItem[i].m_pHeatItem);
	}

}


//----------------------------
// �v���C���[�̍��W���Z�b�g
//----------------------------
void HeatGauge::GetPlayerPos(FloatPos PlayerPos)
{
	m_3DItemPos = { PlayerPos.X, PlayerPos.Y, PlayerPos.Z };
}


//----------------------------
// �J�����̏����Z�b�g
//----------------------------
void HeatGauge::GetCameraManager(C_CameraManager * pCameraManager)
{
	m_pCameraManager = pCameraManager;
}
