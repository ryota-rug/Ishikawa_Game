#pragma once
#ifndef __KNOCK_UI_H__
#define __KNOCK_UI_H__

#include "DirectX.h"
#include "SpriteManager.h"

class KnockUI
{
public:
	KnockUI();
	~KnockUI();
	void Draw();
	void AddKnock(int num);
	void UpdateTexCoord();
	int GetKnockCnt();

public:
	typedef struct
	{
		DirectX::XMFLOAT2 m_Pos;           // �摜�̕\���ʒu
		DirectX::XMFLOAT2 m_Size;	       // �摜�̑傫��
		DirectX::XMFLOAT3 m_Angle;         // �p�x
		DirectX::XMFLOAT3 m_Scale;		   // �傫��
		DirectX::XMFLOAT2 posTexCoord;	   // �e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	   // �e�N�X�`���T�C�Y(�E��) (0.0 �` 1.0)
		bool use;				           // �g�p���t���O
		int frame;				           // �A�j���[�V�����Ǘ��p�t���[��
		int currentAnimNo;		           // �A�j���[�V�����̃R�}�ԍ�(���ォ��O�`)
		ID3D11ShaderResourceView* m_pKnockUI;
	}KNOCKUI_INFO;

private:
	SpriteManager* m_pSprite;
	KnockUI::KNOCKUI_INFO g_KnockUI[2];
	int m_KnockCnt;   // �ł��t���񐔕ۑ��p

};

#endif //__KNOCK_UI_H__