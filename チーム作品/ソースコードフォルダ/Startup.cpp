#include "Main.h"
#include "WinUtil.h"
#include "Timer.h"

#include <crtdbg.h>
#include <time.h>


//--- 定数定義
const char* APP_TITLE = "ロボノック";	//ウィンドウの名前
const Frame DEFAULT_FPS = 60;	//fpsの設定


/*
* エントリポイント
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((UINT)time(NULL));

	//ウィンドウ初期化
	if (FAILED(InitWindow(APP_TITLE, GetAppWidth(), GetAppHeight())))
	{
		Error("window initialize faield");
	}

	//タイマーの初期化
	InitTimer(DEFAULT_FPS);

	//その他初期化
	Init();


	//--- ウィンドウの管理
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

	// 終了時
	Uninit();
	UninitTimer();
	UninitWindow();

	_CrtDumpMemoryLeaks();	//リークチェック
	return 0;
}
