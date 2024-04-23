#include "Game3D.h"
#include "WinUtil.h"

#include "ModelManager.h"
#include "ModelManager_Class.h"
#include "Effect_Manager.h"
#include "SaveLoad.h"
///#include "DebugConsole.h"

#include "Scene.h"
#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Game.h"
#include "Scene_Stage1_1.h"
#include "Scene_Stage1_2.h"
#include "Scene_Stage1_3.h"
#include "Scene_Stage1_4.h"
#include "Scene_Stage1_5.h"
#include "Scene_Stage2_1.h"
#include "Scene_Stage2_2.h"
#include "Scene_Stage2_3.h"
#include "Scene_Stage2_4.h"
#include "Scene_Stage2_5.h"
#include "Scene_Stage3_1.h"
#include "Scene_Stage3_2.h"
#include "Scene_Stage3_3.h"
#include "Scene_Stage3_4.h"
#include "Scene_Stage3_5.h"

#include <thread>
#include "LoadScene.h"
#include "Input.h"
#include "Timer.h"
#include <atomic>



//--------------------
//�@�v���g�^�C�v�錾
//--------------------

//���[�h����
//	SCENE NextScene : ���̃V�[��
void _SceneChangeLoad();

//���[�h����ʏ���
void _SceneChangeScreen();

//���f������[�ǂ��Ƃ��܁[�� ^_^
void _LoadModel_BackGround();



//------------------
//�@�O���[�o���ϐ�
//------------------
namespace
{
	///DebugConsole* g_pDebugConsole;

	CScene *g_pNowSceneData;		//���݃V�[���̃f�[�^
	CScene *_g_pBeforeSceneData;	//�O�V�[���̃f�[�^
	SCENE g_NowScene;			//���݂̃V�[��
	SCENE _g_BeforeScene;		//�O�̃V�[��
	bool g_ChangeScene;			//�V�[���ύX�t���O

	CScene_Load* g_pLoadScene;		//���[�h�����̃V�[�����
	std::thread _th_BackLoad;		//���Ń��[�h����
	std::atomic<bool> g_Loading;	//���[�h�I���t���O
}



//----------------
//�@Game3D�N���X
//----------------
Game3D::Game3D()
{
	///g_pDebugConsole = new DebugConsole;

	//���f��������
	CModelManager::c_ModelManager_Init();
	ModelManager_Init();
	_th_BackLoad = std::thread{ _LoadModel_BackGround };

	//�G�t�F�N�g������
	Effect_Manager::Effect_Init(); 

	//�X�v���C�g������
	Sprite::Init();
	SpriteManager::Init();

	//�V�[���f�[�^������
	g_pNowSceneData = nullptr;
	SceneChange(SCENE_TITLE);

	//���[�h��ʏ�����
	g_pLoadScene = new CScene_Load(); 
	
	//csv�t�@�C���̃Z�[�u�f�[�^��ǂݍ���(���[�h)
	FileLoad();
}

Game3D::~Game3D()
{
	//SE��S�폜
	SE::_Destroy();

	//�Z�[�u�f�[�^��csv�t�@�C���ɏ�������(�Z�[�u)
	FileSave();

	delete g_pNowSceneData;	//�V�[���f�[�^�폜
	delete g_pLoadScene;	//���[�h��ʍ폜

	//�X�v���C�g�폜
	Sprite::Uninit();

	//�G�t�F�N�g�폜
	Effect_Manager::Effect_Uninit();

	//���f���폜
	_th_BackLoad.join();
	ModelManager_Uninit();
	CModelManager::c_ModelManager_Uninit();

	///delete g_pDebugConsole;
}

void Game3D::Update()
{
	//�V�[����ύX����
	if (g_ChangeScene)
	{
		g_ChangeScene = false;	//�V�[���ύX�v����j��
		g_Loading = true;		//���[�h�J�n

		//���݂̃V�[��������΃R�s�[����
		if (g_pNowSceneData != nullptr) 
		{
			_g_pBeforeSceneData = g_pNowSceneData;
		}

		std::thread th_load{ _SceneChangeLoad };
		std::thread th_screen{ _SceneChangeScreen };

		th_load.join();
		th_screen.join();

		g_pLoadScene->Reset(); //���[�h�V�[���̏������Z�b�g

		return;
	}


	//�X�V����
	g_pNowSceneData->Update();
	///g_pDebugConsole->Update();
}

void Game3D::Draw()
{
	g_pNowSceneData->Draw();
}



