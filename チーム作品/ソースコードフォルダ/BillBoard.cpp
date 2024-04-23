#include "BillBoard.h"

using namespace DirectX;

CameraBase** BillBoard::m_ppCamera;



BillBoard::BillBoard(LPCSTR filePath, SpriteManager* pSM) :
	pos(0.0f, 0.0f, 0.0f),
	size(100.0f, 100.0f),
	color(1.0f, 1.0f, 1.0f, 1.0f),
	texNum(0)
{
	m_pSpriteManager = pSM;
	LoadTextureFromFile(filePath, &m_pImage);	//�e�N�X�`���ǂݍ���

	m_reverseU = false;
	m_reverseV = false;

	m_texPos[0] = { 0.0f, 0.0f };
	m_texScale = { 1.0f, 1.0f };

	m_frame = 0;
}

BillBoard::~BillBoard()
{
	for (auto it = m_texPos.begin(); it != m_texPos.end();)
	{
		it = m_texPos.erase(it);
	}

	m_pSpriteManager->TextureRelease(m_pImage);
}

void BillBoard::Draw()
{
	//�e�N�X�`���ԍ���-1�Ȃ�`�悵�Ȃ�
	if (texNum == -1) { return; }


	//UV���W�𔽓]������
	XMFLOAT2 texPos = m_texPos[texNum];
	if (m_reverseU) { texPos.x -= m_texScale.x; }
	if (m_reverseV) { texPos.y -= m_texScale.y; }


	//�`��
	m_pSpriteManager->DrawBillBoard
	(
		pos, size,			// ���W�E�傫��
		texPos, m_texScale,	// UV���W�EUV�̑傫��
		color,				// �F
		m_pImage,			// �摜�f�[�^
		*m_ppCamera			// �J�������
	);
}



void BillBoard::Reverse(bool reverseU, bool reverseV)
{
	m_reverseU = reverseU;
	m_reverseV = reverseV;


	//---X�����̔��]
	if (reverseU)
	{
		//�uUV�̑傫���v�����̒l�ł���Ε��̒l�ɂ���
		if (m_texScale.x > 0.0f) { m_texScale.x = -m_texScale.x; }
	}
	else
	{
		//�uUV�̑傫���v�����̒l�ł���ΐ��̒l�ɂ���
		if (m_texScale.x < 0.0f) { m_texScale.x = -m_texScale.x; }
	}


	//---Y�����̔��]
	if (reverseV)
	{
		//�uUV�̑傫���v�����̒l�ł���Ε��̒l�ɂ���
		if (m_texScale.y > 0.0f) { m_texScale.y = -m_texScale.y; }
	}
	else
	{
		//�uUV�̑傫���v�����̒l�ł���ΐ��̒l�ɂ���
		if (m_texScale.y < 0.0f) { m_texScale.y = -m_texScale.y; }
	}
}

void BillBoard::SetTexScale(float divisionU, float divisionV)
{
	//�傫���̐ݒ�
	m_texScale = { 1.0f / divisionU, 1.0f / divisionV };


	//���W�̐ݒ�
	for (int i = 0; i < divisionV; i++)
	{
		for (int j = 0; j < divisionU; j++)
		{
			float scaleU = m_texScale.x * j;
			float scaleV = m_texScale.y * i;
			m_texPos[i*divisionU + j] = { scaleU, scaleV };
		}
	}

	//�e�N�X�`��������
	m_divisionTexNum = divisionU * divisionV;
}

void BillBoard::UpdateAnimation(UINT frame, bool loop)
{
	m_frame++;

	if (m_frame >= frame)
	{
		m_frame = 0;
		texNum++;

		if (loop)
		{
			texNum %= m_divisionTexNum;
		}
		else
		{
			if (texNum >= m_divisionTexNum) { texNum = -1; }
		}
	}
}



void BillBoard::_SetCamera(CameraBase** ppCamera)
{
	m_ppCamera = ppCamera;
}
