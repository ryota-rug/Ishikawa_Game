#include "astarnodemanager.h"
#include "manager.h"
#include "game.h"

// ===============
// �����\�[�g�p�֐�
// ===============
bool AStarNodeManager::Less(FieldManager::Info& a, FieldManager::Info& b)
{
	return a.score < b.score;
}

// ===============
// ���[�g�����֐�
// ===============
std::list<FieldManager::Info*> AStarNodeManager::AStar(FieldManager::Info * start, FieldManager::Info * goal)
{
	std::list<FieldManager::Info*> open_list;
	std::list<FieldManager::Info*> close_list;

	// �R�X�g������
	static_cast<Game*>(Manager::GetScene())->GetFieldMan()->InitCost();

	// �I�[�v�����X�g�ɊJ�n�_�ǉ�
	open_list.push_back(start);

	// �I�[�v�����X�g�̒��g���Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (!open_list.empty())
	{
		// ��ԃX�R�A�̍����m�[�h�����o��
		FieldManager::Info* search_node = *open_list.begin();
		open_list.erase(open_list.begin());

		// �S�[���ɓ��B���Ă���Ȃ�
		if (IsSameNode(search_node, goal))
		{
			// �N���[�Y���X�g�ɍŌ�̃m�[�h��ǉ����ďI��
			close_list.push_back(search_node);
			break;
		}

		// �אڂ��Ă���m�[�h������
		std::vector<FieldManager::Info*> adjacent_list;

		adjacent_list.push_back(search_node->UpInfo);
		adjacent_list.push_back(search_node->LeftInfo);
		adjacent_list.push_back(search_node->DownInfo);
		adjacent_list.push_back(search_node->RightInfo);

		// �󂹂Ȃ��u���b�N�������͔��e�������烊�X�g�������
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
			// �v�Z���s���Ă��Ȃ������ꍇ�����v�Z
			if (adjacent_node->heuristiccost == 999)
			{
				// �q���[���X�e�B�N�X�R�X�g�v�Z
				adjacent_node->heuristiccost = CalculateHeuristic(adjacent_node, goal);
			}

			// �X�R�A�����O
			int total_score = adjacent_node->heuristiccost + adjacent_node->cost + 1;

			// �m�[�h�ǉ�
			if (AddOpenList(open_list, close_list, adjacent_node, total_score) == true)
			{
				// �X�R�A���X�V
				adjacent_node->cost = total_score;
				// �e�X�V
				adjacent_node->parent = search_node;
			}
		}

		AddCloseList(close_list, search_node);

		// �����\�[�g
		open_list.sort([](const FieldManager::Info * a, const FieldManager::Info * b) { return a->score < b->score; });


	}

	std::list<FieldManager::Info*> route_list;
	// �S�[���Z�����畜������
	route_list.push_back(goal);
	while (route_list.empty() == false)
	{
		FieldManager::Info* route = route_list.front();

		if (route == nullptr)
			break;

		// �X�^�[�g�Z���Ȃ�I��
		if (IsSameNode(route, start) == true)
		{
			break;
		}
		else
		{
			if (IsNodeWithinTheRange(route->numX, route->numY) == true)
			{
				// �ǉ�
				route_list.push_front(route->parent);
			}
		}
	}
	return route_list;
}


// =====================
// �I�[�v�����X�g�ɒǉ��֐�
// =====================
bool AStarNodeManager::AddOpenList(std::list<FieldManager::Info*>& open_list, std::list<FieldManager::Info*>& close_list, FieldManager::Info * node, int cost)
{

	std::list<FieldManager::Info*> node_list[] =
	{
		close_list,
		open_list
	};

	// �����m�[�h���I�[�v���ƃN���[�Y�ɑ��݂��Ȃ����m�F
	for (std::list<FieldManager::Info*>& list : node_list)
	{
		// ���X�g�ɓ����m�[�h�������ă��X�g�̕��̃R�X�g�������Ȃ�폜
		for (auto it = list.begin(); it != list.end();)
		{
			// �m�[�h�Ɠ����Z�������邩���ׂ�
			if (IsSameNode(node, (*it)) == true)
			{
				// �R�X�g�̔�r
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
// �N���[�Y���X�g�ɒǉ��֐�
// ======================
bool AStarNodeManager::AddCloseList(std::list<FieldManager::Info*>& close_list , FieldManager::Info* search_node)
{
	// �N���[�Y���X�g�`�F�b�N
	for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
	{
		// �m�[�h�Ɠ����Z�������邩���ׂ�
		if (IsSameNode(search_node, (*itr)) == true)
		{
			return false;
		}
	}

	// �����m�[�h�����������炱�̃m�[�h�̒T���I��
	close_list.push_back(search_node);
	return true;
}

// =====================
// �������ǂ������ׂ�֐�
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
// �q���[���X�e�B�b�N�R�X�g�v�Z(�m�[�h�ƃS�[���܂ł̋�����Ԃ�)�֐�
// =============================================================
int AStarNodeManager::CalculateHeuristic(FieldManager::Info* node, FieldManager::Info* goal)
{
	int x = abs(goal->numX - node->numX);
	int y = abs(goal->numY - node->numY);

	return x + y;
}

// =====================
// ���Ȃ��אڃm�[�h�폜
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
// �Z���͈̓`�F�b�N�֐�
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

