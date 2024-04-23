#include "modelinfo.h"


aiScene * ModelInfo::ImportFile(const char * pFile, unsigned int pFlags)
{
	// default pp steps
	static unsigned int ppsteps =
		//aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
		aiProcess_JoinIdenticalVertices | // join identical vertices/ optimize indexing
		aiProcess_ValidateDataStructure | // perform a full validation of the loader's output
		aiProcess_ImproveCacheLocality | // improve the cache locality of the output vertices
		aiProcess_RemoveRedundantMaterials | // remove redundant materials
		aiProcess_FindDegenerates | // remove degenerated polygons from the import
		aiProcess_FindInvalidData | // detect invalid model data, such as invalid normal vectors
		aiProcess_GenUVCoords | // convert spherical, cylindrical, box and planar mapping to proper UVs
		aiProcess_TransformUVCoords | // preprocess UV transformations (scaling, translation ...)
		aiProcess_FindInstances | // search for instanced meshes and remove them by references to one master
		aiProcess_LimitBoneWeights | // limit bone weights to 4 per vertex
		aiProcess_OptimizeMeshes | // join small meshes, if possible;
		aiProcess_SplitByBoneCount | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
		0;

	aiScene* pScene;
	aiPropertyStore* props = aiCreatePropertyStore();
	aiSetImportPropertyInteger(props, AI_CONFIG_IMPORT_TER_MAKE_UVS, 1);
	aiSetImportPropertyFloat(props, AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80.0f);
	aiSetImportPropertyInteger(props, AI_CONFIG_PP_SBP_REMOVE, 0);

	aiSetImportPropertyInteger(props, AI_CONFIG_GLOB_MEASURE_TIME, 1);
	//aiSetImportPropertyInteger(props, AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);

	// Call ASSIMPs C-API to load the file
	pScene = (aiScene*)aiImportFileExWithProperties(pFile,
		pFlags |
		ppsteps | /* configurable pp steps */
		aiProcess_GenSmoothNormals | // generate smooth normal vectors if not existing
		aiProcess_SplitLargeMeshes | // split large, unrenderable meshes into submeshes
		aiProcess_Triangulate | // triangulate polygons with more than 3 edges
		aiProcess_SortByPType | // make 'clean' meshes which consist of a single typ of primitives
		0,
		nullptr,
		props);

	aiReleasePropertyStore(props);

	return pScene;
}

ModelInfo::~ModelInfo()
{
	for (auto pair = Texture_map.begin(); pair != Texture_map.end(); pair++)
	{
		for (auto it = (*pair).second.begin(); it != (*pair).second.end(); it++)
		{
			if ((*it).second)
				(*it).second->Release();
		}
	}

	for (std::pair<const std::string, const aiScene*> pair : Model_map)
	{
		aiReleaseImport(pair.second);
	}


	for (std::pair<const std::string, const aiScene*> pair : Anim_map)
	{
		aiReleaseImport(pair.second);
	}
}

void ModelInfo::LoadModelInfo(const char *FileName, const std::string Name)
{
	char szPath[_MAX_PATH], szDrive[_MAX_DRIVE], szDir[_MAX_DIR], szFName[_MAX_FNAME], szExt[_MAX_EXT];
	_splitpath_s(FileName, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szFName, _MAX_FNAME, szExt, _MAX_EXT);

	const std::string modelPath(FileName);

	//もうその中に実体がある場合
	auto it = Model_map.find(Name);

	//見つかった場合
	if (it != Model_map.end())
	{
		return;
	}
	else
	{
		Model_map[Name] = ImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
		assert(Model_map[Name]);

		//テクスチャ読み込み
		for (unsigned int i = 0; i < Model_map[Name]->mNumTextures; i++)
		{
			aiTexture* aitexture = Model_map[Name]->mTextures[i];

			ID3D11ShaderResourceView* texture;

			CreateTextureFromMemory(
				Renderer::GetDevice(),
				(const unsigned char*)aitexture->pcData,
				aitexture->mWidth,
				&texture);

			Texture_map[Name][aitexture->mFilename.data] = texture;
		}
		for (unsigned int i = 0; i < Model_map[Name]->mNumMaterials; i++) {
			aiMaterial* material = Model_map[Name]->mMaterials[i];
			aiString path;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
			if (path.length > 0) {
				ID3D11ShaderResourceView* texture = Texture_map[Name][path.data];
				if (!texture) {
					_makepath_s(szPath, _MAX_PATH, szDrive, szDir, path.data, nullptr);
					CreateTextureFromFile(
						Renderer::GetDevice(),
						szPath,
						&texture);
					Texture_map[Name][path.data] = texture;
				}
			}
		}
	}
}

void ModelInfo::LoadAnimInfo(const char * FileName, const std::string Name)
{
	auto it = Anim_map.find(Name);
	//見つかった場合
	if (it != Anim_map.end())
	{
		return;
	}
	else
	{
		Anim_map[Name] = ImportFile(FileName, aiProcess_ConvertToLeftHanded);
		assert(Anim_map[Name]);
	}
}
