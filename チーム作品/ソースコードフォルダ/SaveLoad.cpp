#include "SaveLoad.h"

#define StageNum (16)

using namespace std;

SaveData StageSave[StageNum];
SaveFile Savefile[StageNum];

//string fileName = "Assets/SaveData.csv";

//====================================================================
//�p�r�@�F�t�@�C���̓ǂݍ���(���[�h)
//�߂�l�F�Ȃ�
//�g�����F�t�@�C���̓ǂݍ��ݗp�Ȃ̂ŃQ�[�����ł͍ŏ������Ăяo���܂�
//���ӓ_�F��{�I�ɌĂяo���͈̂��݂̂ɂ��Ă�������(����{�I�Ɏg��Ȃ��ł�������)
//=====================================================================
void FileLoad()
{
	ifstream ifs("Assets/SaveData.csv");        //ifstream�^�̓t�@�C���ǂݍ��݂��s���^


	// �ǂݍ���
	vector<string> lines;	// �f�[�^�i�[�p
	string line;	        // �ꎞ�f�[�^�ێ��p
	// �s���o��
	while (getline(ifs, line))  //���̈���(������)���E�̈����Ɋi�[
	{
		lines.push_back(line);  //�ǂݍ��񂾃t�@�C���̒��̕�������i�[���Ă���line�ϐ���vector�^��lines�ϐ��Ɋi�[
	}
	//����o��
	SaveFile temp;
	string str;
	char delimiter = ',';  //��؂蕶��(�R���})


	for (int i = 0; i < (int)lines.size(); i++)
	{
		string check = lines[i];                //vector�^��lines�ϐ��̒���1����check�֐��̒��Ɋi�[���Ċm�F����
		istringstream issSave(check);         //check�ϐ���istringstream�^�ɕϊ�����issSave�Ɋi�[(�u,�v��؂�œǂݍ��߂�悤�ɂȂ�)
		//���߂ẴX�e�[�W���ۂ�
		getline(issSave, str, delimiter);     //stringstream�^�̓��͕�������R���}�ŕ�����str�ϐ��Ɋi�[
		temp.AgainStage = stoi(str);                   //�����񂩂琔�l�ւ̕ϊ�
		if (temp.AgainStage == 0) StageSave[i].AgainStage = false;
		else StageSave[i].AgainStage = true;
		//�N���A���Ă���X�e�[�W���ۂ�
		getline(issSave, str, delimiter);
		temp.ClearStage = stoi(str);
		if (temp.ClearStage == 0) StageSave[i].ClearStage = false;
		else StageSave[i].ClearStage = true;
		//�ŏ��ł��t����(�x�X�g)
		getline(issSave, str, delimiter);
		temp.MinHitnum = stoi(str);
		StageSave[i].MinHitnum = temp.MinHitnum;
		//�Y�̑��ł��t����
		getline(issSave, str, delimiter);
		temp.AllHitnum = stoi(str);
		StageSave[i].AllHitnum = temp.AllHitnum;
		//�u���b�N�̑��j��
		getline(issSave, str, delimiter);
		temp.AllBlocknum = stoi(str);
		StageSave[i].AllBlocknum = temp.AllBlocknum;

		//�i�[
		//m_StageSave.push_back(temp);        //�A�C�e���p��vector�ϐ��̒��Ɋi�[
		//��Еt��
		issSave.clear(stringstream::goodbit);  //clear()�̓������̒������ׂď����A�������L���p�V�e�B��0�ɂȂ�Ȃ�(stringstream::goodbit��0�ɂ��Ă�?)

	}

	ifs.close();     //�t�@�C�������
}

