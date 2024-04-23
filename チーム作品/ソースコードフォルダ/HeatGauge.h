#ifndef __HEAT_GAUGE_H__
#define __HEAT_GAUGE_H__

#include "DirectX.h"
#include "SpriteManager.h"
#include "Camera_Manager.h"

class HeatGauge
{
public:
	HeatGauge();
	~HeatGauge();
	void Update();
	void IncreaseHeat(float gauge);   // �Q�[�W����
	void DecreaseHeat(float gauge);   // �Q�[�W����
	void Draw();

	// ���`��ԗp�֐�
	void GetPlayerPos(FloatPos PlayerPos);
	void GetCameraManager(C_CameraManager* pCameraManager);

public:
	typedef struct
	{
		// ���`��ԗp
		DirectX::XMFLOAT2 m_Pos;
		DirectX::XMFLOAT2 Size;
		DirectX::XMFLOAT3 Angle;
		DirectX::XMFLOAT2 m_StartPos;    // ���`��ԗp�J�n���W
		DirectX::XMFLOAT2 m_EndPos;      // ���`��ԗp�I�����W
		bool Use;
		bool GetItem;
		bool AnimeFlg;
		int CurrentCnt;                  // ���݂̃J�E���g
		int MaxCnt;						 // �A�j���[�V�������J�E���g
		ID3D11ShaderResourceView* m_pHeatItem;
	}HEATITEM_INFO;

private:
	ID3D11ShaderResourceView* m_pHeatGauge;
	SpriteManager* m_pSprite;

	DirectX::XMFLOAT2 m_Size;       // �摜�̑傫��
	DirectX::XMFLOAT2 m_DisplayPos; // �摜�̕\���ʒu
	DirectX::XMFLOAT3 m_Scale;	    // �傫��
	DirectX::XMFLOAT3 m_Angle;	    // �p�x
	float m_Meter;   // ���[�^�[�̒l
	
	// ���`��ԗp�ϐ�
	HeatGauge::HEATITEM_INFO m_HeatItem[6];
	C_CameraManager* m_pCameraManager;
	DirectX::XMFLOAT2 m_2DItemPos;
	FloatPos m_3DItemPos;
	int m_UINum;
};

#endif   //__HEAT_GAUGE_H__