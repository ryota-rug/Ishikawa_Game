#pragma once
#include "ObjectRenderer.h"
#include "ModelManager_Class.h"

class Area1BackObject : public ObjectRenderer
{
public:
	Area1BackObject(CModelManager* pmodelmanger);
	~Area1BackObject() override;
	void ObjectUpdate() override;
	void ObjectDraw() override;

};