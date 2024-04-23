#include "StageBase.h"
#include <stdio.h>
#include "BlockBase.h"
#include "ItemBase.h"
#include <Windows.h>
#include "PileBankerBase.h"

#include "Heat.h"

void Stage_Base::HeetUpdate()
{
	int BlockNum = m_Stage_Width.X * m_Stage_Width.Y;

	//非難しているブロックのアップデート
	for (auto it = m_RefugeItem.begin();
		it != m_RefugeItem.end();)
	{
		if ((*it) == nullptr)
		{
			continue;
		}

		//非難した後のアップデート
		(*it)->RefugeUpdate();

		if ((*it)->Get_Destroy())
		{
			delete (*it);
			it = m_RefugeItem.erase(it);
		}
		else
		{
			it++;
		}
	}

	for (int i = 0; i < BlockNum; i++)
	{
		if (m_mapInfo_Heet[i] == nullptr)
		{
			continue;
		}
		m_mapInfo_Heet[i]->Set_DidUpdate(false);
	}

	for (int i = 0; i < BlockNum; i++)
	{
		if (m_mapInfo_Heet[i] == nullptr)
		{
			continue;
		}

		if (m_mapInfo_Heet[i]->Get_DidUpdate())
		{
			continue;
		}

		m_mapInfo_Heet[i]->Set_DidUpdate(true);

		m_exeMoveItem = false;
		m_exeRefugeItem = false;;

		//アイテムのアップデート
		m_mapInfo_Heet[i]->Update();

		//アイテムを動かす
		if (m_exeMoveItem)
		{
			int ItemNum = m_Temporary_ItemPos.X + (m_Stage_Width.X * m_Temporary_ItemPos.Y);
			if (m_mapInfo_Heet[ItemNum] != nullptr)
			{
				//MessageBox(nullptr, "移動したいポジションにアイテムがあります ", "Error", MB_OK);
				continue;
			}
			//動く場合新しく入れるところに今のアイテムを入れる
			m_mapInfo_Heet[ItemNum] = m_mapInfo_Heet[i];
			//アイテムに場所を設定
			m_mapInfo_Heet[ItemNum]->SetMap(m_Temporary_ItemPos.X, m_Temporary_ItemPos.Y);
			m_mapInfo_Heet[i] = nullptr;
			continue;
		}

		//アイテムを避難する
		if (m_exeRefugeItem)
		{
			m_RefugeItem.push_back(m_mapInfo_Heet[i]);
			CItemBase *temp = m_RefugeItem.back();
			temp->Set_ModelManager(m_pModelManager);
			temp->Set_CameraManager(m_pCameraManager);
			m_mapInfo_Heet[i] = nullptr;
			continue;
		}

		if (m_mapInfo_Heet[i]->Get_Destroy())
		{
			delete  m_mapInfo_Heet[i];
			m_mapInfo_Heet[i] = nullptr;
			continue;
		}

	}

}

CItemBase* Stage_Base::GetHeet(int X, int Y)
{
	if (m_Stage_Width.X <= X || 0 > X ||
		m_Stage_Width.Y <= Y || 0 > Y)
	{
		return nullptr;
	}

	return m_mapInfo_Heet[X + m_Stage_Width.X * Y];
}

void Stage_Base::CreateHeet(int X, int Y)
{
	if (m_Stage_Width.X <= X || 0 > X ||
		m_Stage_Width.Y <= Y || 0 > Y)
	{
		return;
	}

	if (m_mapInfo_Heet[X + m_Stage_Width.X * Y] == nullptr)
	{
		int Create_ItemNum = X + m_Stage_Width.X * Y;
		//ジュエリーを作る
		m_mapInfo_Heet[Create_ItemNum] = new CHeat(this, X, Y);
		m_mapInfo_Heet[Create_ItemNum]->Set_ModelManager(m_pModelManager);
		m_mapInfo_Heet[Create_ItemNum]->Set_CameraManager(m_pCameraManager);
	}
	else
	{
		MessageBox(nullptr, "アイテムを作りたいしたいポジションにアイテムがあります ", "Error", MB_OK);
	}
}

void Stage_Base::DestroyHeet(int X, int Y)
{
	if (m_Stage_Width.X <= X || 0 > X ||
		m_Stage_Width.Y <= Y || 0 > Y)
	{
		return;
	}

	if (m_mapInfo_Heet[X + m_Stage_Width.X * Y] != nullptr)
	{
		//ジュエリーを作る
		delete m_mapInfo_Heet[X + m_Stage_Width.X * Y];
		m_mapInfo_Heet[X + m_Stage_Width.X * Y] = nullptr;
	}
}

void Stage_Base::MoveHeet(int X, int Y)
{
	if (m_Stage_Width.X <= X || 0 > X ||
		m_Stage_Width.Y <= Y || 0 > Y)
	{
		return;
	}

	//入れるべきアイテムの場所を入れておく
	m_Temporary_ItemPos.X = X;
	m_Temporary_ItemPos.Y = Y;

	m_exeMoveItem = true;

}