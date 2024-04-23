#ifndef __INPUT_H__
#define __INPUT_H__

#include <Windows.h>

HRESULT InitInput();
void UninitInput();
void UpdateInput();

bool IsKeyPress(BYTE key);
bool IsKeyAnyTrigger();	//�Ȃ�̃L�[�������Ă��������܂�
bool IsKeyTrigger(BYTE key);
bool IsKeyRelease(BYTE key);
bool IsKeyRepeat(BYTE key);

int GetMousePosX();
int GetMousePosY();

#endif // __INPUT_H__