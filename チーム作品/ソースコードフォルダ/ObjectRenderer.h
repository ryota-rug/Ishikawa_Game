#pragma once
#include "ModelManager_Class.h"
#include <string>
#include <DirectX.h>
#include "StageBase.h"

class ObjectRenderer
{
public:
	ObjectRenderer(CModelManager* pmodelmanger);
	virtual ~ObjectRenderer();
	void Update();
	virtual void ObjectUpdate() {};
	void Draw();
	virtual void ObjectDraw() {};
	void SetModel(std::string modelName);
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetSize(DirectX::XMFLOAT3 size);
	void SetRotate(DirectX::XMFLOAT3 rotate);
	void SetModelManger(CModelManager* pmodelManager);
	void SetStage(Stage_Base* pStage);

protected:
	std::string m_ModelName;
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_size;
	DirectX::XMFLOAT3 m_rotate;
	CModelManager* m_pModelManager;
	Stage_Base* m_pStage;

};