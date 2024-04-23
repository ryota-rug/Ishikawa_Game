#pragma once
#include "ObjectRenderer.h"
#include "ModelManager_Class.h"

class Area2BackObject : public ObjectRenderer
{
public:
	Area2BackObject(CModelManager* pmodelmanger);
	~Area2BackObject() override;
	void ObjectUpdate() override;
	void ObjectDraw() override;

};