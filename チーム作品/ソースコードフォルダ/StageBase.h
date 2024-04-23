//#pragma once
#ifndef STAGE_BASE_H
#define STAGE_BASE_H
#include "Position_struct.h"
#include "CameraBase.h"
#include <vector>
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "GameUI.h"
#include "jewelryUI.h"
#include "BreakNumUI.h"
#include "Sound.h"
#include "SaveLoad.h"

class Block_Base;
class PileBanker;
class C_Player;
class CItemBase;

class Stage_Base
{
public:
	enum GAMEOVER_TYPE
	{
		GAMEOVER_DFAULT = 0,
		GAMEOVER_HIT_MAGMA,			// �}�O�}�ɓ���������
		GAMEOVER_HIT_SAND,			// ���ɓ���������
		GAMEOVER_CEILING_DESTROY,	//�V�䂪����
		GAMEOVER_JEWELY_DESTROY,	//��΂�����
		GAMEOVER_JEWELY_MELT,		//��΂��n����
		GAMEOVER_JEWELY_DOROP,		//��΂𗎂Ƃ�
		GAMEOVER_MAX,
	};

public:
	static const FloatPos CenterPos;

	Stage_Base();
	virtual ~Stage_Base();
	virtual void Update();
	virtual void Draw();
	void UIDraw();

	//�p�������u���b�N�̒��ŌĂт��������֐�
	IntPos GetStageWidthNum();
	void BlockUpdate();
	void BlockDraw();
	Block_Base* GetBlockInfo(int X, int Y);				//�����ɓ��ꂽ���l�̏ꏊ�ɂ���u���b�N�̏���Ԃ�
	PileBanker* GetPileBanker();
	PileBanker* GetSideBanker();
	CItemBase* GetJewely(int X, int Y);					//�W���G���[���ĂԊ֐�
	CItemBase* GetHeet(int X, int Y);					//�q�[�g���ĂԊ֐�
	void DestroyBlock(int X, int Y);					//�����ɂ���u���b�N������
	void CreateBlock(int X, int Y, Block_Base* pBlock);	//�u���b�N��������
	FloatPos Get_DrawPos(int X, int Y);					//���ꂽ�z��̔ԍ��̍��W(float)��Ԃ�
	IntPos Get_MapPos(float X, float Y);				//���ꂽ���W�̔z��̔ԍ�(int)��Ԃ�
	void MoveBlock(int X,int Y);						//�u���b�N���ړ�������
	void ChangeBlock(Block_Base* NewBlock);				//���Ԃ�̃|�W�V�����ɐV�����u���b�N�֒u��������
	FloatPos GetBasePos();
	void Refuge_Block();								//������z��̊O�֔�����
	void TakeTurn_Block(int X,int Y);					//�����Ƃ��̏ꏊ�ɂ���u���b�N����������


	//�v���C���[�֌W
	void PlayerUpdate();
	void PlayerDraw();
	void CreatePlayer();
	void DeletePlaer();
	C_Player* GetPlayer();

	//�p�C���o���J�[
	void NvigateUpdate();
	void NvigateDraw();
	void CreateMainBanker(int LineNum, FloatPos InstancePos,bool Heet);		//�c�Y�����
	void CreateSideBanker();		//���Y�����
	void DestroyMainBanker();		//�c�Y����
	void DestroySideBanker();		//���Y����
	void SetCantTypeIn_Side();		//�T�C�h�o���J�[��ł����߂Ȃ��悤�ɂ���
	
	//��Ί֌W
	void JewelyUpdate();
	void CreateJewely(int X,int Y);
	void DestroyJewely(int X, int Y);
	void MoveJewely(int X, int Y);
	void Refuge_Item();

	//�q�[�g�A�C�e���֌W
	void HeetUpdate();
	void CreateHeet(int X,int Y);
	void DestroyHeet(int X,int Y);
	void MoveHeet(int X,int Y);

	//�A�C�e�����L
	void ItemDraw();

	//�Q�[��CPP�ȂǂŌĂт���
	void Mina_Jewely();
	void Set_GameClear();
	bool Get_GameClear();
	void Set_GameOver(GAMEOVER_TYPE Type = GAMEOVER_TYPE::GAMEOVER_DFAULT);
	bool Get_GameOver();
	GAMEOVER_TYPE Get_GameOverType();
	void CreateStage(int X_Width, int Y_Height,const char* FileName);	//�X�e�[�W�����
	void CreateStage(int X_Width, int Y_Height, const int* BlockInfo, const int* JewelyInfo, const int* HeetInfo);
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
	void StageDraw();
	FloatPos GetStageLength() { return m_StageLength; }
	CModelManager* Get_ModelManager_Address();
	

	BreakNumUI* GetBreakNum(int Num);       // �u���b�N�����󂵂������擾
	BreakNumUI* GetBreakInfo();

	//�Z�[�u�֌W
	SaveData* GetSaveData();
	void SetSaveData(SaveData* SaveData);

protected:
	IntPos m_Stage_Width;
	PileBanker* m_pNavigate;				//�c�ł��p�p�C���o���J�[
	PileBanker* m_pSideBanker;				//���ł��p�p�C���o���J�[
	C_Player *m_pPlayer;					//�v���C���[
	Block_Base** m_mapInfo_Block;			//�u���b�N�̔z��p
	CItemBase** m_mapInfo_Jewely;				//�A�C�e���̔z��
	CItemBase** m_mapInfo_Heet;
	CModelManager *m_pModelManager;			//���f���}�l�[�W���[
	C_CameraManager *m_pCameraManager;		//�J�����}�l�[�W���[
	FloatPos m_BasePos;						//����̃|�W�V����
	FloatPos m_StageLength;

private:
	int m_JewelyCount;	//��΂̃J�E���g
	bool m_GameClear;	//�Q�[���N���A�ɂ���
	bool m_GameOver;	//�Q�[���I�[�o�[�ɂ���
	GAMEOVER_TYPE m_GameOverType;

	//�u���b�N�̓����Ɋւ���
	Block_Base *m_VirtualBlock;				//���G�ȃu���b�N
	bool m_exeMoveBlock;					//�u���b�N�𓮂����Ƃ��̃g���K�[
	bool m_exeChangeBlock;					//�����̃u���b�N��ς��鎞�̃g���K�[
	bool m_exeRefugeBlock;					//�z���ł͏������A�b�v�f�[�g�����������ɂ���g���K�[
	bool m_exeTakeTurnsBlock;				//�u���b�N����������Ƃ��Ɏg��
	Block_Base* Temporary_Block;			//�ꎞ���Ă����|�C���^�[
	IntPos temporary_BlockPos;				//�ꎞ���Ă����ꏊ�u���b�N
	int m_BreakNum;                         // �j�󂵂��u���b�N���i�[����ϐ�
	std::vector<Block_Base*> m_RefugeBlock;	//�r�񂩂�O�ɏo���Ƃ��p�̕ϐ���u���ꏊ

	//�A�C�e���̓����Ɋւ���
	bool m_exeMoveItem;
	bool m_exeRefugeItem;
	IntPos m_Temporary_ItemPos;				//�A�C�e���̈ꎞ���Ă����|�W�V����
	std::vector<CItemBase*> m_RefugeItem;

	//�p�C���o���J�[�֌W
	bool m_CanTypeIn_Side;

	// UI�֌W
	GameUI* m_pUI;
	JewelryUI* m_pJewelryUI;
	BreakNumUI* m_pBreakUI;

	SE* m_pClearSE;
	SE* m_pOverSE;

	SaveData *m_pNowSaveFile;
};

#endif // !STAGE_BASE_H

