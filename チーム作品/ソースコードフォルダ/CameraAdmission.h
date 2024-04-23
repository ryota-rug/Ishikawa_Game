#ifndef __CAMERAADMISSION_H__
#define __CAMERAADMISSION_H__

#include "CameraBase.h"
#include "Camera_Manager.h"
#include "StageBase.h"
#include "Player.h"

//playerの入場カメラ
//ステージのサイズをコンストラクタで呼んでいます
class CameraAdmission : public CameraBase
{
public:
	CameraAdmission(Stage_Base* Stage );
	~CameraAdmission() {};

	void Update();

public:
	enum MIGRATE
	{
		MIGRATE_PLAYER,
		MIGRATE_END,
		MIGRATE_MAX
	};

private:
	void Player();
private:
	Stage_Base* m_pStage;
	MIGRATE m_Migrate;
	DirectX::XMFLOAT3 m_start;
	DirectX::XMFLOAT3 m_end;
	int LIMIT_RIGHT;
	int LIMIT_LEFT;
	constexpr static float m_pointZ = -200.0f;
};



#endif // !__CAMERAADMISSION_H__
