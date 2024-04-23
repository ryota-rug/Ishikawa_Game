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
	A_BUTTON,                   //Aボタン
	B_BUTTON,                   //Bボタン
	X_BUTTON,                   //Xボタン
	Y_BUTTON,                   //Yボタン
	START_BUTTON,               //STARTボタン
	BACK_BUTTON,                //BACKボタン
	LEFT_SHOULDER,				//左後ろについている上のボタン(LB)
	RIGHT_SHOULDER,				//右後ろについている上のボタン(RB)
	UP_BUTTON,                  //上ボタン
	DOWN_BUTTON,                //下ボタン
	LEFT_BUTTON,                //左ボタン
	RIGHT_BUTTON,               //右ボタン
	LEFT_TRIGGER,		        //左トリガー(LT)
	RIGHT_TRIGGER,			    //右トリガー(RT)
	LEFT_STICK,			        //左スティック
	RIGHT_STICK				    //右スティック
};


void UpdateGamePad();                                //Xboxコントローラーの情報を取得する関数(Updateの初めの方に書きましょう) 
int InputPressKey(Key key);                          //プレスキーの入力関数
int InputTriggerKey(Key key);                        //トリガーキーの入力関数
int InputReleaseKey(Key key);                        //リリースキーの入力関数
DirectX::XMFLOAT2 GetPressStick();                   //プレスされているスティックの値を返す関数(DirectX::Float2型です、返した値に補完したい値を掛けましょう)
float GetPressTrigger();                             //プレスされているトリガーの値を返す
DirectX::XMFLOAT2 GetTriggerStick();                 //トリガー状態のスティックの値を返す(危険!出来るだけGetPressStick()で代用しましょう)              
float GetTriggerTrigger();                           //トリガー状態のトリガーの値を返す
int AllKeyTrigger();                                 //全てのトリガー入力関数
int AlfaKeyTrigger();                                //ABXYのみに対応したトリガー入力
int AlfaKeyPress();                                  //ABXYのみに対応したプレス入力
WORD StickChangeButton(SHORT StickX, SHORT StickY, SHORT DeadZone);    //スティック入力をキー入力に変換                   
WORD TriggerChangeButton(BYTE Trigger, BYTE DeadZone);                 //トリガーの入力をキー入力に変換
WORD TriggerChangeButtonReleaseVer(BYTE Trigger, BYTE DeadZone);        //トリガーキーの入力をキー入力に変換(ReleaseVer)

void SetPowerVibration(WORD Left, WORD RIGHT);            //バイブレーションの強さ設定
void SetVibration(int num);                               //バイブレーション起動(フレーム指定できる用)
void MoveVibration();                                     //バイブレーションを起動(無限)
void StopVibration();                                     //バイブレーションを強制終了


#endif
