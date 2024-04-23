//#pragma once
#ifndef STAGE_1_5_H
#define STAGE_1_5_H
#include "Scene_StageBase.h"
#include "StageBase.h"
#include "ModelManager_Class.h"
#include "Sound.h"

#include "GameClearEvent.h"
#include "GameStartEvent.h"
#include "GameOverEvent.h"
#include "GamePause.h"
#include "GameOver.h"
#include "GameClear.h"

#include "Image2D.h"

#include "KnockUI.h"
#include "BreakNumUI.h"
#include "UI_OverPeople.h"
#include "UI_Tutorial.h"

class CStage1_5 : public Scene_StageBase
{
public:
	CStage1_5();
	~CStage1_5();
};

#endif