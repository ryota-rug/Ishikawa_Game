//#pragma once
#ifndef H_Player
#define H_Player

#include "DirectX.h"
#include "CameraDebug.h"
#include "Game3D.h"
#include "Geometory.h"
#include "HeatGauge.h"
#include "KnockUI.h"
#include "Effect_Manager.h"

class Player
{
public :
	Player(): m_pos(0.0f,0.0f,0.0f)
	{
		m_pModel = new Model();
		//���f���̐�������
		if (!m_pModel->Load("Assets/3D/export/yakan.fbx"
			//Satono_Dia/Satono_Dia.pmx"
			, 0.005f, false))
		{
			MessageBox(nullptr, "���f���G���[", "Error", MB_OK);
		}

		//�V�F�[�_�[�ǂݍ��ݏ���(�O��쐬����ModelVS.cso��ǂݍ���)
		m_pVS = new VertexShader;
		if (FAILED(m_pVS->Load("Assets/Shader/ModelVS.cso")))
		{
			MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
		}

		m_pModel->SetVertexShader(m_pVS);

		//�萔�o�b�t�@�쐬(���[���h�A�r���[�A�v���W�F�N�V�����̃f�[�^���V�F�[�_�ɑ���
		m_pWVP = new ConstantBuffer();
		m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
	}
	~Player()
	{
		delete m_pWVP;
		delete m_pVS;
		delete m_pModel;
	}

	void Update()
	{
		//�J��������v���C���[�ɐL�тĂ���x�N�g������ړ��̕������v�Z
		DirectX::XMFLOAT3 camPos = m_pCamera->GetPos();				//�J�����̃|�W�V�������擾
		DirectX::XMFLOAT3 camLook = m_pCamera->GetLook();				//�J�����̒��_���擾
		camPos.y = camLook.y = 0.0f;
		DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);		//Float3��Vector�ɕϊ�
		DirectX::XMVECTOR vCamLook = DirectX::XMLoadFloat3(&camLook);

		DirectX::XMVECTOR vFront;								//�J�������璍�_(�v���C���[)�ւ̃x�N�g���������
		vFront = DirectX::XMVectorSubtract(vCamLook,vCamPos);	//�x�N�g���̌v�Z
		vFront = DirectX::XMVector3Normalize(vFront);			//���K��(1�ɂ���)

		float Radion = 90.0f * 3.141592f / 180.0f;

		DirectX::XMMATRIX matrotSide = DirectX::XMMatrixRotationY(Radion);//��]�s��
		DirectX::XMVECTOR vSide = DirectX::XMVector3TransformCoord(vFront, matrotSide);			//�J��������E�ɏo��x�N�g��

		DirectX::XMVECTOR vMove = DirectX::XMVectorZero();			//�[���ŏ�����

		//��ŏo�����x�N�g���𑫂�����������肷��
		if (IsKeyPress('A')) vMove = DirectX::XMVectorSubtract(vMove,vSide);
		if (IsKeyPress('D')) vMove = DirectX::XMVectorAdd(vMove,vSide);
	
		vMove = DirectX::XMVectorScale(vMove, 0.1f);	//�x�N�g���̒�����ύX

		DirectX::XMFLOAT3 move;		//��������
		DirectX::XMStoreFloat3(&move, vMove);	//��������������


		
		//�ړ�
//		m_pos.x += X  lane;
		m_pos.z += 0.0f;
	}

	void Draw()
	{
		if (!m_pCamera) { return; }
		DirectX::XMFLOAT4X4 mat[3];
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(5.0f, 5.0f, 5.0f);//�g��k���s��
		DirectX::XMMATRIX world = S * T;
		DirectX::XMStoreFloat4x4(&mat[0],
			DirectX::XMMatrixTranspose(world));
		mat[1] = m_pCamera->GetViewMatrix();
		mat[2] = m_pCamera->GetProjectionMatrix();
		m_pWVP->Write(mat);
		m_pWVP->BindVS(0);
		m_pModel->Draw();
	}

	void SetCamera(CameraBase *pCamera) { m_pCamera = pCamera; }

	DirectX::XMFLOAT3 GetPos() { return m_pos; }
	void SetPlayerPos(DirectX::XMFLOAT3 m_Setpos);
private :
	int X;
	CameraBase* m_pCamera;
	DirectX::XMFLOAT3 m_pos;
	Model* m_pModel;
	VertexShader* m_pVS;
	ConstantBuffer* m_pWVP;
};

//#include "StageBase.h"
#include "Position_struct.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "PileBankerBase.h"

class Stage_Base;

class C_Player
{
public :
	enum PLAYER_STATE
	{
		PLAYER_SELECTNOW,
		PLAYER_MOVENOW,
		PLAYER_SHOTNOW
	};

public:
	C_Player(Stage_Base* pStage);
	~C_Player();
	void Update();
	void Draw();
	void UIDraw();
	FloatPos GetPos();
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
	void MoveOK();
	void AddHeetItem();
	int GetLine();
	bool GetJudge();
	bool GetRightMove();
	KnockUI* GetKnock();
	Effekseer::Handle m_SteamHandle;
	void SetPos(DirectX::XMFLOAT3 SetPos);

private:
	//const
	const float Stage_Player_Distance;

	//
	Stage_Base* m_myStage;
	PLAYER_STATE m_NowState;
	int m_Line;
	FloatPos m_BasePosition;
	FloatPos m_Position;
	CModelManager *m_pModelManager;
	C_CameraManager *m_pCameraManager;
	PileBanker* m_tempBanker;
	int m_HeetItemNum;
	HeatGauge* m_pHeatGauge;
	KnockUI* m_pKnockUI;

	bool m_movejudge;
	bool m_moveright;
	float m_TotalTime;
	float m_NowTime;
	FloatPos m_StartPos;
	FloatPos m_EndPos;
	DirectX::XMFLOAT2 m_KeyGet;

	DirectX::XMFLOAT3 m_Rotation;
	/*�p�C���o���J�[�͌������ゾ���ɂ���
	���[���̑I���Ȃǂ͂������ł��Ă��܂�*/

	bool m_bOnce;	//�J�����̕������s�h�~�p
	bool m_bOnce2;

	int m_EffectFrame = 0;

	SE* m_pWalkSE;
};

#endif // !H_Player
