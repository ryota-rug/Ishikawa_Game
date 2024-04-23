#include "StageBase.h"
#include <stdio.h>
#include "BlockBase.h"
#include "ItemBase.h"
#include <Windows.h>
#include "PileBankerBase.h"
#include <time.h>
#include <stdlib.h>


//ブロック
#include "Clay.h"
#include "Soil.h"
#include "Stone.h"
#include "Concrete.h"
#include "Bedrock.h"
#include "Sand.h"
#include "Ice.h"
#include "Water.h"
#include "Magma.h"
#include "Gas.h"

#include "VirtualBlock.h"

//パイルバンカー 
#include "Main_Bunker.h"
#include "Side_Banker.h"

//プレイヤー
#include "Player.h"

//アイテム
#include "Jewely.h"
#include "Heat.h"

const FloatPos Stage_Base::CenterPos = { 0.0f,0.0f,0.0f };
//IntPos Stage_Base::m_Stage_Width;

Stage_Base::Stage_Base()
	:m_Stage_Width({10,10}),
	m_pNavigate(nullptr),		//釘を作る場所
	m_pSideBanker(nullptr),
	m_pPlayer(nullptr),
	m_mapInfo_Block(nullptr),	//ブロックの配列を作る場所
	m_mapInfo_Jewely(nullptr),
	m_mapInfo_Heet(nullptr),
	m_pModelManager(nullptr),	//モデルを描画する変数
	m_pCameraManager(nullptr),
	m_JewelyCount(0),		//宝石の数
	m_BreakNum(0),          // 破壊したブロック数 
	m_GameClear(false),		//これをtrueにしたらゲームクリア
	m_GameOver(false),		//これをtrueにしたらゲームオーバー
	m_GameOverType(GAMEOVER_TYPE::GAMEOVER_DFAULT),	//ゲームオーバーの種類
	m_CanTypeIn_Side(true),
	m_pJewelryUI(nullptr)
{
	m_VirtualBlock = new VirtualBlock((this),999,999);		//配列外を参照したときに返すブロック
	CModelManager::c_AddModel("MAIN_PILE",	"Assets/New_Character/Kui/kui.fbx");
	CModelManager::c_AddModel("MAIN_ADD_PILE",	"Assets/New_Character/Kui/addkui.fbx");
	CModelManager::c_AddModel("SIDE_PILE",	"Assets/New_Character/Kui/yokokui1.fbx");
	CModelManager::c_AddModel("SIDE_ADD_PILE",	"Assets/New_Character/Kui/addyokokui1.fbx");
	CModelManager::c_AddModel("MAIN_PILE_NETU", "Assets/New_Character/atukui/atukui.fbx");
	CModelManager::c_AddModel("MAIN_ADD_PILE_NETU", "Assets/New_Character/atukui/atuaddkui.fbx");
	CModelManager::c_AddModel("SIDE_PILE_NETU", "Assets/New_Character/atukui/atuyokokui0_05.fbx");
	CModelManager::c_AddModel("SIDE_ADD_PILE_NETU", "Assets/New_Character/atukui/atuaddyokokui0_05.fbx");
	//CModelManager::c_AddModel("STAGE",		"Assets/Stage/steage_kari/steage1.fbx");

	m_pUI = new GameUI;
	m_pJewelryUI = new JewelryUI();
	m_pBreakUI = new BreakNumUI();

	m_pClearSE = new SE("Assets/SE/GameClear.wav");
	m_pOverSE = new SE("Assets/SE/GameOver.wav");

}