//--------------
//�@�V�[���ύX
//--------------
void SceneChange(const SCENE NextScene)
{
	//�Q�[�����I���
	if (NextScene == SCENE_END) 
	{
		DestroyWindow(GetHWND()); 
	}

	//���̃V�[����ǂݍ���
	else
	{
		_g_BeforeScene = g_NowScene;
		g_NowScene = NextScene;
		g_ChangeScene = true;
	}
}

void _SceneChangeLoad()
{
	//SE��S�폜
	SE::_Destroy();

	Sleep(1000);


	//���[�h����ʂɈڍs������O�V�[�����폜
	auto DeleteBeforeScene = []()
	{
		if (_g_pBeforeSceneData == nullptr) { return; }

		while (true)
		{
			if (g_pLoadScene->GetLoadState() == CScene_Load::LOAD_LOADING || 
				g_pLoadScene->GetLoadState() == CScene_Load::LOAD_AFTER)
			{
				delete _g_pBeforeSceneData;
				break;
			}
		}
	};
	std::thread deleteBeforeScene{ DeleteBeforeScene };

	Effect_Manager::All_EffectStop();
	//�V�[���̃��[�h
	switch (g_NowScene)
	{
		case SCENE_TITLE:	g_pNowSceneData = new CScene_Title(); break;				//�^�C�g���V�[��
		case SCENE_SELECT:	g_pNowSceneData = new CScene_Select(_g_BeforeScene); break;	//�Z���N�g�V�[��
		case SCENE_GAME:	g_pNowSceneData = new CScene_Game(); break;					//�Q�[���V�[��
		
		case SCENE_STAGE1_1: g_pNowSceneData = new CStage1_1();	break;		//�X�e�[�W1-1
		case SCENE_STAGE1_2: g_pNowSceneData = new CStage1_2();	break;		//�X�e�[�W1-2
		case SCENE_STAGE1_3: g_pNowSceneData = new CStage1_3();	break;		//�X�e�[�W1-3
		case SCENE_STAGE1_4: g_pNowSceneData = new CStage1_4();	break;		//�X�e�[�W1-4
		case SCENE_STAGE1_5: g_pNowSceneData = new CStage1_5();	break;		//�X�e�[�W1-5
		case SCENE_STAGE2_1: g_pNowSceneData = new CStage2_1();	break;		//�X�e�[�W2-1
		case SCENE_STAGE2_2: g_pNowSceneData = new CStage2_2();	break;		//�X�e�[�W2-2
		case SCENE_STAGE2_3: g_pNowSceneData = new CStage2_3();	break;		//�X�e�[�W2-3
		case SCENE_STAGE2_4: g_pNowSceneData = new CStage2_4();	break;		//�X�e�[�W2-4
		case SCENE_STAGE2_5: g_pNowSceneData = new CStage2_5();	break;		//�X�e�[�W2-5
		case SCENE_STAGE3_1: g_pNowSceneData = new CStage3_1();	break;		//�X�e�[�W3-1
		case SCENE_STAGE3_2: g_pNowSceneData = new CStage3_2();	break;		//�X�e�[�W3-2
		case SCENE_STAGE3_3: g_pNowSceneData = new CStage3_3();	break;		//�X�e�[�W3-3
		case SCENE_STAGE3_4: g_pNowSceneData = new CStage3_4();	break;		//�X�e�[�W3-4
		case SCENE_STAGE3_5: g_pNowSceneData = new CStage3_5();	break;		//�X�e�[�W3-5
	}

	deleteBeforeScene.join();

	g_pLoadScene->LoadEnd();	//���[�h�I�������[�h�V�[���ɒʒm
}

void _SceneChangeScreen()
{
	while (true) //���[�h���I������܂Ŏ��s
	{
		if (UpdateTimer())
		{
			//�X�V
			g_pLoadScene->Update();


			//�`��
			BeginDrawDX();

			switch (g_pLoadScene->GetLoadState())
			{
			case CScene_Load::LOAD_BEFORE:
			{
				if (_g_pBeforeSceneData) { _g_pBeforeSceneData->Draw(); }
				g_pLoadScene->Draw();
			}
			break;

			case CScene_Load::LOAD_LOADING:
			{
				g_pLoadScene->Draw();
			}
			break;

			case CScene_Load::LOAD_AFTER:	
			{
				g_pNowSceneData->Draw();
				g_pLoadScene->Draw();
			}
			break;
			}

			EndDrawDX();


			//���[�h��ʂ��I������甲����
			if (g_pLoadScene->GetLoadState() == CScene_Load::LOAD_NONE) { break; }
		}
	}
}



