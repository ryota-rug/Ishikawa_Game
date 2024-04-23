// Boxオブジェクト [box.cpp]
#include "box.h"
#include "shader.h"
#include "modelRenderer.h"
#include "shadow.h"

void Box::Init()
{
	AddComponent<Shader>()->Load("shader/vertexLightingVS.cso",
		"shader/vertexLightingPS.cso");
	AddComponent<ModelRenderer>()->Load("asset/model/box.obj");
	AddComponent<Shadow>()->SetSize(1.0f);
}
