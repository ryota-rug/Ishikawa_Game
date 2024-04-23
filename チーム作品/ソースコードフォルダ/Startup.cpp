#include "Main.h"
#include "WinUtil.h"
#include "Timer.h"

#include <crtdbg.h>
#include <time.h>


//--- �萔��`
const char* APP_TITLE = "���{�m�b�N";	//�E�B���h�E�̖��O
const Frame DEFAULT_FPS = 60;	//fps�̐ݒ�


/*
* �G���g���|�C���g
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((UINT)time(NULL));

	//�E�B���h�E������
	if (FAILED(InitWindow(APP_TITLE, GetAppWidth(), GetAppHeight())))
	{
		Error("window initialize faield");
	}

	//�^�C�}�[�̏�����
	InitTimer(DEFAULT_FPS);

	//���̑�������
	Init();


	//--- �E�B���h�E�̊Ǘ�
	AppState state = APP_STATE_MESSAGE;
	while (state != APP_STATE_QUIT)
	{
		state = UpdateWindow();
		if (state == APP_STATE_WAIT && UpdateTimer())
		{
			Update(GetDeltaTime());
			Draw();
		}
	}

	// �I����
	Uninit();
	UninitTimer();
	UninitWindow();

	_CrtDumpMemoryLeaks();	//���[�N�`�F�b�N
	return 0;
}
