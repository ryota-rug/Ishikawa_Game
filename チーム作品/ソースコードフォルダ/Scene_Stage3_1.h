//#pragma once
#ifndef STAGE_3_1_H
#define STAGE_3_1_H

#include "Scene_StageBase.h"
#include "Scene.h"
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

class CStage3_1 : public Scene_StageBase
{
public:
	CStage3_1();
	~CStage3_1();
};

#endif