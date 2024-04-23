#include "Select_Block.h"
#include "Select_Data.h"
#include <mutex>

namespace
{
	static bool SEPlayFlag;
}




Select_Block::Select_Block(SpriteManager* pSM, SCENE beforeScene)
{
	Image2D* pBlock;
	int i;


	//���������u���b�N���쐬
	for (i = Stage11; i <= Stage35; i++)
	{
		//�N���A���ĂȂ��X�e�[�W
		if (GetLoadStage(static_cast<SaveElea>(i)).ClearStage == false)
		{
			// �X�e�[�W�ԍ� (0 �` 14)
			// �N���A�����ɃX�e�[�W����o�Ă�����A���ĂȂ��u���b�N���쐬���邽�� for�� �𔲂���
			// -3 ���邱�Ƃ� SCENE_STAGE1_1 ���� 0 �Ƃ��Ĉ���
			if (_GetBeforeScene() - 3 == i) { break; }

			//�󂷃u���b�N�̔ԍ�������
			m_breakBlock = static_cast<SaveElea>(i);

			//�X�e�[�W�ԍ�����u���b�N�ǂݍ���
			switch (i / 5)
			{
			case 0: { pBlock = new Image2D("Assets/2D/animation/block1.png", pSM); } break;
			case 1: { pBlock = new Image2D("Assets/2D/animation/block2.png", pSM); } break;
			case 2: { pBlock = new Image2D("Assets/2D/animation/block3.png", pSM); } break;
			}

			// �X�e�[�W�ԍ�����ʒu���w��
			// 2-1 �ł���� 0�Ԗ� (SELECT1_POS_X) �̈ʒu�ɍ��
			switch (i % 5)
			{
			case 0: { pBlock->pos.x = SELECT1_POS_X; } break;
			case 1: { pBlock->pos.x = SELECT2_POS_X; } break;
			case 2: { pBlock->pos.x = SELECT3_POS_X; } break;
			case 3: { pBlock->pos.x = SELECT4_POS_X; } break;
			case 4: { pBlock->pos.x = SELECT5_POS_X; } break;
			}

			//�u���b�N�̈ʒu��傫���Ȃ�
			pBlock->pos.y = 600.0f;
			pBlock->size = { 200.0f, 350.0f };
			pBlock->SetTexScale(14, 1);

			//�u���b�N�ꗗ�Ɋi�[
			m_mapBlocks[m_breakBlock] = pBlock;

			break; 
		}
	}


	//���ĂȂ��u���b�N���쐬
	for (i += 1; i <= Stage35; i++)
	{
		//�X�e�[�W���ƂɃu���b�N�摜�ǂݍ���
		switch (i / 5)
		{
		case 0: { pBlock = new Image2D("Assets/2D/animation/block1.png", pSM); } break;
		case 1: { pBlock = new Image2D("Assets/2D/animation/block2.png", pSM); } break;
		case 2: { pBlock = new Image2D("Assets/2D/animation/block3.png", pSM); } break;
		}

		// �X�e�[�W�ԍ�����ʒu���w��
		// 2-1 �ł���� 0�Ԗ� (SELECT1_POS_X) �̈ʒu�ɍ��
		switch (i % 5)
		{
		case 0: { pBlock->pos.x = SELECT1_POS_X; } break;
		case 1: { pBlock->pos.x = SELECT2_POS_X; } break;
		case 2: { pBlock->pos.x = SELECT3_POS_X; } break;
		case 3: { pBlock->pos.x = SELECT4_POS_X; } break;
		case 4: { pBlock->pos.x = SELECT5_POS_X; } break;
		}

		//�u���b�N�̈ʒu��傫���Ȃ�
		pBlock->pos.y = 600.0f;
		pBlock->size = { 200.0f, 350.0f };
		pBlock->SetTexScale(14, 1);

		//�u���b�N�ꗗ�Ɋi�[
		m_mapBlocks[static_cast<SaveElea>(i)] = pBlock;
	}


	//SE
	m_pSEBreak = new SE("Assets/SE/Destroy_Block.wav");
	SEPlayFlag = true;
}



Select_Block::~Select_Block()
{
	delete m_pSEBreak;

	for (auto it = m_mapBlocks.begin(); it != m_mapBlocks.end();)
	{
		delete (*it).second;
		it = m_mapBlocks.erase(it);
	}
}



void Select_Block::Draw()
{
	SelectState::STAGE nowStage = SelectState::GetStage();

	for (auto it = m_mapBlocks.begin(); it != m_mapBlocks.end(); it++)
	{
		//���݂̃X�e�[�W�łȂ���Ε\�����Ȃ�
		if (static_cast<SelectState::STAGE>( ((*it).first / 5) + 1) != nowStage) continue;

		//�u���b�N��������Ε\�����Ȃ�
		if ((*it).second == nullptr) continue;

		//�\��
		(*it).second->Draw();
	}
}


//--------------------------------------------------------
// �u���b�N�j�󉉏o
// �j�󒆂� false ���Ԃ���A�Ăяo�����œ��͂𐧌�����
//--------------------------------------------------------
bool Select_Block::BreakBlock()
{
	if ( m_mapBlocks[m_breakBlock] == nullptr ) { return true; }
	if ( (m_breakBlock / 5) + 1 != SelectState::GetStage() ) { return true; }

	if (SEPlayFlag) 
	{
		m_pSEBreak->Play();
		SEPlayFlag = false;
	}

	if (m_mapBlocks[m_breakBlock]->texNum == -1)
	{
		for (auto it = m_mapBlocks.begin(); it != m_mapBlocks.end(); it++)
		{
			if ((*it).first == m_breakBlock)
			{
				delete (*it).second;
				m_mapBlocks.erase(it);
				break;
			}
		}

		return true;
	}

	m_mapBlocks[m_breakBlock]->UpdateAnimation(3, false);
	return false;
}



bool Select_Block::IsPlayable()
{
	SaveElea nowElea = static_cast<SaveElea>(
		(SelectState::GetStage() - 1) * 5 + (SelectState::GetSelect() - 1)  );

	if (nowElea == m_breakBlock) { return true; }

	for (auto it = m_mapBlocks.begin(); it != m_mapBlocks.end(); it++)
	{
		if (it->first == nowElea)
		{
			return false;
		}
	}

	return true;
}
