#pragma once
#ifndef  __JEWELRY_UI_H__
#define  __JEWELRY_UI_H__

#include "DirectX.h"
#include "SpriteManager.h"
#include "Player.h"
#include <string>
#include <list>
#include "Camera_Manager.h"

// プロトタイプ
int AddJewelry(int num);

class JewelryUI
{
public:
	JewelryUI();
	~JewelryUI();
	void MakeJewelryUI(int Num);
	void GetJewelryUI();
	void GetMoveJewelry();
	void Draw();
	void SetPlayer(C_Player* pPlayer);
	void SetCameraManager(C_CameraManager* pCameraManager);

public:
	typedef struct
	{
		DirectX::XMFLOAT2 m_Size;                  // 画像の大きさ
		DirectX::XMFLOAT2 m_Pos;				   // 画像の表示位置
		DirectX::XMFLOAT3 m_Angle;	               // 角度
		bool GetJewelry;                           // 宝石を取得したか判定
		ID3D11ShaderResourceView* m_pJewelryNot;   // 未獲得UIの情報
		ID3D11ShaderResourceView* m_pJewelryGet;   // 獲得UIの情報

		// ベジエ曲線用
		DirectX::XMFLOAT2 m_StartPos;              // ベジエ用開始座標
		DirectX::XMFLOAT2 m_EndPos;                // ベジエ用終了座標
		DirectX::XMFLOAT2 m_ControlPos1;           // ベジエ用制御点
		DirectX::XMFLOAT2 m_ControlPos2;           // ベジエ用制御点
		int MaxCnt;								   // アニメーション総カウント
		int CurrentCnt;                            // 現在のカウント
		bool Use;                                  // アニメーションの有無
		bool AnimeFlg;
	}JEWELRYUI_INFO;

private:
	SpriteManager* m_pSprite;
	C_Player* m_pPlayer;
	JewelryUI::JEWELRYUI_INFO g_Jewelry[6];
	int m_UINum;   // 宝石を何個作るかの保存用変数
	int tmp;
	C_CameraManager* m_pCameraManager;
	DirectX::XMFLOAT2 m_2DJewelyPos;

};

#endif //  __JEWELRY_UI_H__
