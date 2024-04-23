#include "astarnodemanager.h"
#include "manager.h"
#include "game.h"

// ===============
// 昇順ソート用関数
// ===============
bool AStarNodeManager::Less(FieldManager::Info& a, FieldManager::Info& b)
{
	return a.score < b.score;
}

// ===============
// ルート検索関数
// ===============
std::list<FieldManager::Info*> AStarNodeManager::AStar(FieldManager::Info * start, FieldManager::Info * goal)
{
	std::list<FieldManager::Info*> open_list;
	std::list<FieldManager::Info*> close_list;

	// コスト初期化
	static_cast<Game*>(Manager::GetScene())->GetFieldMan()->InitCost();

	// オープンリストに開始点追加
	open_list.push_back(start);

	// オープンリストの中身がなくなるまで繰り返す
	while (!open_list.empty())
	{
		// 一番スコアの高いノードを取り出す
		FieldManager::Info* search_node = *open_list.begin();
		open_list.erase(open_list.begin());

		// ゴールに到達しているなら
		if (IsSameNode(search_node, goal))
		{
			// クローズリストに最後のノードを追加して終了
			close_list.push_back(search_node);
			break;
		}

		// 隣接しているノードを入れる
		std::vector<FieldManager::Info*> adjacent_list;

		adjacent_list.push_back(search_node->UpInfo);
		adjacent_list.push_back(search_node->LeftInfo);
		adjacent_list.push_back(search_node->DownInfo);
		adjacent_list.push_back(search_node->RightInfo);

		// 壊せないブロックもしくは爆弾だったらリストから消す
		for (auto it = adjacent_list.begin(); it < adjacent_list.end(); ++it)
		{
			if (((*it)->block != nullptr && 
				(*it)->block->GetType() == BlockBase::BlockType::Unbreakable))
			{
				adjacent_list.erase(it);
				it--;
			}
			
		}


		for (FieldManager::Info* adjacent_node : adjacent_list)
		{
			// 計算を行っていなかった場合だけ計算
			if (adjacent_node->heuristiccost == 999)
			{
				// ヒューリスティクスコスト計算
				adjacent_node->heuristiccost = CalculateHeuristic(adjacent_node, goal);
			}

			// スコアリング
			int total_score = adjacent_node->heuristiccost + adjacent_node->cost + 1;

			// ノード追加
			if (AddOpenList(open_list, close_list, adjacent_node, total_score) == true)
			{
				// スコアを更新
				adjacent_node->cost = total_score;
				// 親更新
				adjacent_node->parent = search_node;
			}
		}

		AddCloseList(close_list, search_node);

		// 昇順ソート
		open_list.sort([](const FieldManager::Info * a, const FieldManager::Info * b) { return a->score < b->score; });


	}

	std::list<FieldManager::Info*> route_list;
	// ゴールセルから復元する
	route_list.push_back(goal);
	while (route_list.empty() == false)
	{
		FieldManager::Info* route = route_list.front();

		if (route == nullptr)
			break;

		// スタートセルなら終了
		if (IsSameNode(route, start) == true)
		{
			break;
		}
		else
		{
			if (IsNodeWithinTheRange(route->numX, route->numY) == true)
			{
				// 追加
				route_list.push_front(route->parent);
			}
		}
	}
	return route_list;
}


// =====================
// オープンリストに追加関数
// =====================
bool AStarNodeManager::AddOpenList(std::list<FieldManager::Info*>& open_list, std::list<FieldManager::Info*>& close_list, FieldManager::Info * node, int cost)
{

	std::list<FieldManager::Info*> node_list[] =
	{
		close_list,
		open_list
	};

	// 同じノードがオープンとクローズに存在しないか確認
	for (std::list<FieldManager::Info*>& list : node_list)
	{
		// リストに同じノードがあってリストの方のコストが高いなら削除
		for (auto it = list.begin(); it != list.end();)
		{
			// ノードと同じセルがあるか調べる
			if (IsSameNode(node, (*it)) == true)
			{
				// コストの比較
				if (cost < (*it)->cost)
				{
					list.erase(it);
				}
				else
				{
					return false;
				}
			}
			it++;
		}
	}

	open_list.push_back(node);
	return true;
}

// ======================
// クローズリストに追加関数
// ======================
bool AStarNodeManager::AddCloseList(std::list<FieldManager::Info*>& close_list , FieldManager::Info* search_node)
{
	// クローズリストチェック
	for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
	{
		// ノードと同じセルがあるか調べる
		if (IsSameNode(search_node, (*itr)) == true)
		{
			return false;
		}
	}

	// 同じノードが無かったらこのノードの探索終了
	close_list.push_back(search_node);
	return true;
}

// =====================
// 同じかどうか調べる関数
// =====================
bool AStarNodeManager::IsSameNode(FieldManager::Info * a, FieldManager::Info * b)
{

	if (a->point.x == b->point.x &&
		a->point.z == b->point.z)
	{
		return true;
	}

	return false;
}

// =============================================================
// ヒューリスティックコスト計算(ノードとゴールまでの距離を返す)関数
// =============================================================
int AStarNodeManager::CalculateHeuristic(FieldManager::Info* node, FieldManager::Info* goal)
{
	int x = abs(goal->numX - node->numX);
	int y = abs(goal->numY - node->numY);

	return x + y;
}

// =====================
// 壊れない隣接ノード削除
// =====================
bool AStarNodeManager::DeleteDdjacentList(FieldManager::Info * it)
{
	if (it->block) 
	{
		return true;
	}
	return false;
}

// ==================
// セル範囲チェック関数
// ==================
bool AStarNodeManager::IsNodeWithinTheRange(int x, int y)
{
	if (x >= 0 &&
		x < MAX_WIDTH &&
		y >= 0 &&
		y < MAX_HEIGHT)
	{
		return true;
	}

	return false;
}

