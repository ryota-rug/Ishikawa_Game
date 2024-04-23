// Goal�I�u�W�F�N�g [goal.cpp]
#include "goal.h"
#include "shader.h"
#include "modelRenderer.h"
#include "shadow.h"

void Goal::Init()
{
	AddComponent<Shader>()->Load("shader/vertexLightingVS.cso",
		"shader/vertexLightingPS.cso");
	AddComponent<ModelRenderer>()->Load("asset/model/goal.obj");
	AddComponent<Shadow>()->SetSize(1.5f);
}
