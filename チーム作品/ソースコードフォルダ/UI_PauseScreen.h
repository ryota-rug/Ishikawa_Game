//#pragma once

#ifndef SCREEN_H
#define SCREEN_H
#include <DirectXMath.h>
#include "UI_PauseText.h"
#include "Image2D.h"

class UI_PauseScreen
{
private:
	enum UI_Pause
	{
		PAUSE = 0,
		RETRY,
		STAGESELECT,
		END,
		MAX
	};
public:
	enum STATE_PAUSE
	{
		STATE_INIT = 0,
		STATE_IN,
		STATE_STAY,
		STATE_OUT,
		STATE_END,
		STATE_MAX
	};

public:
	UI_PauseScreen();
	~UI_PauseScreen();
	bool Update();
	void ScreenInit();
	void ScreenDraw();
	void PauseDraw();
	void RetryDraw(bool Select);
	void StageSelectDraw(bool Select);
	void EndDraw(bool Select);
	STATE_PAUSE GetState();
	void SetState(STATE_PAUSE NextState);
	

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
	UItransform m_Transform[UI_Pause::MAX];
	ID3D11ShaderResourceView* m_pTexture[UI_Pause::MAX];    // �e�N�X�`��
	ID3D11ShaderResourceView* m_pChoseTexture[UI_Pause::MAX];    // �e�N�X�`��
	STATE_PAUSE m_NowState;
	Image2D* m_pArm;
	DirectX::XMFLOAT2 m_ArmAddPos;
};

#endif
