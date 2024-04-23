#include "UI_OverPeople.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"
#include "Game3D.h"

const int MaxUI(3);

//----------------------------
// コンストラクタ
//----------------------------
UI_OverPeople::UI_OverPeople(SpriteManager* pSM)
{
	for (int i = 0; i < MaxUI; i++)
	{
		m_pPeople[i] = new BillBoard("Assets/2D/People/pict2.png", pSM);
		m_pPeople[i]->pos = { -550.0f + (rand() % 250), 255.0f, (rand() % 70) + 15.0f };
		m_pPeople[i]->size = { 100.0f, 100.0f };
		m_pPeople[i]->SetTexScale(1, 1);
		m_pPeople[i]->texNum = 0.0f;

		m_pPeople1[i] = new BillBoard("Assets/2D/People/pict3.png", pSM);
		m_pPeople1[i]->pos  = { -250.0f + (rand() % 250), 255.0f, (rand() % 50) + 15.0f};
		m_pPeople1[i]->size = { 100.0f, 100.0f };
		m_pPeople1[i]->SetTexScale(1, 1);
		m_pPeople1[i]->texNum = 0.0f;

		m_pPeople2[i] = new BillBoard("Assets/2D/People/pict5.png", pSM);
		m_pPeople2[i]->pos = { 250.0f + (rand() % 250), 255.0f, (rand() % 30) + 15.0f };
		m_pPeople2[i]->size = { 100.0f, 100.0f };
		m_pPeople2[i]->SetTexScale(1, 1);
		m_pPeople2[i]->texNum = 0.0f;

		
	}

	m_pCar = new BillBoard("Assets/2D/People/pict6.png", pSM);
	m_pCar->pos = { 0.0f + (rand() % 250), 255.0f,  (rand() % 10) + 15.0f };
	m_pCar->size = { 200.0f, 120.0f };
	m_pCar->SetTexScale(1, 1);
	m_pCar->texNum = 0.0f;

}


//----------------------------
// デストラクタ
//----------------------------
UI_OverPeople::~UI_OverPeople()
{
	delete m_pCar;

	for (int i = 0; i < MaxUI; i++)
	{
		
		delete m_pPeople[i];
		delete m_pPeople1[i];
		delete m_pPeople2[i];
	}
}


//----------------------------
// 更新
//----------------------------
void UI_OverPeople::Update()
{


}


//----------------------------
// 描画
//----------------------------
void UI_OverPeople::Draw()
{

	for (int i = 0; i < MaxUI; i++)
	{
		m_pPeople[i]->Draw();
		m_pPeople1[i]->Draw();
		m_pPeople2[i]->Draw();
	}

	for (int i = 0; i < 1; i++)
	{
		// ステージ２では車は表示させない
		if (_GetNowScene() == SCENE::SCENE_STAGE2_1)
		{
			break;
		}
		else if (_GetNowScene() == SCENE::SCENE_STAGE2_2)
		{
			break;
		}
		else if (_GetNowScene() == SCENE::SCENE_STAGE2_3)
		{
			break;
		}

		m_pCar->Draw();
	}
	
	
}