Stage_Base::~Stage_Base()
{
	delete m_pClearSE;
	delete m_pOverSE;

	delete m_pBreakUI;
	delete m_pJewelryUI;
	delete m_pUI;

	//vectorのブロックを消す
	for (auto it : m_RefugeBlock)
	{
		if (it != nullptr)
		{
			delete it;
		}
	}
	m_RefugeBlock.clear();
	
	//無敵ブロックを消す
	delete m_VirtualBlock;
	m_VirtualBlock = nullptr;

	//横杭を消す
	if (m_pSideBanker)
	{
		delete m_pSideBanker;
		m_pSideBanker = nullptr;
	}

	//縦杭を消す
	if (m_pNavigate)
	{
		delete m_pNavigate;
		m_pNavigate = nullptr;
	}

	int BlockNum = m_Stage_Width.X * m_Stage_Width.Y;

	for (int i = 0; i < BlockNum; i++)
	{
		if (m_mapInfo_Heet[i] != nullptr)
		{
			delete m_mapInfo_Heet[i];
			m_mapInfo_Heet[i] = nullptr;
		}
	}

	if (m_mapInfo_Heet != nullptr)
	{
		delete m_mapInfo_Heet;
	}

	for (int i = 0; i < BlockNum; i++)
	{
		if (m_mapInfo_Jewely[i] != nullptr)
		{
			delete m_mapInfo_Jewely[i];
			m_mapInfo_Jewely[i] = nullptr;
		}
	}

	if (m_mapInfo_Jewely != nullptr)
	{
		delete m_mapInfo_Jewely;
	}

	for (int i = 0; i < m_Stage_Width.X * m_Stage_Width.Y; i++)
	{
		if (m_mapInfo_Block[i] != nullptr)
		{
			delete m_mapInfo_Block[i];
			m_mapInfo_Block[i] = nullptr;
		}
	}

	if (m_mapInfo_Block != nullptr)
	{
		delete m_mapInfo_Block;
	}

	if (m_pPlayer != nullptr)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}

//継承用の更新処理
void Stage_Base::Update()
{
	//if (m_pCameraManager->Get_NowType() ==
	//	C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MAIN)
	//{
		m_pJewelryUI->GetMoveJewelry();
	//}
	
}

//描画用の更新処理
void Stage_Base::Draw()
{

	//m_pModelManager->c_ModelDraw("STAGE", 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f);;
}

IntPos Stage_Base::GetStageWidthNum()
{
	return m_Stage_Width;
}

//入れた配列の番号の座標(float)を返す
FloatPos Stage_Base::Get_DrawPos(int X, int Y)
{
	if (m_Stage_Width.X <= X || 0 > X ||
		m_Stage_Width.Y <= Y || 0 > Y)
	{
		MessageBox(nullptr, "変換されるマップ座標の数値が異常です ", "Error", MB_OK);
	}

	FloatPos ReturnFloat;
	ReturnFloat.X = m_BasePos.X + (X * Block_Base::BlockSize) + (Block_Base::BlockSize * 0.5f);
	ReturnFloat.Y = m_BasePos.Y - (Y * Block_Base::BlockSize) - (Block_Base::BlockSize * 0.5f);
	ReturnFloat.Z = m_BasePos.Z;
	return ReturnFloat;
}

//入れた座標の配列の番号(int)を返す
IntPos Stage_Base::Get_MapPos(float X, float Y)
{
	if (m_BasePos.X + ((float)m_Stage_Width.X * Block_Base::BlockSize) < X ||
		m_BasePos.X > X || m_BasePos.Y < Y ||
		m_BasePos.Y - ((float)m_Stage_Width.Y * Block_Base::BlockSize) > Y)
	{
		MessageBox(nullptr, "変換されるマップ座標の数値が異常です ", "Error", MB_OK);
	}

	IntPos ReturnInt;
	ReturnInt.X = (int)((X - m_BasePos.X) / Block_Base::BlockSize);
	ReturnInt.Y = (int)((m_BasePos.Y - Y) / Block_Base::BlockSize);
	return ReturnInt;
}

CModelManager* Stage_Base::Get_ModelManager_Address()
{
	return m_pModelManager;
}


// ブロックを破壊数を取得
// 引数：int Num 壊したブロック数
BreakNumUI* Stage_Base::GetBreakNum(int Num)
{
	m_BreakNum = Num;
	m_pBreakUI->AddNum(m_BreakNum);

	return m_pBreakUI;
}

