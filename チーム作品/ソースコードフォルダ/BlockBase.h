//#pragma once
#ifndef BLOCK_BASE_H
#define BLOCK_BASE_H
#include "StageBase.h"
#include "Position_struct.h"
#include "CameraBase.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"

#define ADDMODEL_SENDDATA(name, path) { m_pModelManager->c_AddModel(name, path); }
#define MODELDRAW_SENDDATA(name, pos, size, angle) { m_pModelManager->c_ModelDraw(name, pos.X, pos.Y, pos.Z, size.X, size.Y, size.Z, angle[0], angle[1], angle[2]); }

class Stage_Base;

class Block_Base
{
public:
	enum BLOCK_TYPE
	{
		BLOCK_NONE = 0,	 //ブロック無し

		BLOCK_CLAY,		 // 粘土
		BLOCK_SOIL,		 // 土
		BLOCK_STONE,	 // 石
		BLOCK_CONCRETE,	 // コンクリート
		BLOCK_BEDROCK,	 // 岩盤
		BLOCK_SAND,		 // 砂
		BLOCK_ICE,		 // 氷
		BLOCK_WATER,	 // 水
		BLOCK_MAGMA,	 // マグマ
		BLOCK_GAS,		 // ガス
		BLOCK_INVINCIBLE,// 無敵
		BLOCK_JEWELY,	 // 宝石
		BLOCK_MAX
	};

public:
	static const float BlockSize;	//一つ当たりのブロックのサイズ
	Block_Base(Stage_Base* MyStage,int PosX,int PosY);
	virtual ~Block_Base();
	virtual void Update();
	virtual void Draw();
	virtual void Update_Refuge();

	BLOCK_TYPE GetType();
	int GetHP();
	int GetDEF();
	int Damage(int Num);
	IntPos GetMap();
	FloatPos GetPos();
	void SetMap(int X,int Y);
	void SetPos(float X, float Y,float Z);
	void Destroy();
	bool Get_Invincibility();		//無敵判定
	bool Get_Slipped();				//すり抜け判定
	virtual void CollisionNavigate();	//杭がこのブロックに当たったときに呼ばれる
	void CollisionBrock();
	void Set_DidUpdate(bool Set);				//アップデートするか
	bool Get_DidUpdate();			//今のフレームでアップデートしたか
	bool Get_Destroy();
	void Set_ModelManager(CModelManager* pModelManager);
	void Set_CameraManager(C_CameraManager* pCameraManager);

private:
	bool m_DidUpdate;

protected:
	BLOCK_TYPE m_Type;		//ブロックの種類
	Stage_Base* m_pMyStage;
	int m_HP;				//耐久値
	int m_DEF;				//力減少値
	IntPos m_MapPos;		//マップ情報
	FloatPos m_DrawPos;		//描画するポジション
	bool m_IsDestroy;
	CameraBase* m_pCamera;
	bool m_Invincibility;	//無敵
	bool m_Slipped;			//すり抜け
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
};


#endif // !BLOCK_BASE_H
