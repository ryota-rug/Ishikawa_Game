#pragma once
#ifndef  __JEWELRY_UI_H__
#define  __JEWELRY_UI_H__

#include "DirectX.h"
#include "SpriteManager.h"
#include "Player.h"
#include <string>
#include <list>
#include "Camera_Manager.h"

// �v���g�^�C�v
int AddJewelry(int num);

class JewelryUI
{
public:
	JewelryUI();
	~JewelryUI();
	void MakeJewelryUI(int Num);
	void GetJewelryUI();
	void GetMoveJewelry();
	void Draw();
	void SetPlayer(C_Player* pPlayer);
	void SetCameraManager(C_CameraManager* pCameraManager);

public:
	typedef struct
	{
		DirectX::XMFLOAT2 m_Size;                  // �摜�̑傫��
		DirectX::XMFLOAT2 m_Pos;				   // �摜�̕\���ʒu
		DirectX::XMFLOAT3 m_Angle;	               // �p�x
		bool GetJewelry;                           // ��΂��擾����������
		ID3D11ShaderResourceView* m_pJewelryNot;   // ���l��UI�̏��
		ID3D11ShaderResourceView* m_pJewelryGet;   // �l��UI�̏��

		// �x�W�G�Ȑ��p
		DirectX::XMFLOAT2 m_StartPos;              // �x�W�G�p�J�n���W
		DirectX::XMFLOAT2 m_EndPos;                // �x�W�G�p�I�����W
		DirectX::XMFLOAT2 m_ControlPos1;           // �x�W�G�p����_
		DirectX::XMFLOAT2 m_ControlPos2;           // �x�W�G�p����_
		int MaxCnt;								   // �A�j���[�V�������J�E���g
		int CurrentCnt;                            // ���݂̃J�E���g
		bool Use;                                  // �A�j���[�V�����̗L��
		bool AnimeFlg;
	}JEWELRYUI_INFO;

private:
	SpriteManager* m_pSprite;
	C_Player* m_pPlayer;
	JewelryUI::JEWELRYUI_INFO g_Jewelry[6];
	int m_UINum;   // ��΂�����邩�̕ۑ��p�ϐ�
	int tmp;
	C_CameraManager* m_pCameraManager;
	DirectX::XMFLOAT2 m_2DJewelyPos;

};

#endif //  __JEWELRY_UI_H__
