#include "StageBase.h"
#include <stdio.h>
#include "BlockBase.h"
#include "ItemBase.h"
#include <Windows.h>
#include "PileBankerBase.h"

//�p�C���o���J�[ 
#include "Main_Bunker.h"
#include "Side_Banker.h"

void Stage_Base::NvigateUpdate()
{
	if (m_pNavigate)
	{
		m_pNavigate->Update();
	}

	if (m_pSideBanker)
	{
		m_pSideBanker->Update();
	}
}

void Stage_Base::NvigateDraw()
{
	//�p�C���o���J�[�`��
	if (m_pNavigate)
	{
		m_pNavigate->Draw();
	}

	if (m_pSideBanker)
	{
		m_pSideBanker->Draw();
	}
}

//�c�Y�����
void Stage_Base::CreateMainBanker(int LineNum, FloatPos InstancePos, bool Heet)
{
	if (!m_pNavigate)
	{
		Main_Bunker* pMainBanker = new Main_Bunker(this, LineNum, InstancePos, Heet);
		pMainBanker->SetCameraManager(m_pCameraManager);
		pMainBanker->SetModelManager(m_pModelManager);
		pMainBanker->Can_TypeInSide(m_CanTypeIn_Side);
		m_pNavigate = pMainBanker;
	}
}

//���Y�����
void Stage_Base::CreateSideBanker()
{
	//�c�Y�͍���Ă��邯�ǉ��Y�͍���Ă��Ȃ��ꍇ
	if (!m_pSideBanker && m_pNavigate)
	{
		m_pSideBanker = new Side_Banker(this, m_pNavigate);
		m_pSideBanker->SetCameraManager(m_pCameraManager);
		m_pSideBanker->SetModelManager(m_pModelManager);
	}
}

//�c�Y������
void Stage_Base::DestroyMainBanker()
{
	if (m_pNavigate)
	{
		delete m_pNavigate;
		m_pNavigate = nullptr;
	}
}

//���Y������
void Stage_Base::DestroySideBanker()
{
	if (m_pSideBanker)
	{
		delete m_pSideBanker;
		m_pSideBanker = nullptr;
	}
}

//�B�ł��̏���Ԃ�
PileBanker* Stage_Base::GetPileBanker()
{
	return m_pNavigate;
}

//���Y�̏���Ԃ�
PileBanker* Stage_Base::GetSideBanker()
{
	return m_pSideBanker;
}

//�T�C�h�o���J�[��ł����߂Ȃ��悤�ɂ���
void Stage_Base::SetCantTypeIn_Side()
{
	m_CanTypeIn_Side = false;
}