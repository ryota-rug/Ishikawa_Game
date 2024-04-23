#ifndef __ATK_GAUGE_H__
#define __ATK_GAUGE_H__

#include "DirectX.h"
#include "SpriteManager.h"

class AtkGauge
{
public:
	AtkGauge();
	~AtkGauge();
	void ChangeGauge(float Atk);
	void GaugeFix();   // �Q�[�W���Œ肷��
	void Draw();

private:

	ID3D11ShaderResourceView* m_pAtkGauge;
	SpriteManager* m_pSprite;

	DirectX::XMFLOAT2 m_Size;       // �摜�̑傫��
	DirectX::XMFLOAT2 m_DisplayPos; // �摜�̕\���ʒu
	DirectX::XMFLOAT3 m_Pos;		// �ʒu
	DirectX::XMFLOAT3 m_Scale;	    // �傫��
	DirectX::XMFLOAT3 m_Angle;	    // �p�x

	int m_Count;
	int m_NowAtk;   // ���݂̍U����
	float m_Rate;   // ����
	bool m_AtkFlg;  // �Q�[�W���Œ肷�邩�ǂ���
};

#endif // __ATK_GAUGE_H__