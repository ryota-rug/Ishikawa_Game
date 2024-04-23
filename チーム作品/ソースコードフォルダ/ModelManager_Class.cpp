#include "ModelManager_Class.h"
#include <Windows.h>
#include <DirectXMath.h>

#define GetRadion(Angle) (Angle * 3.141592f / 180.0f)

VertexShader* CModelManager::m_pVS_ModelManager;		//���_�V�F�[�_�[
ConstantBuffer* CModelManager::m_pWVP_ModelManager;	//�萔�o�b�t�@�[

//�A�z�z��
std::map < std::string,CModelManager::c_MODEL_INFORMATION> CModelManager::m_Model_Information;

CModelManager::CModelManager(CameraBase** Model_pCamera)
	:m_ppCamera(Model_pCamera)
{

}

CModelManager::~CModelManager()
{

}

//��ΌĂԂ��!!
void CModelManager::c_ModelManager_Init()
{
	//�V�F�[�_�[�ǂݍ��ݏ���(�O��쐬����ModelVS.cso��ǂݍ���)
	m_pVS_ModelManager = new VertexShader;
	if (FAILED(m_pVS_ModelManager->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
	}

	//�萔�o�b�t�@�쐬(���[���h�A�r���[�A�v���W�F�N�V�����̃f�[�^���V�F�[�_�ɑ���
	m_pWVP_ModelManager = new ConstantBuffer();
	m_pWVP_ModelManager->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

void CModelManager::c_ModelManager_Uninit()
{
	for (auto& copy : m_Model_Information)
	{
		if (copy.second.model != nullptr)
		{
			copy.second.Animetion.clear();

			delete copy.second.model;
		}
	}
	m_Model_Information.clear();

	delete m_pWVP_ModelManager;
	delete m_pVS_ModelManager;
}

//���f���̏���ǉ�����
void CModelManager::c_AddModel(const std::string CharName, const char* FileName)
{
	//�������̒��Ɏ��̂�����ꍇ
	std::map<std::string, c_MODEL_INFORMATION>::iterator it = m_Model_Information.find(CharName);

	//���������ꍇ
	if (it != m_Model_Information.end()) {
		//MessageBox(nullptr, "�������̖��O�ō���Ă��܂�", CharName.c_str(), MB_OK);
		return;
	}

	//���f���̐���
	m_Model_Information.insert(std::make_pair(CharName,
		c_MODEL_INFORMATION{ nullptr }));

	//���f�����������ɍ��
	m_Model_Information[CharName].model = new Model;

	//�V�F�[�_�[�̐ݒ�
	m_Model_Information[CharName].model->SetVertexShader(m_pVS_ModelManager);

	//���f���̃��[�h����
	if (!m_Model_Information[CharName].model->Load(FileName, 1.0f, false))
	{
		//MessageBox(nullptr, "���f���ǂݍ��݃G���[!", FileName, MB_OK);
	}

	m_Model_Information[CharName].AnimeNow = false;
}

void CModelManager::c_AddModel(const std::string CharName, const char* FileName, const char* TextureName)
{
	//�������̒��Ɏ��̂�����ꍇ
	std::map<std::string, c_MODEL_INFORMATION>::iterator it = m_Model_Information.find(CharName);

	//���������ꍇ
	if (it != m_Model_Information.end()) {
		//MessageBox(nullptr, "�������̖��O�ō���Ă��܂�", CharName.c_str(), MB_OK);
		return;
	}

	//���f���̐���
	m_Model_Information.insert(std::make_pair(CharName,
		c_MODEL_INFORMATION{ nullptr }));

	//���f�����������ɍ��
	m_Model_Information[CharName].model = new Model;

	//�V�F�[�_�[�̐ݒ�
	m_Model_Information[CharName].model->SetVertexShader(m_pVS_ModelManager);

	//���f���̃��[�h����
	if (!m_Model_Information[CharName].model->LoadAndTexture(FileName, TextureName, 1.0f, false))
	{
		//MessageBox(nullptr, "���f���ǂݍ��݃G���[!", FileName, MB_OK);
	}

	m_Model_Information[CharName].AnimeNow = false;
}

void CModelManager::c_AddAnimetion(const std::string AnimeName, const char* AnimeFileName, const std::string CharName,float StartFrame)		//�A�j���[�V������ǉ�����
{
	std::map<std::string, c_MODEL_INFORMATION>::iterator ModelIt = m_Model_Information.find(CharName);
	//���̂��Ȃ������ꍇ
	if (ModelIt == m_Model_Information.end()) {
		MessageBox(nullptr,"��񂪂Ȃ��̂ŃA�j���[�V������ǉ��ł��܂���", CharName.c_str(), MB_OK);
		return;
	}
	//���̂��Ȃ��ꍇ
	if(m_Model_Information[CharName].model == nullptr)
	{
		MessageBox(nullptr, "�ǉ����������f���̎��Ԃ��Ȃ��̂ŃA�j���[�V������ǉ��ł��܂���", CharName.c_str(), MB_OK);
		return;
	}

	//�������̒��Ɏ��̂�����ꍇ
	std::map<std::string, Model::AnimeNo>::iterator animeIt = m_Model_Information[CharName].Animetion.find(AnimeName);

	//���������ꍇ
	if (animeIt != m_Model_Information[CharName].Animetion.end()) {
		//MessageBox(nullptr, "�������̖��O�ō���Ă��܂�", CharName.c_str(), MB_OK);
		return;
	}

	m_Model_Information[CharName].Animetion.insert(std::make_pair(AnimeName,
		Model::AnimeNo{ m_Model_Information[CharName].model->AddAnimation(AnimeFileName,StartFrame) }));

	if (m_Model_Information[CharName].Animetion[AnimeName] == Model::ANIME_NONE)
	{
		MessageBox(nullptr, "�A�j���[�V�����G���[", "Error", MB_OK);
		return;
	}
}

void CModelManager::c_SetAnimetion(const std::string CharName, const std::string AnimeName, bool Repeat)
{
	std::map<std::string, c_MODEL_INFORMATION>::iterator modelit = m_Model_Information.find(CharName);
	//���̂��Ȃ������ꍇ
	if (modelit == m_Model_Information.end()) {
		MessageBox(nullptr, "���̖��O�̃��f�����Ȃ��̂ŃA�j���[�V�������Đ��ł��܂���", CharName.c_str(), MB_OK);
		return;
	}
	//���̂��Ȃ��ꍇ
	if (m_Model_Information[CharName].model == nullptr)
	{
		MessageBox(nullptr, "���f���̎��Ԃ��Ȃ��̂ŃA�j���[�V�������Đ��ł��܂���", CharName.c_str(), MB_OK);
		return;
	}
	//�A�j���[�V�������o�^����Ă��邩�̊m�F
	auto animeit = m_Model_Information[CharName].Animetion.find(AnimeName);
	if (animeit == m_Model_Information[CharName].Animetion.end())
	{
		MessageBox(nullptr, "���̃A�j���[�V�������o�^����ĂȂ��̂ōĐ��ł��܂���", CharName.c_str(), MB_OK);
		return;
	}

	//�A�j���[�V�����̍Đ�
	m_Model_Information[CharName].model->Play(m_Model_Information[CharName].Animetion[AnimeName], Repeat);
	m_Model_Information[CharName].AnimeNow = true;
}

void CModelManager::c_AllDelete()			//�S�Ẵ��f����������
{
	//for (std::pair<std::string, MODEL_INFORMATION> copy : Model_Information)
	for (auto& copy : m_Model_Information)
	{
		if (copy.second.model != nullptr)
		{
			delete copy.second.model;
		}
	}
	m_Model_Information.clear();
}

//�����ς����ɕ`�悷��
void CModelManager::c_ModelDraw(const std::string Name)
{
	c_ModelDraw(Name, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
}

//���f���������̏������Ƃɕ`�悷��
void CModelManager::c_ModelDraw(const std::string CharName, float PosX, float PosY, float PosZ, float ScaleX, float ScaleY, float ScaleZ, float AngleX, float AngleY, float AngleZ)
{
	ScaleX *= 1.32f;
	ScaleY *= 1.32f;
	ScaleZ *= 1.32f;
	std::map<std::string, c_MODEL_INFORMATION>::iterator it = m_Model_Information.find(CharName);
	//���̂��Ȃ������ꍇ
	if (it == m_Model_Information.end()) {
		//MessageBox(nullptr,"���f�����Ȃ��̂ŕ`��ł��܂���", "Error", MB_OK);
		return;
	}

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(PosX, PosY, PosZ);	//�ړ�
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(ScaleX, ScaleY, ScaleZ);//�g��k���s��
	
	//��]�s��͂��ꍇ�Ƃ��Ȃ��ꍇ�����邽��
	DirectX::XMMATRIX world;
	world = S;

	if (AngleX != 0.0f)
	{
		DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(GetRadion(AngleX));//X��]�s��
		world *= Rx;
	}

	if (AngleY != 0.0f)
	{
		DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(GetRadion(AngleY));//X��]�s��
		world *= Ry;
	}

	if (AngleZ != 0.0f)
	{
		DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(GetRadion(AngleZ));//X��]�s��
		world *= Rz;
	}

	world *= T;
	
	DirectX::XMStoreFloat4x4(&mat[0],
	DirectX::XMMatrixTranspose(world));
	mat[1] = (*m_ppCamera)->GetViewMatrix();		//�J�����̏�񂪕����莟�����
	mat[2] = (*m_ppCamera)->GetProjectionMatrix();		//�J�����̏�񂪕����莟�����
	m_pWVP_ModelManager->Write(mat);
	m_pWVP_ModelManager->BindVS(0);
	
	if(m_Model_Information[CharName].AnimeNow)
	m_Model_Information[CharName].model->Step(1.0f / 60.0f);
	
	
	m_Model_Information[CharName].model->Draw();
}

void CModelManager::c_SetCamera(CameraBase* NewPointer)
{
	delete *m_ppCamera;

	*m_ppCamera = NewPointer;
}

CameraBase* CModelManager::c_GetCamera()
{
	return *m_ppCamera;
}