BreakNumUI* Stage_Base::GetBreakInfo()
{
	return m_pBreakUI;
}

FloatPos Stage_Base::GetBasePos()
{
	return m_BasePos;
}

void Stage_Base::Mina_Jewely()
{
	m_JewelyCount--;

	// 宝石のUI切り替え
	m_pJewelryUI->GetJewelryUI();

	if (m_JewelyCount <= 0)
	{
		m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_CLEAR
			, m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MAIN)->GetPos(),
			m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MAIN)->GetLook());
		Set_GameClear();
	}
}

void Stage_Base::Set_GameClear()
{
	if (m_GameClear || m_GameOver) 
	{
		return;
	}

	m_pClearSE->Play();
	m_GameClear = true;
}
bool Stage_Base::Get_GameClear()
{
	return m_GameClear;
}

void Stage_Base::Set_GameOver(GAMEOVER_TYPE Type)
{
	if(m_GameClear || m_GameOver)
	{
		return;
	}

	m_GameOverType = Type;
	m_pOverSE->Play();
	m_GameOver = true;
}

bool Stage_Base::Get_GameOver()
{
	return m_GameOver;
}

Stage_Base::GAMEOVER_TYPE Stage_Base::Get_GameOverType()
{
	return m_GameOverType;
}

//ステージの情報を作る
void Stage_Base::CreateStage(int X_Width, int Y_Height, const char* FileName)
{
	const int X_WIDTH = 7;
	const int Y_HEIGHT = 8;
	int StageNum = X_WIDTH * Y_HEIGHT;

	m_Stage_Width.X = X_WIDTH;
	m_Stage_Width.Y = Y_HEIGHT;
	
	float StageWidth = Block_Base::BlockSize * X_WIDTH;
	float StageHeight = Block_Base::BlockSize * Y_HEIGHT;
	//左上のポジション
	m_BasePos.X = CenterPos.X - StageWidth * 0.5f;
	m_BasePos.Y = CenterPos.Y + StageHeight * 0.5f;
	m_BasePos.Z = CenterPos.Z;

	//ブロックの生成-----------------------------------------------
	m_mapInfo_Block = new Block_Base*[StageNum] {nullptr};

	//fopenをする
	//仮-------------------------------------------------------
	int BlockNumbers[Y_HEIGHT][X_WIDTH] =
	{
		{4,4,4,4,4,4,4},
		{2,5,2,2,2,2,2},
		{2,5,2,2,10,2,8},
		{2,5,2,2,10,3,2},
		{8,2,2,2,2,3,2},
		{2,3,2,2,2,3,2},
		{2,3,2,2,2,3,2},
		{2,3,2,2,2,3,2}
	};
	//--------------------------------------------------------
	////X*Y分だけデータを持ってくる
	for (int i = 0; i < StageNum; i++)
	{
		bool Instance = true;

		int tmpX = i % m_Stage_Width.X;
		int tmpY = i / m_Stage_Width.X;

		Block_Base::BLOCK_TYPE type = (Block_Base::BLOCK_TYPE)BlockNumbers[tmpY][tmpX];

		//ブロックの生成
		switch (type)
		{
		case Block_Base::BLOCK_NONE:
			m_mapInfo_Block[i] = nullptr;
			Instance = false;
			break;

		case Block_Base::BLOCK_CLAY:	 m_mapInfo_Block[i] = new CClay(this, tmpX, tmpY);		break;
		case Block_Base::BLOCK_SOIL:	 m_mapInfo_Block[i] = new CSoil(this, tmpX, tmpY);		break;
		case Block_Base::BLOCK_STONE:	 m_mapInfo_Block[i] = new CStone(this, tmpX, tmpY);		break;
		case Block_Base::BLOCK_CONCRETE: m_mapInfo_Block[i] = new CConcrete(this, tmpX, tmpY);	break;
		case Block_Base::BLOCK_BEDROCK:  m_mapInfo_Block[i] = new CBedrock(this, tmpX, tmpY);	break;
		case Block_Base::BLOCK_SAND:	 m_mapInfo_Block[i] = new CSand(this, tmpX, tmpY);		break;
		case Block_Base::BLOCK_ICE:		 m_mapInfo_Block[i] = new CIce(this, tmpX, tmpY);		break;
		case Block_Base::BLOCK_WATER:	 m_mapInfo_Block[i] = new CWater(this, tmpX, tmpY);		break;
		case Block_Base::BLOCK_MAGMA:	 m_mapInfo_Block[i] = new CMagma(this, tmpX, tmpY);		break;
		case Block_Base::BLOCK_GAS:		 m_mapInfo_Block[i] = new CGas(this, tmpX, tmpY);		break;

		default:
			m_mapInfo_Block[i] = nullptr;
			Instance = false;
			break;
		}

		//生成したブロックのポジションを設定
		if (Instance)
		{
			m_mapInfo_Block[i]->SetPos(m_BasePos.X + (Block_Base::BlockSize * (i % X_WIDTH)) + (Block_Base::BlockSize * 0.5f),
				m_BasePos.Y - (Block_Base::BlockSize * (i / X_WIDTH)) - (Block_Base::BlockSize * 0.5f),
				m_BasePos.Z);
		}
	}
	//----------------------------------------------------------------------------------
	//ジュエリーの生成
	m_mapInfo_Jewely = new CItemBase*[StageNum] {nullptr};

	//仮-------------------------------------------------------
	int JewelyNumbers[Y_HEIGHT][X_WIDTH] =
	{
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0},
		{0,1,0,0,0.0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0}
	};
	//--------------------------------------------------------

	for (int i = 0; i < StageNum; i++)
	{
		bool Instance = true;

		CItemBase::ITEM_TYPE type = (CItemBase::ITEM_TYPE)JewelyNumbers[i / m_Stage_Width.X][i % m_Stage_Width.X];

		//ブロックの生成
		switch (type)
		{
		case CItemBase::JEWELY:
			m_mapInfo_Jewely[i] = new CJewely(this, i % m_Stage_Width.X, i / m_Stage_Width.X);
			m_JewelyCount++;
			break;
		default:
			m_mapInfo_Jewely[i] = nullptr;
			Instance = false;
			break;
		}


		if (Instance)
		{
			m_mapInfo_Jewely[i]->SetPos(m_BasePos.X + (Block_Base::BlockSize * (i % X_WIDTH)) + (Block_Base::BlockSize * 0.5f),
				m_BasePos.Y - (Block_Base::BlockSize * (i / X_WIDTH)) - (Block_Base::BlockSize * 0.5f),
				m_BasePos.Z);
		}
	}

	//---------------------------------------------------------------------------------
	//ヒートアイテムの生成
	m_mapInfo_Heet = new CItemBase*[StageNum] {nullptr};

	//仮-------------------------------------------------------
	int HeetNumbers[Y_HEIGHT][X_WIDTH] =
	{
		{0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0},
		{2,0,2,0,0,0,0},
		{2,0,2,0,0,0,0},
		{0,0,2,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0}
	};
	//--------------------------------------------------------
	
	for (int i = 0; i < StageNum; i++)
	{
		bool Instance = true;

		CItemBase::ITEM_TYPE type = (CItemBase::ITEM_TYPE)HeetNumbers[i / m_Stage_Width.X][i % m_Stage_Width.X];

		//ブロックの生成
		switch (type)
		{
		case CItemBase::HEAT:
			m_mapInfo_Heet[i] = new CHeat(this, i % m_Stage_Width.X, i / m_Stage_Width.X);
			break;
		default:
			m_mapInfo_Heet[i] = nullptr;
			Instance = false;
			break;
		}

		if (Instance)
		{
			m_mapInfo_Heet[i]->SetPos(m_BasePos.X + (Block_Base::BlockSize * (i % X_WIDTH)) + (Block_Base::BlockSize * 0.5f),
				m_BasePos.Y - (Block_Base::BlockSize * (i / X_WIDTH)) - (Block_Base::BlockSize * 0.5f),
				m_BasePos.Z);
		}
	}
}

