#pragma once

#include <unordered_map>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>

#include "component.h"


//�ό`�㒸�_�\����
struct DEFORM_VERTEX
{
	aiVector3D	Position;
	aiVector3D	Normal;
	int			BoneNum;
	std::string	BoneName[4];//�{���̓{�[���C���f�b�N�X�ŊǗ�����ׂ�
	float		BoneWeight[4];
};

//�{�[���\����
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};

class AnimationModel : public Component
{
private:
	aiScene* m_AiScene = nullptr;
	std::unordered_map<std::string, const aiScene*> m_Animation;

	ID3D11Buffer**	m_VertexBuffer;
	ID3D11Buffer**	m_IndexBuffer;

	//std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;

	std::vector<DEFORM_VERTEX>* m_DeformVertex;//�ό`�㒸�_�f�[�^
	std::unordered_map<std::string, BONE> m_Bone;//�{�[���f�[�^�i���O�ŎQ�Ɓj

	void CreateBone(aiNode* Node);
	void UpdateBoneMatrix(aiNode* Node, aiMatrix4x4 Matrix);
	aiScene* ImportFile(const char *pFile, unsigned int pFlags);
	std::string m_name;
public:
	using Component::Component;

	void Load(const char *FileName , const std::string Name);
	void LoadAnimation(const char *FileName, const char *AnimName);
	void Uninit() override;
	void Update(const char *AnimationName, int Frame);
	void Update(const char *AnimationName1, int Frame1, const char *AnimationName2, int Frame2, float BlendRate);
	void Draw() override;
};
