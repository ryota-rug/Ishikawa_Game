#include "fieldmanager.h"
#include "manager.h"

#include "scene.h"

void FieldManager::Init()
{
	DirectX::XMFLOAT3 pos = m_TopLeft; // 左上のポジション

	Scene* scene = Manager::GetScene();
	
	for (int y = 0; y < MAX_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_WIDTH; x++)
		{
			m_Infos[y][x].point = pos;	  // ポジション代入
			m_Infos[y][x].numX = x;
			m_Infos[y][x].numY = y;
			if (y != 0)
			{
				m_Infos[y][x].UpInfo = &m_Infos[y - 1][x];
			}

			if (y != MAX_HEIGHT - 1)
			{
				m_Infos[y][x].DownInfo = &m_Infos[y + 1][x];
			}

			if (x != MAX_WIDTH - 1)
			{
				m_Infos[y][x].RightInfo = &m_Infos[y][x + 1];
			}

			if (x != 0)
			{
				m_Infos[y][x].LeftInfo = &m_Infos[y][x - 1];
			}

			// --- ブロック配置 ---
			// 端のブロック配置
			if ( x == 0 || x == MAX_WIDTH - 1 || y == 0 || y == MAX_HEIGHT - 1)
			{
				m_Infos[y][x].block = scene->AddGameObject<BlockBase>(); // ブロック生成
				m_Infos[y][x].block->SetBlock(m_Infos[y][x].point, BlockBase::BlockType::Unbreakable);
			}
			// 一個飛ばしで壊れないブロックを置く
			else if (x % 2 == 0 && y % 2 == 0)
			{
				m_Infos[y][x].block = scene->AddGameObject<BlockBase>(); // ブロック生成
				m_Infos[y][x].block->SetBlock(m_Infos[y][x].point, BlockBase::BlockType::Unbreakable);
			}
			//// 普通のブロックを置く
			//else if (!(((y == 1 || y == MAX_HEIGHT - 2) && (x == 1 || x == 2 || x ==  MAX_WIDTH - 3 || x == MAX_WIDTH - 2)) ||
			//	((y == 2 || y == MAX_HEIGHT - 3) && ( x == 1 || x == MAX_WIDTH - 2))))
			//{
			//	m_Infos[y][x].block = scene->AddGameObject<BlockBase>(); // ブロック生成
			//	m_Infos[y][x].block->SetBlock(m_Infos[y][x].point, BlockBase::BlockType::Normal);
			//}
			else // 何もない
			{
				//pAstar->SetCost(x, y, 1);
			}
			pos.x += m_SquareSize.x;	  // 1マス分増やす
		}
		pos.x = m_TopLeft.x;
		pos.z -= m_SquareSize.z;
	}

	SetBlock(scene);
}

void FieldManager::Update()
{

}

FieldManager::Info* FieldManager::GetInfo(int x, int y)
{
	return &m_Infos[y][x];
}

void FieldManager::InitCost()
{
	for (int y = 0; y < MAX_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_WIDTH; x++)
		{
			m_Infos[y][x].cost = 0;
			m_Infos[y][x].score = 0;
			m_Infos[y][x].heuristiccost = 999;
			m_Infos[y][x].parent = nullptr;
		}
	}
}

void FieldManager::SetBlock(Scene * scene)
{
	int center_x = (MAX_WIDTH - 1) / 2;
	int center_y = (MAX_HEIGHT - 1) / 2;

	for (int y = 1; y <= MAX_HEIGHT - 1; y++)
	{
		for (int x = 1; x <= MAX_WIDTH - 1; x++)
		{
			if (m_Infos[y][x].block)
				continue;

			if (CheckBlockPlacement(x, y, center_x, center_y))
			{
				m_Infos[y][x].block = scene->AddGameObject<BlockBase>();
				m_Infos[y][x].block->SetBlock(m_Infos[y][x].point, BlockBase::BlockType::Unbreakable);
			}
		}
	}
}

bool FieldManager::CheckBlockPlacement(int x, int y , int centerX, int centerY)
{
	// 真ん中(縦)
	if (x == centerX && ((y >= 1 && y <= centerY - 2) || (y >= centerY + 2 && y <= MAX_HEIGHT - 2)))
		return true;

	// 真ん中(横)
	if (y == centerY && x >= 2 && x <= MAX_WIDTH - 3)
		return true;

	return false;
}

