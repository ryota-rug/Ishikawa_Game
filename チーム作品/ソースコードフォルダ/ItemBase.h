#ifndef __ITEM_BASE__
#define __ITEM_BASE__
#include "StageBase.h"
#include "Position_struct.h"
#include "CameraBase.h"
#include "BlockBase.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"

class Stage_Base;

class CItemBase
{
public :
	// アイテムの種類
	enum ITEM_TYPE
	{
		NONE,
		JEWELY,
		HEAT
	};
	// ステージ配列の中か外か
	enum ITEMSTATE
	{
		ITEM_IN,
		ITEM_OUT
	};
	// アイテムの傾き
	enum ITEM_ANGLE
	{
		RIGHT,
		LEFT
	};
	// 同じ場所にあるアイテムの数
	enum ITEM_COINCIDE
	{
		ONE,
		DOUBLE,
		TRIPLE
	};

public:
	static const float ItemSize;	//一つ当たりのアイテムのサイズ
	CItemBase(Stage_Base* MyStage, int PosX, int PosY);
	virtual ~CItemBase();
	virtual void Update() {}
	virtual void Draw() {}
	virtual void RefugeUpdate() {}
	IntPos GetMap();			// マップ上(StageBaseのマップ配列)でのポジション取得関数
	FloatPos GetPos();			// 描画上でのポジション取得関数
	void SetMap(int X, int Y);
	void SetPos(float X, float Y, float Z);
	void Destroy();
	bool Get_Destroy();			// 破壊フラグ取得関数
	ITEM_TYPE GetType();		// アイテムの種類取得関数
	ITEM_ANGLE GetAngle();		// アイテムの傾き取得関数
	void SetAngle(ITEM_ANGLE num);		// セット関数
	void CheckCollisionMagma();	// マグマとの当たり判定
	void Set_DidUpdate(bool Set);				//アップデートするか
	bool Get_DidUpdate();			//今のフレームでアップデートしたか
	void Set_ModelManager(CModelManager* pModelManager);
	void Set_CameraManager(C_CameraManager* pCameraManager);
	void AddCoinCide(int num) { m_CoinCide += num; }
	int GetCoinCide() { return m_CoinCide; }

private:
	bool m_DidUpdate;

protected:
	ITEM_TYPE m_Type;		//アイテムの種類
	ITEM_ANGLE m_Angle;		// アイテムの傾き
	Stage_Base* m_pMyStage;
	IntPos m_MapPos;		//マップ情報
	FloatPos m_DrawPos;		//描画するポジション
	bool m_IsDestroy;
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
	static int m_AngleNum; // 0は右に1は左に傾かせる
	int m_CoinCide = 1; // 同じ場所にあるアイテム数
};

#endif //__ITEM_BASE__