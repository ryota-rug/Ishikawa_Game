#include "AtkGauge.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

const float MaxAtk = 99.0f;
const float MinAtk = 0.0f;
const float MaxSizeY = -398.0f;   // �摜�̍ő�T�C�Y

//--------------------
// �R���X�g���N�^
//--------------------
AtkGauge::AtkGauge()
	:m_Size(45.0f, 0.0f), m_DisplayPos(1207.0f, 493.0f),
	 m_Scale(1.0f, 1.0f, 1.0f), m_Angle(0.0f, 0.0f, 0.0f),
	 m_Count(0.0f), m_NowAtk(0.0f), m_Rate(0.0f), m_AtkFlg(false)
{
	m_pSprite = new SpriteManager;

	// �e�N�X�`���ǂݍ���
	LoadTextureFromFile("Assets/2D/�p���[�Q�[�W�o�[.png", &m_pAtkGauge);
}


//--------------------
// �f�X�g���N�^
//--------------------
AtkGauge::~AtkGauge()
{
	m_pAtkGauge->Release();
	delete m_pSprite;
}


//--------------------
// �A�^�b�N�Q�[�W�ω�
//--------------------
void AtkGauge::ChangeGauge(float Atk)
{
	// �U���͂�99�����̎�
	if (Atk < MaxAtk)
	{
		// �����v�Z
		m_Rate = Atk / MaxAtk;
		m_Size.y = m_Rate * MaxSizeY;
	}
	else
	{
		Atk = MaxAtk;

		// �����v�Z
		m_Rate = Atk / MaxAtk;
		m_Size.y = m_Rate * MaxSizeY;
	}
}


//--------------------
// �Q�[�W���Œ肷��
//--------------------
void AtkGauge::GaugeFix()
{
	m_AtkFlg = true;
}

//--------------------
// �`��
//--------------------
void AtkGauge::Draw()
{
	DirectX::XMFLOAT2 temp = m_DisplayPos;
	temp.y += (m_Size.y * 0.5f);// +2.0f;

	// �Q�[�W�̕`����@
	if (!m_AtkFlg)
	{
		// �Q�[�W���Œ肳��Ă��Ȃ��ꍇ
		m_pSprite->Draw(temp, m_Size, m_Angle, { 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,1.0f,1.0f,1.0f }, m_pAtkGauge);
	}
	else
	{
		// �Q�[�W���Œ肳��Ă���ꍇ
		m_pSprite->Draw(temp, m_Size, m_Angle, { 0.0f,0.0f }, { 1.0f,1.0f }, { 1.0f,0.0f,0.0f,1.0f }, m_pAtkGauge);
	}
	
}
