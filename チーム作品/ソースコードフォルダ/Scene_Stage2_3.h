//#pragma once
#ifndef STAGE_2_3_H
#define STAGE_2_3_H
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

class CStage2_3 : public Scene_StageBase
{
public:
	CStage2_3();
	~CStage2_3();
};


#endif