//--------------------------------
// �Q�[���n�܂�O�Ƀ��[�h���Ƃ���
//--------------------------------
void _LoadModel_BackGround()
{
	//�X�e�[�W1�Ŏg������
	CModelManager::c_AddModel("Stage1", "Assets/steage/steage1/steage1.fbx", "steage1.png");
	CModelManager::c_AddModel("Stage1_Deppari", "Assets/steage/steage1/steage1_deppari.fbx", "steage1_deppari.png");
	CModelManager::c_AddModel("Player", "Assets/New_Character/characterrobonock.fbx");
	CModelManager::c_AddAnimetion("Walk", "Assets/New_Character/character_anim_walk.fbx", "Player", 25.0f);
	CModelManager::c_AddAnimetion("Charge", "Assets/New_Character/character_anim_charge.fbx", "Player", 125.0f);
	CModelManager::c_AddAnimetion("Charge_First", "Assets/New_Character/character_anim_charge_first.fbx", "Player", 100.0f);
	CModelManager::c_AddAnimetion("Clear", "Assets/New_Character/character_anim_clear.fbx", "Player", 265.0f);
	CModelManager::c_AddAnimetion("Over", "Assets/New_Character/character_anim_gameover.fbx", "Player", 175.0f);
	CModelManager::c_AddAnimetion("knock", "Assets/New_Character/character_anim_knock.fbx", "Player", 150.0f);

	CModelManager::c_AddModel("Jewely", "Assets/NewItem/item_houseki1.fbx");

	CModelManager::c_AddModel("Soil", "Assets/New_Block/tuti/blocks_tuti.fbx");
	CModelManager::c_AddModel("Stone", "Assets/New_Block/isi/blocks_isi.fbx");
	CModelManager::c_AddModel("StoneDamage1", "Assets/New_Block/isi/blocks_isi.fbx", "base_isi1.png");
	CModelManager::c_AddModel("StoneDamage2", "Assets/New_Block/isi/blocks_isi.fbx", "base_isi2.png");
	CModelManager::c_AddModel("StoneDamage3", "Assets/New_Block/isi/blocks_isi.fbx", "base_isi3.png");
	CModelManager::c_AddModel("Concrete", "Assets/New_Block/konnkurito/blocks_konnkurito.fbx");
	CModelManager::c_AddModel("ConcreteDamage1", "Assets/New_Block/konnkurito/blocks_konnkurito.fbx", "base_konnkuri-to1.png");
	CModelManager::c_AddModel("ConcreteDamage2", "Assets/New_Block/konnkurito/blocks_konnkurito.fbx", "base_konnkuri-to2.png");
	CModelManager::c_AddModel("ConcreteDamage3", "Assets/New_Block/konnkurito/blocks_konnkurito.fbx", "base_konnkuri-to3.png");
	CModelManager::c_AddModel("Water", "Assets/New_Block/mizu/blocks_mizu.fbx");
	CModelManager::c_AddModel("SquareWater", "Assets/New_Block/mizu/Square/blocks_mizu.fbx");
	CModelManager::c_AddModel("Sand", "Assets/New_Block/suna/blocks_suna.fbx");
	CModelManager::c_AddModel("Clay", "Assets/New_Block/nendo/blocks_nendo.fbx");

	//�X�e�[�W2�Ŏg������
	CModelManager::c_AddModel("Stage2", "Assets/steage/steage2/steage2.fbx", "steage2.png");
	CModelManager::c_AddModel("Stage2_Deppari", "Assets/steage/steage2/steage2_deppari.fbx", "steage2_deppari.png");
	CModelManager::c_AddModel("Bedrock", "Assets/New_Block/ganban/blocks_ganban.fbx");

	//�X�e�[�W3�Ŏg������
	CModelManager::c_AddModel("Stage3", "Assets/steage/steage3/steage3.fbx", "steage3.png");
	CModelManager::c_AddModel("Stage3_Deppari", "Assets/steage/steage3/steage3_deppari.fbx", "steage3_deppari.png");
	CModelManager::c_AddModel("Heat", "Assets/NewItem/item_heatitem1.fbx");
	CModelManager::c_AddModel("Ice", "Assets/New_Block/koori/blocks_koori.fbx");
	CModelManager::c_AddModel("GAS", "Assets/New_Block/gass/blocks_gasss.fbx");
	CModelManager::c_AddModel("Magma", "Assets/New_Block/magma/blocks_yogan.fbx");
}


//--------------------------------
// ���̃V�[�����擾
//--------------------------------
SCENE _GetNowScene() { return g_NowScene; }
SCENE _GetBeforeScene() { return _g_BeforeScene; }
