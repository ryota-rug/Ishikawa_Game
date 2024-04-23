
#pragma once
#ifndef __SAVELOAD_H__
#define __SAVELOAD_H__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

enum SaveElea
{
	Stage11,
	Stage12,
	Stage13,
	Stage14,
	Stage15,
	Stage21,
	Stage22,
	Stage23,
	Stage24,
	Stage25,
	Stage31,
	Stage32,
	Stage33,
	Stage34,
	Stage35,

};

//�Q�[�����ň����Z�[�u�f�[�^(��������Ƃ��͊�{�I�ɂ��̍\���̂������Ă�������)
//�Q�[�����ɃZ�[�u�f�[�^��ێ����Ă���\����
struct SaveData
{
	bool AgainStage;      //�K�ꂽ���Ƃ�����X�e�[�W(true:1 false:0)
	bool ClearStage;      //�N���A�����X�e�[�W(true:1 false:0)
	int MinHitnum;        //�Y�̍ŏ��ł��t����(�x�X�g)
	int AllHitnum;        //�Y�̑��ł��t����
	int AllBlocknum;      //�u���b�N�̑��j��
};

//�t�@�C���A�N�Z�X�p�̍\����(�t�@�C���̓ǂݍ��ݏ������ݗp�Ȃ̂ň���Ȃ��ł�������)
//�Q�[�����ň����Z�[�u�f�[�^�ɕϊ����邽�߂̍\����
struct SaveFile
{
	int AgainStage;      //�K�ꂽ���Ƃ�����X�e�[�W(true:1 false:0)
	int ClearStage;      //�N���A�����X�e�[�W(true:1 false:0)
	int MinHitnum;       //�Y�̍ŏ��ł��t����(�x�X�g)
	int AllHitnum;       //�Y�̑��ł��t����
	int AllBlocknum;     //�u���b�N�̑��j��
};


void FileLoad();            //�t�@�C���̓ǂݍ���&�Q�[�����Z�[�u���Ɋi�[(���[�h)(�Q�[���J�n���̂݁H)
void FileSave();            //�t�@�C���ɏ�������(�Z�[�u)(�Q�[���I�����̂݁H)
SaveData GetLoadStage(SaveElea stage);		//�w�肳�ꂽ�ԍ��̃X�e�[�W�����擾
void SetSave(SaveElea stage, bool again, bool clear, int hit, int bloak);   //�Q�[�����Z�[�u���Ɋi�[
void SetAgain(SaveElea stage, bool again);	//���ꂵ������񂾂��ۑ�����
void ResetData();                           //�Q�[�����̃Z�[�u�f�[�^�����Z�b�g
void CheatData();	//�S�X�e�[�W���


#endif

