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
	/*メンバ変数を元にプロジェクション行列を作成し、転置済みの行列として戻り値を返す*/
	DirectX::XMVECTOR EyePos = DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f);//カメラ位置
	DirectX::XMVECTOR FocusPos = DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f);//カメラ注点
	DirectX::XMVECTOR UpDirection = DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);//カメラ上方向
	view = DirectX::XMMatrixLookAtLH(EyePos, FocusPos, UpDirection);//ビュー座標系行列の作成
	view = XMMatrixTranspose(view);//転置

	DirectX::XMStoreFloat4x4(&mat, view);//最適化

	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	/*メンバー変数を元にプロジェクション行列を作成し、転置済みの行列として戻り値を返す*/
	float FovAngleY = Angle_To_Radion(m_fovy);//カメラ縦方向の画角
	float AspectRatio = m_aspect;//縦を1とした横の比率
	float NearZ = m_near;//どこから映すか
	float FarZ = m_far;//どこまで映すか
	proj = DirectX::XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ);//プロジェクション座標系行列の作成
	proj = XMMatrixTranspose(proj);//転置
	DirectX::XMStoreFloat4x4(&mat, proj);//最適化

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