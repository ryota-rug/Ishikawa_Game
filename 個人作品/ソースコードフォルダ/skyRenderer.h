// �X�J�C�h�[���`��R���|�[�l���g [skyRenderer.h]
#pragma once
#include "modelRenderer.h"

class SkyRenderer : public ModelRenderer
{
public:
	using ModelRenderer::ModelRenderer;

	void Draw() override;
};