//====================================================================
//�p�r�@�F�t�@�C���̏�������(�Z�[�u)
//�߂�l�F�Ȃ�
//�g�����F�t�@�C���̏������ݗp�Ȃ̂ŃQ�[�����ł͍Ōゾ���Ăяo���܂�
//���ӓ_�F��{�I�ɌĂяo���͈̂��݂̂ɂ��Ă�������(����{�I�Ɏg��Ȃ��ł�������)
//=====================================================================
void FileSave()
{
	char delimiter = ',';  //��؂蕶��(�R���})

	for (int i = 0; i < StageNum; i++)
	{
		if (StageSave[i].AgainStage == false) Savefile[i].AgainStage = 0;
		else Savefile[i].AgainStage = 1;
		if (StageSave[i].ClearStage == false) Savefile[i].ClearStage = 0;
		else Savefile[i].ClearStage = 1;
		Savefile[i].MinHitnum = StageSave[i].MinHitnum;
		Savefile[i].AllHitnum = StageSave[i].AllHitnum;
		Savefile[i].AllBlocknum = StageSave[i].AllBlocknum;
	}

	ofstream ofs("Assets/SaveData.csv");

	for (int i = 0; i < StageNum; i++)
	{
		ofs << Savefile[i].AgainStage << delimiter;
		ofs << Savefile[i].ClearStage << delimiter;
		ofs << Savefile[i].MinHitnum << delimiter;
		ofs << Savefile[i].AllHitnum << delimiter;
		ofs << Savefile[i].AllBlocknum << delimiter;
		ofs << endl;
	}

	ofs.close();    //�t�@�C�������
}

//====================================================================
//�p�r�@�F�X�e�[�W���w�肵�ė~�����X�e�[�W�̃Z�[�u���𓾂�
//�߂�l�FSaveData�^
//�g�����F�����ɃZ�[�u�f�[�^�̗~�����X�e�[�W���w�肵�ĕԂ�
//���ӓ_�F�Ȃ�
//=====================================================================
SaveData GetLoadStage(SaveElea stage)
{
	if (stage < 0 || stage >= StageNum)    //�z��O�A�N�Z�X����
	{//��O����
		SaveData error = {
			-1, -1, -1, -1
		};
		return error;              //�z��O�A�N�Z�X�̏ꍇ��erorr�̒l��Ԃ�
	}

	return StageSave[stage];         //�w�肳�ꂽ�ԍ��Ɋi�[����Ă���A�C�e������Ԃ�
}

//====================================================================
//�p�r�@�F�Z�[�u�����������Q�[�����ŕێ����Ă���Z�[�u�\���̂ɕۑ�(�Z�[�u)
//�߂�l�F�Ȃ�
//�g�����F������(�K�ꂽ���Ƃ����邩�A�N���A�������Ƃ����邩�A
//�@�@�@�@����ł��t�������A���u���b�N��j�󂵂���)���w��
//���ӓ_�F�Q�[�����Ŏg���Z�[�u�͂�����g���Ă�������
//=====================================================================
void SetSave(SaveElea stage, bool again, bool clear, int hit, int bloak)
{
	StageSave[stage].AgainStage = again;
	StageSave[stage].ClearStage = clear;
	if (StageSave[stage].MinHitnum > hit)
		StageSave[stage].MinHitnum = hit;
	StageSave[stage].AllHitnum += hit;
	StageSave[stage].AllBlocknum += bloak;
}

void SetAgain(SaveElea stage, bool again)
{
	StageSave[stage].AgainStage = again;
}

//====================================================================
//�p�r�@�F�Q�[�����̃Z�[�u�f�[�^�����Z�b�g
//�߂�l�F�Ȃ�
//�g�����F�V�����l���Q�[�����n�߂鎞�Ɏg���Ă�������(�t�@�C���ɃZ�[�u���[�h����Ӗ����Ă���?)
//���ӓ_�F�Ȃ�
//=====================================================================
void ResetData()
{
	for (int i = 0; i < StageNum; i++)
	{
		StageSave[i].AgainStage = false;
		StageSave[i].ClearStage = false;
		StageSave[i].MinHitnum = 999;
		StageSave[i].AllHitnum = 0;
		StageSave[i].AllBlocknum = 0;
	}
}

void CheatData()
{
	for (int i = 0; i < StageNum; i++)
	{
		StageSave[i].AgainStage = true;
		StageSave[i].ClearStage = true;
		StageSave[i].MinHitnum = 1;
		StageSave[i].AllHitnum = 999;
		StageSave[i].AllBlocknum = 999;
	}
}