#pragma once
#include "ObjectRenderer.h"
#include "ModelManager_Class.h"

class Area3BackObject : public ObjectRenderer
{
public:
	Area3BackObject(CModelManager* pmodelmanger);
	~Area3BackObject() override;
	void ObjectUpdate() override;
	void ObjectDraw() override;

};