#pragma once
#include <unordered_map>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include "renderer.h"
#include "CreateTexture.h"

static std::unordered_map<std::string, aiScene*> Model_map;
static std::unordered_map<std::string, aiScene*> Anim_map;
static std::unordered_map<std::string, std::unordered_map<std::string, ID3D11ShaderResourceView*>> Texture_map;

class ModelInfo
{
private:
	aiScene* ImportFile(const char* pFile, unsigned int pFlags);
public:
	~ModelInfo();
	void LoadModelInfo(const char *FileName, const std::string Name);
	void LoadAnimInfo(const char *FileName, const std::string Name);
};