void Stage_Base::CreateStage(int X_Width, int Y_Height, const int* BlockInfo, const int* JewelyInfo, const int* HeetInfo)
{
	int StageNum = X_Width * Y_Height;

	m_Stage_Width.X = X_Width;
	m_Stage_Width.Y = Y_Height;

	float StageWidth = Block_Base::BlockSize * X_Width;
	float StageHeight = Block_Base::BlockSize * Y_Height;

	m_StageLength.X = StageWidth;
	m_StageLength.Y = StageHeight;
	m_StageLength.Z = 0.0f;

	//左上のポジション
	m_BasePos.X = CenterPos.X - StageWidth * 0.5f;
	m_BasePos.Y = CenterPos.Y + StageHeight * 0.5f;
	m_BasePos.Z = CenterPos.Z;

	//ブロックの生成-----------------------------------------------
	m_mapInfo_Block = new Block_Base*[StageNum] {nullptr};


	////X*Y分だけデータを持ってくる
	for (int i = 0; i < StageNum; i++)
	{
		bool Instance = true;
		Block_Base::BLOCK_TYPE type = (Block_Base::BLOCK_TYPE)BlockInfo[i];

		//ブロックの生成
		switch (type)
		{
		case Block_Base::BLOCK_NONE:
			m_mapInfo_Block[i] = nullptr;
			Instance = false;
			break;

		case Block_Base::BLOCK_CLAY:	 m_mapInfo_Block[i] = new CClay(this, i % m_Stage_Width.X, i / m_Stage_Width.X); break;
		case Block_Base::BLOCK_SOIL:	 m_mapInfo_Block[i] = new CSoil(this, i % m_Stage_Width.X, i / m_Stage_Width.X); break;
		case Block_Base::BLOCK_STONE:	 m_mapInfo_Block[i] = new CStone(this, i % m_Stage_Width.X, i / m_Stage_Width.X); break;
		case Block_Base::BLOCK_CONCRETE: m_mapInfo_Block[i] = new CConcrete(this, i % m_Stage_Width.X, i / m_Stage_Width.X); break;
		case Block_Base::BLOCK_BEDROCK:  m_mapInfo_Block[i] = new CBedrock(this, i % m_Stage_Width.X, i / m_Stage_Width.X); break;
		case Block_Base::BLOCK_SAND:	 m_mapInfo_Block[i] = new CSand(this, i % m_Stage_Width.X, i / m_Stage_Width.X); break;
		case Block_Base::BLOCK_ICE:		 m_mapInfo_Block[i] = new CIce(this, i % m_Stage_Width.X, i / m_Stage_Width.X); break;
		case Block_Base::BLOCK_WATER:	 m_mapInfo_Block[i] = new CWater(this, i % m_Stage_Width.X, i / m_Stage_Width.X); break;
		case Block_Base::BLOCK_MAGMA:	 m_mapInfo_Block[i] = new CMagma(this, i % m_Stage_Width.X, i/m_Stage_Width.X); break;
		case Block_Base::BLOCK_GAS:		 m_mapInfo_Block[i] = new CGas(this, i % m_Stage_Width.X, i / m_Stage_Width.X); break;

		default:
			m_mapInfo_Block[i] = nullptr;
			Instance = false;
			break;
		}

		//生成したブロックのポジションを設定
		if (Instance)
		{
			m_mapInfo_Block[i]->SetPos(m_BasePos.X + (Block_Base::BlockSize * (i % X_Width)) + (Block_Base::BlockSize * 0.5f),
				m_BasePos.Y - (Block_Base::BlockSize * (i / X_Width)) - (Block_Base::BlockSize * 0.5f),
				m_BasePos.Z);
		}
	}
	//----------------------------------------------------------------------------------
	//ジュエリーの生成
	m_mapInfo_Jewely = new CItemBase*[StageNum] {nullptr};

	for (int i = 0; i < StageNum; i++)
	{
		bool Instance = true;

		CItemBase::ITEM_TYPE type = (CItemBase::ITEM_TYPE)JewelyInfo[i];

		//ブロックの生成
		switch (type)
		{
		case CItemBase::JEWELY:
			m_mapInfo_Jewely[i] = new CJewely(this, i % m_Stage_Width.X, i / m_Stage_Width.X);
			m_JewelyCount++;
			break;
		default:
			m_mapInfo_Jewely[i] = nullptr;
			Instance = false;
			break;
		}

		if (Instance)
		{
			m_mapInfo_Jewely[i]->SetPos(m_BasePos.X + (Block_Base::BlockSize * (i % X_Width)) + (Block_Base::BlockSize * 0.5f),
				m_BasePos.Y - (Block_Base::BlockSize * (i / X_Width)) - (Block_Base::BlockSize * 0.5f),
				m_BasePos.Z);
		}
	}

	// 宝石の数だけUIを作成
	m_pJewelryUI->MakeJewelryUI(m_JewelyCount);

	//---------------------------------------------------------------------------------
	//ヒートアイテムの生成
	m_mapInfo_Heet = new CItemBase*[StageNum] {nullptr};

	for (int i = 0; i < StageNum; i++)
	{
		bool Instance = true;

		CItemBase::ITEM_TYPE type = (CItemBase::ITEM_TYPE)HeetInfo[i];

		//ブロックの生成
		switch (type)
		{
		case CItemBase::HEAT:
			m_mapInfo_Heet[i] = new CHeat(this, i % m_Stage_Width.X, i / m_Stage_Width.X);
			break;
		default:
			m_mapInfo_Heet[i] = nullptr;
			Instance = false;
			break;
		}

		if (Instance)
		{
			m_mapInfo_Heet[i]->SetPos(m_BasePos.X + (Block_Base::BlockSize * (i % X_Width)) + (Block_Base::BlockSize * 0.5f),
				m_BasePos.Y - (Block_Base::BlockSize * (i / X_Width)) - (Block_Base::BlockSize * 0.5f),
				m_BasePos.Z);
		}
	}
}

