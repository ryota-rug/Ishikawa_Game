#ifndef ___LOAD_SCENE_H___
#define ___LOAD_SCENE_H___

#include "Image2D.h"


class CScene_Load
{
public:
	enum LOADSCENE_STATE
	{
		LOAD_NONE,		//��ʏ������ĂȂ�

		LOAD_BEFORE,	//���[�h�O��ʏ���
		LOAD_LOADING,	//���[�h����ʏ���
		LOAD_AFTER		//���[�h���ʏ���
	};

public:
	CScene_Load();
	~CScene_Load();
	void Update();
	void Draw();
	void Reset();

	CScene_Load::LOADSCENE_STATE GetLoadState();	//���[�h��ʂ̏�Ԃ��擾
	void LoadEnd();	//���[�h�I����ʒm����


private:
	SpriteManager* m_pSpriteManager;	//2D�`��p
	Image2D* m_pBack;				//�w�i�摜

	LOADSCENE_STATE m_loadState;	//���[�h��ʂ̏��
	bool m_loadEnd;					//���[�h�����I���t���O
};


#endif // !___LOAD_SCENE_H___
