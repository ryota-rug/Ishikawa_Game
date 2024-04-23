#include "ModelManager.h"
#include "GameCamera.h"

#define GetRadion(Angle) (Angle * 3.141592f / 180.0f)

//�\����
typedef struct
{
	Model *model;			//���f���������Ă����ϐ�
}MODEL_INFORMATION;

VertexShader* pVS_ModelManager;		//���_�V�F�[�_�[
ConstantBuffer* pWVP_ModelManager;	//�萔�o�b�t�@�[

//�A�z�z��
std::map < std::string, MODEL_INFORMATION> Model_Information;

//��ΌĂԂ��!!
void ModelManager_Init()
{
	//�V�F�[�_�[�ǂݍ��ݏ���(�O��쐬����ModelVS.cso��ǂݍ���)
	pVS_ModelManager = new VertexShader;
	if (FAILED(pVS_ModelManager->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
	}

	//�萔�o�b�t�@�쐬(���[���h�A�r���[�A�v���W�F�N�V�����̃f�[�^���V�F�[�_�ɑ���
	pWVP_ModelManager = new ConstantBuffer();
	pWVP_ModelManager->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

void ModelManager_Uninit()
{
	for (auto& copy : Model_Information)
	{
		if (copy.second.model != nullptr)
		{
			delete copy.second.model;
		}
	}
	Model_Information.clear();

	delete pWVP_ModelManager;
	delete pVS_ModelManager;
}

//���f���̏���ǉ�����
void AddModel(const std::string CharName,const char* FileName)
{
	static int Count = 0;
	Count++;
	//�������̒��Ɏ��̂�����ꍇ
	std::map<std::string, MODEL_INFORMATION>::iterator it = Model_Information.find(CharName);
	
	//���������ꍇ
	if (it != Model_Information.end()){
		//MessageBox(nullptr, "�������̖��O�ō���Ă��܂�", "Error", MB_OK);
		return;
	}

	//���f���̐���
	Model_Information.insert(std::make_pair(CharName, 
		MODEL_INFORMATION{ nullptr }));

	//���f�����������ɍ��
	Model_Information[CharName].model = new Model;

	//�V�F�[�_�[�̐ݒ�
	Model_Information[CharName].model->SetVertexShader(pVS_ModelManager);

	//���f���̃��[�h����
	if (!Model_Information[CharName].model->Load(FileName, 1.0f, false))
	{
		MessageBox(nullptr, "���f���G���[!!!!!", "Error", MB_OK);
	}
}

void AllDelete()			//�S�Ẵ��f����������
{
	//for (std::pair<std::string, MODEL_INFORMATION> copy : Model_Information)
	for (auto& copy : Model_Information)
	{
		if (copy.second.model != nullptr)
		{
			delete copy.second.model;
		}
	}
	Model_Information.clear();
}

//�����ς����ɕ`�悷��
void ModelDraw(const std::string Name)
{
	ModelDraw(Name, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
}

//���f���������̏������Ƃɕ`�悷��
void ModelDraw(const std::string CharName, float PosX, float PosY, float PosZ, float ScaleX, float ScaleY, float ScaleZ, float AngleX, float AngleY, float AngleZ)
{
	std::map<std::string, MODEL_INFORMATION>::iterator it = Model_Information.find(CharName);
	//���̂��Ȃ������ꍇ
	if (it == Model_Information.end()) {
		MessageBox(nullptr, "���f���G���[", "Error", MB_OK);
		return;
	}

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(PosX, PosY, PosZ);	//�ړ�
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(GetRadion(AngleX));//X��]�s��
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(GetRadion(AngleY));//Y��]�s��
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(GetRadion(AngleZ));//Z��]�s��
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(ScaleX, ScaleY, ScaleZ);//�g��k���s��
	DirectX::XMMATRIX world = S * Rx * Ry * Rz * T;//���[���h���W�n�s��̍쐬
	DirectX::XMStoreFloat4x4(&mat[0],
		DirectX::XMMatrixTranspose(world));
	mat[1] = Get_ViewMat();		//�J�����̏�񂪕����莟�����
	mat[2] = Get_ProtMat();		//�J�����̏�񂪕����莟�����
	pWVP_ModelManager->Write(mat);
	pWVP_ModelManager->BindVS(0);

	Model_Information[CharName].model->Draw();
}