//モデルマネージャーの設定
void Stage_Base::SetModelManager(CModelManager* pModelManager)
{
	m_pModelManager = pModelManager;
	int StageNum = m_Stage_Width.X * m_Stage_Width.Y;

	//ブロックがある分だけモデルマネージャーを設定してやる
	for (int i = 0; i < StageNum; i++)
	{
		if (m_mapInfo_Block[i] == nullptr)
		{
			continue;
		}

		m_mapInfo_Block[i]->Set_ModelManager(pModelManager);
	}

	//アイテムにモデルマネージャーを付ける
	for (int i = 0; i < StageNum; i++)
	{
		if (m_mapInfo_Jewely[i] == nullptr)
		{
			continue;
		}

		//モデルマネージャーなどを付ける
		m_mapInfo_Jewely[i]->Set_ModelManager(pModelManager);
	}

	for (int i = 0; i < StageNum; i++)
	{
		if (m_mapInfo_Heet[i] == nullptr)
		{
			continue;
		}
		//モデルマネージャーを付ける
		m_mapInfo_Heet[i]->Set_ModelManager(pModelManager);
	}

	if (m_pNavigate != nullptr)
	{
		m_pNavigate->SetModelManager(pModelManager);
	}

	if (m_pSideBanker != nullptr)
	{
		m_pSideBanker->SetModelManager(pModelManager);
	}

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->SetModelManager(m_pModelManager);
	}
}

