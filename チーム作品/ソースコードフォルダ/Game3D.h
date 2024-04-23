#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include "Model.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "SpriteManager.h"

enum SCENE
{
	SCENE_TITLE,	//タイトルシーン
	SCENE_SELECT,	//セレクトシーン
	SCENE_GAME,		//ゲームシーン
					  
	SCENE_STAGE1_1,	//ステージ1-1
	SCENE_STAGE1_2,	//ステージ1-2
	SCENE_STAGE1_3,	//ステージ1-3
	SCENE_STAGE1_4,	//ステージ1-4
	SCENE_STAGE1_5,	//ステージ1-5
	SCENE_STAGE2_1,	//ステージ2-1
	SCENE_STAGE2_2,	//ステージ2-2
	SCENE_STAGE2_3,	//ステージ2-3
	SCENE_STAGE2_4,	//ステージ2-4
	SCENE_STAGE2_5,	//ステージ2-5
	SCENE_STAGE3_1,	//ステージ3-1
	SCENE_STAGE3_2,	//ステージ3-2
	SCENE_STAGE3_3,	//ステージ3-3
	SCENE_STAGE3_4,	//ステージ3-4
	SCENE_STAGE3_5,	//ステージ3-5
					  
	SCENE_END,		//ゲームを終わる
};

class Game3D
{
public:
	Game3D();
	~Game3D();
	void Update();
	void Draw();

private:
};


//シーン変更
//	SCENE NextScene : 次に読み込みたいシーン
void SceneChange(SCENE NextScene);	


SCENE _GetNowScene();		// 現在のシーンをゲット
SCENE _GetBeforeScene();	// 1つ前のシーン


#endif // __GAME_3D_H__