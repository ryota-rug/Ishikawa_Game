#ifndef __CAMERAPILE_H__
#define __CAMERAPILE_H__

#include "CameraBase.h"
#include "StageBase.h"
#include "PileBankerBase.h"

 void BiblationCameraPile();

class CameraPile :public CameraBase
{
public:
	CameraPile(Stage_Base* Stage);
	~CameraPile() {};
	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos , DirectX::XMFLOAT3 yetLook) override;
	bool GetPile();
public:
	enum MIGRATE
	{
		CameraInterpolation,
		MIGRATE_SHOT,
		MIGRATE_SIDE,
		MIGRATE_MAX
	};
private:
	void Side();
	void Shot();
	void Shake();
	
	void Interpolation();
private:
	DirectX::XMFLOAT3 m_EndPos;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_EndLook;	//ワールドカメラの最終地点（一番遠ざかった場所）
	DirectX::XMFLOAT3 m_StartPos;	//ワールドカメラの開始地点
	DirectX::XMFLOAT3 m_StartLook;	//ワールドカメラの開始地点
	float m_time;
	float m_totalTime;
	DirectX::XMFLOAT3 m_OldPilePos;	//パイルの前フレーム座標
	DirectX::XMFLOAT3 m_PileMove;	//パイルの移動量
	
	Stage_Base* m_pStage;
	MIGRATE m_Migrate;
	constexpr static float m_pointZ = -230.0f;
	int m_PileAtk;
	constexpr static int m_ShakeFrame = 10;	//揺れるフレーム数
	constexpr static int m_ShakeWidth = 10;	//揺れる幅の抽選（１０なら-５～５）
};


#endif // !__CAMERAPILE_H__
