//#pragma once
#ifndef CLEAR_SCREEN_H
#define CLEAR_SCREEN_H
#include <DirectXMath.h>
#include "UI_PauseText.h"
#include "UI_ClearScore.h"
#include "Image2D.h"

class UI_ClearScreen
{
public:
	enum UI_Clear
	{
		STAGECLEAR = 0,
		NEXT,
		RETRY,
		STAGESELECT,
		MAX
	};
public:
	enum STATE_CLEAR
	{
		STATE_INIT = 0,
		STATE_IN,
		STATE_STAY,
		STATE_OUT,
		STATE_END,
		STATE_MAX
	};

public:
	UI_ClearScreen();
	~UI_ClearScreen();
	void ScreenInit();
	bool Update();
	void ScreenDraw();
	void StageClearDraw();
	void HakaiScoreDraw(int Score);
	void UtitukeScoreDraw(int Score);
	void RetryDraw(bool Select);
	void NextDraw(bool Select);
	void StageSelectDraw(bool Select);
	STATE_CLEAR GetState();
	void SetState(STATE_CLEAR NextState);
	
private:

	typedef struct
	{
		DirectX::XMFLOAT2 m_pos;			//���W
		DirectX::XMFLOAT2 m_size;			//�傫��
		DirectX::XMFLOAT3 m_Scale;	        // �傫��
		DirectX::XMFLOAT3 m_Angle;	        // �p�x

	}UItransform;

private:

	SpriteManager* m_pSprite;
	UItransform m_ScreenTransform;
	ID3D11ShaderResourceView* m_pScreenTexture;
	UItransform m_Transform[UI_Clear::MAX];
	ID3D11ShaderResourceView* m_pTexture[UI_Clear::MAX];    // �e�N�X�`��
	ID3D11ShaderResourceView* m_pChoseTexture[UI_Clear::MAX];    // �e�N�X�`��
	ID3D11ShaderResourceView* m_pDestroyNum_Mozi;    // �e�N�X�`��
	ID3D11ShaderResourceView* m_pNockNum_Mozi;    // �e�N�X�`��

	STATE_CLEAR m_NowState;
	UI_ClearScore* m_pScore;
	Image2D* m_pArm;
	DirectX::XMFLOAT2 m_ArmAddPos;
};

#endif


