//#pragma once
#ifndef STAGE_BASE_H
#define STAGE_BASE_H
#include "Position_struct.h"
#include "CameraBase.h"
#include <vector>
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "GameUI.h"
#include "jewelryUI.h"
#include "BreakNumUI.h"
#include "Sound.h"
#include "SaveLoad.h"

class Block_Base;
class PileBanker;
class C_Player;
class CItemBase;

class Stage_Base
{
public:
	enum GAMEOVER_TYPE
	{
		GAMEOVER_DFAULT = 0,
		GAMEOVER_HIT_MAGMA,			// マグマに当たった時
		GAMEOVER_HIT_SAND,			// 砂に当たった時
		GAMEOVER_CEILING_DESTROY,	//天井が壊れる
		GAMEOVER_JEWELY_DESTROY,	//宝石が壊れる
		GAMEOVER_JEWELY_MELT,		//宝石が溶ける
		GAMEOVER_JEWELY_DOROP,		//宝石を落とす
		GAMEOVER_MAX,
	};

public:
	static const FloatPos CenterPos;

	Stage_Base();
	virtual ~Stage_Base();
	virtual void Update();
	virtual void Draw();
	void UIDraw();

	//継承したブロックの中で呼びだしたい関数
	IntPos GetStageWidthNum();
	void BlockUpdate();
	void BlockDraw();
	Block_Base* GetBlockInfo(int X, int Y);				//引数に入れた数値の場所にあるブロックの情報を返す
	PileBanker* GetPileBanker();
	PileBanker* GetSideBanker();
	CItemBase* GetJewely(int X, int Y);					//ジュエリーを呼ぶ関数
	CItemBase* GetHeet(int X, int Y);					//ヒートを呼ぶ関数
	void DestroyBlock(int X, int Y);					//そこにあるブロックを消す
	void CreateBlock(int X, int Y, Block_Base* pBlock);	//ブロックを代入する
	FloatPos Get_DrawPos(int X, int Y);					//入れた配列の番号の座標(float)を返す
	IntPos Get_MapPos(float X, float Y);				//入れた座標の配列の番号(int)を返す
	void MoveBlock(int X,int Y);						//ブロックを移動させる
	void ChangeBlock(Block_Base* NewBlock);				//じぶんのポジションに新しいブロックへ置き換える
	FloatPos GetBasePos();
	void Refuge_Block();								//自分を配列の外へ避難させる
	void TakeTurn_Block(int X,int Y);					//自分とその場所にあるブロックを交換する


	//プレイヤー関係
	void PlayerUpdate();
	void PlayerDraw();
	void CreatePlayer();
	void DeletePlaer();
	C_Player* GetPlayer();

	//パイルバンカー
	void NvigateUpdate();
	void NvigateDraw();
	void CreateMainBanker(int LineNum, FloatPos InstancePos,bool Heet);		//縦杭を作る
	void CreateSideBanker();		//横杭を作る
	void DestroyMainBanker();		//縦杭を壊す
	void DestroySideBanker();		//横杭を壊す
	void SetCantTypeIn_Side();		//サイドバンカーを打ち込めないようにする
	
	//宝石関係
	void JewelyUpdate();
	void CreateJewely(int X,int Y);
	void DestroyJewely(int X, int Y);
	void MoveJewely(int X, int Y);
	void Refuge_Item();

	//ヒートアイテム関係
	void HeetUpdate();
	void CreateHeet(int X,int Y);
	void DestroyHeet(int X,int Y);
	void MoveHeet(int X,int Y);

	//アイテム共有
	void ItemDraw();

	//ゲームCPPなどで呼びだす
	void Mina_Jewely();
	void Set_GameClear();
	bool Get_GameClear();
	void Set_GameOver(GAMEOVER_TYPE Type = GAMEOVER_TYPE::GAMEOVER_DFAULT);
	bool Get_GameOver();
	GAMEOVER_TYPE Get_GameOverType();
	void CreateStage(int X_Width, int Y_Height,const char* FileName);	//ステージを作る
	void CreateStage(int X_Width, int Y_Height, const int* BlockInfo, const int* JewelyInfo, const int* HeetInfo);
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
	void StageDraw();
	FloatPos GetStageLength() { return m_StageLength; }
	CModelManager* Get_ModelManager_Address();
	

	BreakNumUI* GetBreakNum(int Num);       // ブロックを何個壊したかを取得
	BreakNumUI* GetBreakInfo();

	//セーブ関係
	SaveData* GetSaveData();
	void SetSaveData(SaveData* SaveData);

protected:
	IntPos m_Stage_Width;
	PileBanker* m_pNavigate;				//縦打ち用パイルバンカー
	PileBanker* m_pSideBanker;				//横打ち用パイルバンカー
	C_Player *m_pPlayer;					//プレイヤー
	Block_Base** m_mapInfo_Block;			//ブロックの配列用
	CItemBase** m_mapInfo_Jewely;				//アイテムの配列
	CItemBase** m_mapInfo_Heet;
	CModelManager *m_pModelManager;			//モデルマネージャー
	C_CameraManager *m_pCameraManager;		//カメラマネージャー
	FloatPos m_BasePos;						//左上のポジション
	FloatPos m_StageLength;

private:
	int m_JewelyCount;	//宝石のカウント
	bool m_GameClear;	//ゲームクリアにする
	bool m_GameOver;	//ゲームオーバーにする
	GAMEOVER_TYPE m_GameOverType;

	//ブロックの動きに関して
	Block_Base *m_VirtualBlock;				//無敵なブロック
	bool m_exeMoveBlock;					//ブロックを動かすときのトリガー
	bool m_exeChangeBlock;					//自分のブロックを変える時のトリガー
	bool m_exeRefugeBlock;					//配列上では消すがアップデートをしたい時にするトリガー
	bool m_exeTakeTurnsBlock;				//ブロックを交換するときに使う
	Block_Base* Temporary_Block;			//一時避難しておくポインター
	IntPos temporary_BlockPos;				//一時避難しておく場所ブロック
	int m_BreakNum;                         // 破壊したブロックを格納する変数
	std::vector<Block_Base*> m_RefugeBlock;	//排列から外に出たとき用の変数を置く場所

	//アイテムの動きに関して
	bool m_exeMoveItem;
	bool m_exeRefugeItem;
	IntPos m_Temporary_ItemPos;				//アイテムの一時避難しておくポジション
	std::vector<CItemBase*> m_RefugeItem;

	//パイルバンカー関係
	bool m_CanTypeIn_Side;

	// UI関係
	GameUI* m_pUI;
	JewelryUI* m_pJewelryUI;
	BreakNumUI* m_pBreakUI;

	SE* m_pClearSE;
	SE* m_pOverSE;

	SaveData *m_pNowSaveFile;
};

#endif // !STAGE_BASE_H

