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
	void IncreaseHeat(float gauge);   // ゲージ増加
	void DecreaseHeat(float gauge);   // ゲージ減少
	void Draw();

	// 線形補間用関数
	void GetPlayerPos(FloatPos PlayerPos);
	void GetCameraManager(C_CameraManager* pCameraManager);

public:
	typedef struct
	{
		// 線形補間用
		DirectX::XMFLOAT2 m_Pos;
		DirectX::XMFLOAT2 Size;
		DirectX::XMFLOAT3 Angle;
		DirectX::XMFLOAT2 m_StartPos;    // 線形補間用開始座標
		DirectX::XMFLOAT2 m_EndPos;      // 線形補間用終了座標
		bool Use;
		bool GetItem;
		bool AnimeFlg;
		int CurrentCnt;                  // 現在のカウント
		int MaxCnt;						 // アニメーション総カウント
		ID3D11ShaderResourceView* m_pHeatItem;
	}HEATITEM_INFO;

private:
	ID3D11ShaderResourceView* m_pHeatGauge;
	SpriteManager* m_pSprite;

	DirectX::XMFLOAT2 m_Size;       // 画像の大きさ
	DirectX::XMFLOAT2 m_DisplayPos; // 画像の表示位置
	DirectX::XMFLOAT3 m_Scale;	    // 大きさ
	DirectX::XMFLOAT3 m_Angle;	    // 角度
	float m_Meter;   // メーターの値
	
	// 線形補間用変数
	HeatGauge::HEATITEM_INFO m_HeatItem[6];
	C_CameraManager* m_pCameraManager;
	DirectX::XMFLOAT2 m_2DItemPos;
	FloatPos m_3DItemPos;
	int m_UINum;
};

#endif   //__HEAT_GAUGE_H__