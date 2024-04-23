#ifndef ___LOAD_SCENE_H___
#define ___LOAD_SCENE_H___

#include "Image2D.h"


class CScene_Load
{
public:
	enum LOADSCENE_STATE
	{
		LOAD_NONE,		//画面処理してない

		LOAD_BEFORE,	//ロード前画面処理
		LOAD_LOADING,	//ロード中画面処理
		LOAD_AFTER		//ロード後画面処理
	};

public:
	CScene_Load();
	~CScene_Load();
	void Update();
	void Draw();
	void Reset();

	CScene_Load::LOADSCENE_STATE GetLoadState();	//ロード画面の状態を取得
	void LoadEnd();	//ロード終了を通知する


private:
	SpriteManager* m_pSpriteManager;	//2D描画用
	Image2D* m_pBack;				//背景画像

	LOADSCENE_STATE m_loadState;	//ロード画面の状態
	bool m_loadEnd;					//ロード処理終了フラグ
};


#endif // !___LOAD_SCENE_H___
