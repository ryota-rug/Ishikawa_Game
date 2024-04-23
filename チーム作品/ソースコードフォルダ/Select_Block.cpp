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


	//今から壊れるブロックを作成
	for (i = Stage11; i <= Stage35; i++)
	{
		//クリアしてないステージ
		if (GetLoadStage(static_cast<SaveElea>(i)).ClearStage == false)
		{
			// ステージ番号 (0 ～ 14)
			// クリアせずにステージから出てきたら、壊れてないブロックを作成するため for文 を抜ける
			// -3 することで SCENE_STAGE1_1 から 0 として扱う
			if (_GetBeforeScene() - 3 == i) { break; }

			//壊すブロックの番号を決定
			m_breakBlock = static_cast<SaveElea>(i);

			//ステージ番号からブロック読み込み
			switch (i / 5)
			{
			case 0: { pBlock = new Image2D("Assets/2D/animation/block1.png", pSM); } break;
			case 1: { pBlock = new Image2D("Assets/2D/animation/block2.png", pSM); } break;
			case 2: { pBlock = new Image2D("Assets/2D/animation/block3.png", pSM); } break;
			}

			// ステージ番号から位置を指定
			// 2-1 であれば 0番目 (SELECT1_POS_X) の位置に作る
			switch (i % 5)
			{
			case 0: { pBlock->pos.x = SELECT1_POS_X; } break;
			case 1: { pBlock->pos.x = SELECT2_POS_X; } break;
			case 2: { pBlock->pos.x = SELECT3_POS_X; } break;
			case 3: { pBlock->pos.x = SELECT4_POS_X; } break;
			case 4: { pBlock->pos.x = SELECT5_POS_X; } break;
			}

			//ブロックの位置や大きさなど
			pBlock->pos.y = 600.0f;
			pBlock->size = { 200.0f, 350.0f };
			pBlock->SetTexScale(14, 1);

			//ブロック一覧に格納
			m_mapBlocks[m_breakBlock] = pBlock;

			break; 
		}
	}


	//壊れてないブロックを作成
	for (i += 1; i <= Stage35; i++)
	{
		//ステージごとにブロック画像読み込み
		switch (i / 5)
		{
		case 0: { pBlock = new Image2D("Assets/2D/animation/block1.png", pSM); } break;
		case 1: { pBlock = new Image2D("Assets/2D/animation/block2.png", pSM); } break;
		case 2: { pBlock = new Image2D("Assets/2D/animation/block3.png", pSM); } break;
		}

		// ステージ番号から位置を指定
		// 2-1 であれば 0番目 (SELECT1_POS_X) の位置に作る
		switch (i % 5)
		{
		case 0: { pBlock->pos.x = SELECT1_POS_X; } break;
		case 1: { pBlock->pos.x = SELECT2_POS_X; } break;
		case 2: { pBlock->pos.x = SELECT3_POS_X; } break;
		case 3: { pBlock->pos.x = SELECT4_POS_X; } break;
		case 4: { pBlock->pos.x = SELECT5_POS_X; } break;
		}

		//ブロックの位置や大きさなど
		pBlock->pos.y = 600.0f;
		pBlock->size = { 200.0f, 350.0f };
		pBlock->SetTexScale(14, 1);

		//ブロック一覧に格納
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
		//現在のステージでなければ表示しない
		if (static_cast<SelectState::STAGE>( ((*it).first / 5) + 1) != nowStage) continue;

		//ブロックが無ければ表示しない
		if ((*it).second == nullptr) continue;

		//表示
		(*it).second->Draw();
	}
}


//--------------------------------------------------------
// ブロック破壊演出
// 破壊中は false が返され、呼び出し元で入力を制限する
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
