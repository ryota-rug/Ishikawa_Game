#pragma once
#include "fieldmanager.h"
#include <list>

class AStarNodeManager
{
public:
	std::list<FieldManager::Info*>AStar(FieldManager::Info* start, FieldManager::Info* goal);
private:
	
	bool Less(FieldManager::Info& a, FieldManager::Info& b);
	bool AddOpenList(std::list<FieldManager::Info*>& open_list, std::list<FieldManager::Info*>& close_list, 
		FieldManager::Info* node, int cost);
	bool AddCloseList(std::list<FieldManager::Info*>& close_list, FieldManager::Info* search_node);
	bool IsSameNode(FieldManager::Info* a, FieldManager::Info* b);
	int CalculateHeuristic(FieldManager::Info* node, FieldManager::Info* goal);
	bool DeleteDdjacentList(FieldManager::Info* it);
	bool IsNodeWithinTheRange(int x, int y);
};