void Stage_Base::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
	int StageNum = m_Stage_Width.X * m_Stage_Width.Y;

	//ブロックがある分だけモデルマネージャーを設定してやる
	for (int i = 0; i < StageNum; i++)
	{
		if (m_mapInfo_Block[i] == nullptr)
		{
			continue;
		}

		m_mapInfo_Block[i]->Set_CameraManager(pCameraManager);
	}

	//アイテムにカメラマネージャーを付ける
	for (int i = 0; i < StageNum; i++)
	{
		if (m_mapInfo_Jewely[i] == nullptr)
		{
			continue;
		}

		//カメラマネージャーなどを付ける
		m_mapInfo_Jewely[i]->Set_CameraManager(pCameraManager);
	}

	for (int i = 0; i < StageNum; i++)
	{
		if (m_mapInfo_Heet[i] == nullptr)
		{
			continue;
		}
		//カメラマネージャーを付ける
		m_mapInfo_Heet[i]->Set_CameraManager(pCameraManager);
	}

	if (m_pNavigate != nullptr)
	{
		m_pNavigate->SetCameraManager(pCameraManager);
	}

	if (m_pSideBanker != nullptr)
	{
		m_pSideBanker->SetCameraManager(pCameraManager);
	}

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->SetCameraManager(pCameraManager);
	}

	if (m_pJewelryUI != nullptr)
	{
		m_pJewelryUI->SetCameraManager(pCameraManager);
	}
}

