#pragma once
#include "component.h"
#include "blockbase.h"

#define MAX_WIDTH 33
#define MAX_HEIGHT 25

class Bomb;

class FieldManager : public Component
{
public:
	using Component::Component;
	struct Info
	{
		BlockBase* block = nullptr; // ブロック情報
		Bomb* bomb = nullptr;		// 爆弾情報
		DirectX::XMFLOAT3 point = {}; //マスの座標
		Info* UpInfo = nullptr;
		Info* DownInfo = nullptr;
		Info* LeftInfo = nullptr;
		Info* RightInfo = nullptr;
		int numX = 0;  // 配列の何番か
		int numY = 0;  // 配列の何番か
		int cost = 0;
		int heuristiccost = 999;	//ヒューリスティックコスト
		int score = 0;
		Info* parent = nullptr;
		bool explosion = false;
	};

	void Init() override;
	void Update() override;
	DirectX::XMFLOAT3 GetTopLeft() { return m_TopLeft; }
	Info* GetInfo(int x, int y);
	DirectX::XMFLOAT3 GetSquareSize() { return m_SquareSize; }
	void InitCost();

private:
	void SetBlock(class Scene* scene);
	const int m_MaxNam = MAX_WIDTH * MAX_HEIGHT;
	DirectX::XMFLOAT3 m_TopLeft = { -MAX_WIDTH + 1.0f,0.0f,MAX_HEIGHT + 1.0f };
	Info m_Infos[MAX_HEIGHT][MAX_WIDTH];
	DirectX::XMFLOAT3 m_SquareSize = DirectX::XMFLOAT3(2.0f,0.0f,2.0f); // 1マスのサイズ縦2、横2
	bool CheckBlockPlacement(int x, int y,int centerX, int centerY); // ブロックを置く場所か
};

