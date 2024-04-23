#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include "Model.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "SpriteManager.h"

enum SCENE
{
	SCENE_TITLE,	//�^�C�g���V�[��
	SCENE_SELECT,	//�Z���N�g�V�[��
	SCENE_GAME,		//�Q�[���V�[��
					  
	SCENE_STAGE1_1,	//�X�e�[�W1-1
	SCENE_STAGE1_2,	//�X�e�[�W1-2
	SCENE_STAGE1_3,	//�X�e�[�W1-3
	SCENE_STAGE1_4,	//�X�e�[�W1-4
	SCENE_STAGE1_5,	//�X�e�[�W1-5
	SCENE_STAGE2_1,	//�X�e�[�W2-1
	SCENE_STAGE2_2,	//�X�e�[�W2-2
	SCENE_STAGE2_3,	//�X�e�[�W2-3
	SCENE_STAGE2_4,	//�X�e�[�W2-4
	SCENE_STAGE2_5,	//�X�e�[�W2-5
	SCENE_STAGE3_1,	//�X�e�[�W3-1
	SCENE_STAGE3_2,	//�X�e�[�W3-2
	SCENE_STAGE3_3,	//�X�e�[�W3-3
	SCENE_STAGE3_4,	//�X�e�[�W3-4
	SCENE_STAGE3_5,	//�X�e�[�W3-5
					  
	SCENE_END,		//�Q�[�����I���
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


//�V�[���ύX
//	SCENE NextScene : ���ɓǂݍ��݂����V�[��
void SceneChange(SCENE NextScene);	


SCENE _GetNowScene();		// ���݂̃V�[�����Q�b�g
SCENE _GetBeforeScene();	// 1�O�̃V�[��


#endif // __GAME_3D_H__