//ステージのブロックを全て描画する
void Stage_Base::StageDraw()
{
	int BlockNum = m_Stage_Width.X * m_Stage_Width.Y;

	//ブロックの描画
	for (auto it : m_RefugeBlock)
	{
		if (it != nullptr)
		{
			it->Draw();
		}
	}

	for (int i = 0; i < BlockNum; i++)
	{
		if (!m_mapInfo_Block[i])
		{
			continue;
		}
		m_mapInfo_Block[i]->Draw();
	}

	//アイテムの描画
	for (auto it : m_RefugeItem)
	{
		if (it != nullptr)
		{
			it->Draw();
		}
	}

	for (int i = 0; i < BlockNum;i++)
	{
		if (!m_mapInfo_Jewely[i])
		{
			continue;
		}
		m_mapInfo_Jewely[i]->Draw();
	}

	for (int i = 0; i < BlockNum; i++)
	{
		if (!m_mapInfo_Heet[i])
		{
			continue;
		}
		m_mapInfo_Heet[i]->Draw();
	}

	//パイルバンカー描画
	if (m_pNavigate)
	{
		m_pNavigate->Draw();
	}
	
	if (m_pSideBanker)
	{
		m_pSideBanker->Draw();
	}

	//プレイヤー描画
	if (m_pPlayer)
	{
		m_pPlayer->Draw();
	}
}

// UI表示用
void Stage_Base::UIDraw()
{
	EnableDepth(false);

	
	m_pJewelryUI->Draw();	// 宝石
	m_pUI->Draw();          // メイン
	m_pBreakUI->Draw();

	EnableDepth(true);

	// アタックゲージ
	if (m_pNavigate != nullptr)
	{
		m_pNavigate->UIDraw();
	}

	// ヒートゲージ
	m_pPlayer->UIDraw();
	
}

void Stage_Base::ItemDraw()
{
	int BlockNum = m_Stage_Width.X * m_Stage_Width.Y;

	//アイテムの描画
	for (auto it : m_RefugeItem)
	{
		if (it != nullptr)
		{
			it->Draw();
		}
	}

	for (int i = 0; i < BlockNum; i++)
	{
		if (!m_mapInfo_Jewely[i])
		{
			continue;
		}
		m_mapInfo_Jewely[i]->Draw();
	}

	for (int i = 0; i < BlockNum; i++)
	{
		if (!m_mapInfo_Heet[i])
		{
			continue;
		}
		m_mapInfo_Heet[i]->Draw();
	}
}