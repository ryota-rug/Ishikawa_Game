#include "CameraBase.h"

CameraBase::CameraBase()
	:m_pos(0.0f, 0.0f, -3.0f), m_look(0.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f),
	m_fovy(80.0f), m_aspect(16.0f / 9.0f), m_near(0.2f), m_far(2500.0f)
{

};

CameraBase::~CameraBase()
{

}

DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	/*�����o�ϐ������Ƀv���W�F�N�V�����s����쐬���A�]�u�ς݂̍s��Ƃ��Ė߂�l��Ԃ�*/
	DirectX::XMVECTOR EyePos = DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f);//�J�����ʒu
	DirectX::XMVECTOR FocusPos = DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f);//�J�������_
	DirectX::XMVECTOR UpDirection = DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);//�J���������
	view = DirectX::XMMatrixLookAtLH(EyePos, FocusPos, UpDirection);//�r���[���W�n�s��̍쐬
	view = XMMatrixTranspose(view);//�]�u

	DirectX::XMStoreFloat4x4(&mat, view);//�œK��

	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	/*�����o�[�ϐ������Ƀv���W�F�N�V�����s����쐬���A�]�u�ς݂̍s��Ƃ��Ė߂�l��Ԃ�*/
	float FovAngleY = Angle_To_Radion(m_fovy);//�J�����c�����̉�p
	float AspectRatio = m_aspect;//�c��1�Ƃ������̔䗦
	float NearZ = m_near;//�ǂ�����f����
	float FarZ = m_far;//�ǂ��܂ŉf����
	proj = DirectX::XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ);//�v���W�F�N�V�������W�n�s��̍쐬
	proj = XMMatrixTranspose(proj);//�]�u
	DirectX::XMStoreFloat4x4(&mat, proj);//�œK��

	return mat;
}

DirectX::XMFLOAT3 CameraBase::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 CameraBase::GetLook()
{
	return m_look;
}

void CameraBase::ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook)
{
	
}