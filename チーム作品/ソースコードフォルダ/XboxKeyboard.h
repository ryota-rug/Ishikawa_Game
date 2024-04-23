#pragma once
#ifndef __XBOXKEYBOARD_H__
#define __XBOXKEYBOARD_H__

#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include <iostream>
#include<DirectXMath.h>
#include "string.h"

#define TRIGGER (state.Gamepad.wButtons & oldstate.Gamepad.wButtons ^ state.Gamepad.wButtons)
#define RELEASE (state.Gamepad.wButtons & oldstate.Gamepad.wButtons ^ oldstate.Gamepad.wButtons)

using namespace std;

enum Key
{
	A_BUTTON,                   //A�{�^��
	B_BUTTON,                   //B�{�^��
	X_BUTTON,                   //X�{�^��
	Y_BUTTON,                   //Y�{�^��
	START_BUTTON,               //START�{�^��
	BACK_BUTTON,                //BACK�{�^��
	LEFT_SHOULDER,				//�����ɂ��Ă����̃{�^��(LB)
	RIGHT_SHOULDER,				//�E���ɂ��Ă����̃{�^��(RB)
	UP_BUTTON,                  //��{�^��
	DOWN_BUTTON,                //���{�^��
	LEFT_BUTTON,                //���{�^��
	RIGHT_BUTTON,               //�E�{�^��
	LEFT_TRIGGER,		        //���g���K�[(LT)
	RIGHT_TRIGGER,			    //�E�g���K�[(RT)
	LEFT_STICK,			        //���X�e�B�b�N
	RIGHT_STICK				    //�E�X�e�B�b�N
};


void UpdateGamePad();                                //Xbox�R���g���[���[�̏����擾����֐�(Update�̏��߂̕��ɏ����܂��傤) 
int InputPressKey(Key key);                          //�v���X�L�[�̓��͊֐�
int InputTriggerKey(Key key);                        //�g���K�[�L�[�̓��͊֐�
int InputReleaseKey(Key key);                        //�����[�X�L�[�̓��͊֐�
DirectX::XMFLOAT2 GetPressStick();                   //�v���X����Ă���X�e�B�b�N�̒l��Ԃ��֐�(DirectX::Float2�^�ł��A�Ԃ����l�ɕ⊮�������l���|���܂��傤)
float GetPressTrigger();                             //�v���X����Ă���g���K�[�̒l��Ԃ�
DirectX::XMFLOAT2 GetTriggerStick();                 //�g���K�[��Ԃ̃X�e�B�b�N�̒l��Ԃ�(�댯!�o���邾��GetPressStick()�ő�p���܂��傤)              
float GetTriggerTrigger();                           //�g���K�[��Ԃ̃g���K�[�̒l��Ԃ�
int AllKeyTrigger();                                 //�S�Ẵg���K�[���͊֐�
int AlfaKeyTrigger();                                //ABXY�݂̂ɑΉ������g���K�[����
int AlfaKeyPress();                                  //ABXY�݂̂ɑΉ������v���X����
WORD StickChangeButton(SHORT StickX, SHORT StickY, SHORT DeadZone);    //�X�e�B�b�N���͂��L�[���͂ɕϊ�                   
WORD TriggerChangeButton(BYTE Trigger, BYTE DeadZone);                 //�g���K�[�̓��͂��L�[���͂ɕϊ�
WORD TriggerChangeButtonReleaseVer(BYTE Trigger, BYTE DeadZone);        //�g���K�[�L�[�̓��͂��L�[���͂ɕϊ�(ReleaseVer)

void SetPowerVibration(WORD Left, WORD RIGHT);            //�o�C�u���[�V�����̋����ݒ�
void SetVibration(int num);                               //�o�C�u���[�V�����N��(�t���[���w��ł���p)
void MoveVibration();                                     //�o�C�u���[�V�������N��(����)
void StopVibration();                                     //�o�C�u���[�V�����������I��


#endif
