//#pragma once
#ifndef CAMERA_STARTEVENT_H
#define CAMERA_STARTEVENT_H

#include "CameraBase.h"
#include "GameStartEvent.h"
#include "StartEvent_Player.h"

class Camera_StartEvent : public CameraBase
{
public:
	Camera_StartEvent(Game_StartEvent* pStartEvent);
	~Camera_StartEvent();
	void Update();

private:
	Game_StartEvent* m_pStartEvent;
	StartEvent_Player* m_pPlayer;

};



#endif // !CAMERA_STARTEVENT_H
