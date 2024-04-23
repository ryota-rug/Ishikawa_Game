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
	void GaugeFix();   // ゲージを固定する
	void Draw();

private:

	ID3D11ShaderResourceView* m_pAtkGauge;
	SpriteManager* m_pSprite;

	DirectX::XMFLOAT2 m_Size;       // 画像の大きさ
	DirectX::XMFLOAT2 m_DisplayPos; // 画像の表示位置
	DirectX::XMFLOAT3 m_Pos;		// 位置
	DirectX::XMFLOAT3 m_Scale;	    // 大きさ
	DirectX::XMFLOAT3 m_Angle;	    // 角度

	int m_Count;
	int m_NowAtk;   // 現在の攻撃力
	float m_Rate;   // 割合
	bool m_AtkFlg;  // ゲージを固定するかどうか
};

#endif // __ATK_GAUGE_H__