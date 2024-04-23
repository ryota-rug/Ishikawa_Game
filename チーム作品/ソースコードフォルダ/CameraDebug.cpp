#include "CameraDebug.h"
#include "Input.h"
#include <DirectXMath.h>

using namespace DirectX;

float AddPosX;
float AddPosY;

//初期化 　
CameraDebug::CameraDebug()
	:m_AngleXZ(90.0f), m_AngleYFlont(96.0f), m_radXZ(00.0f), m_radY(0.0f), m_lateXZ(0.0f), m_lateYFlont(0.0f)
{
	AddPosX = 0.0f;
	AddPosY = 0.0f;
	//初期化位置は適当なので後で変えてください
	m_pos.x = -5.0f;
	m_pos.z = -327.0f;
	m_pos.y = 0.0f;

	HINANPOS = m_look;
}

void CameraDebug::Update()
{
	m_look = HINANPOS;

	//デバックカメラの移動方法
	XMVECTOR vcamPos = XMLoadFloat3(&m_pos);	//m_posをXMベクター型に変換
	XMVECTOR vcamLook = XMLoadFloat3(&m_look);	//m_lookををXMベクター型に変換

	XMVECTOR vFront = XMVectorSubtract(vcamLook, vcamPos);	//正面方向のベクトルを計算
	vFront = XMVector3Normalize(vFront);	//正規化

	XMMATRIX matRotSide = XMMatrixRotationY(90.0f * 3.14f / 180);	//Y軸に対して直角の回転行列を作成
	XMVECTOR vSide = XMVector3TransformCoord(vFront, matRotSide);	//vFrontに対して直角のベクトルを作成

	XMVECTOR vMove = XMVectorZero();//0で初期化
	if (IsKeyPress('W')) vMove = XMVectorAdd(vMove, vFront);		//画面正面に移動
	if (IsKeyPress('S')) vMove = XMVectorSubtract(vMove, vFront);	//画面後方に移動
	if (IsKeyPress('D')) vMove = XMVectorAdd(vMove, vSide);			//画面右に移動
	if (IsKeyPress('A')) vMove = XMVectorSubtract(vMove, vSide);	//画面左に移動

	XMStoreFloat3(&f3Flont, vFront);	//XMベクター型⇒XMFloat3型に変換
	f3Flont.y = 0;	//y方向の傾きを0にして横移動時に斜めに行かないようにする

	//デバックカメラの視点操作
	if (IsKeyPress(VK_UP)) m_AngleYFlont -= UD_ANGLE_SPEED;		
	if (IsKeyPress(VK_DOWN)) m_AngleYFlont += UD_ANGLE_SPEED;
	if (IsKeyPress(VK_RIGHT)) m_AngleXZ -= RL_ANGLE_SPEED;
	if (IsKeyPress(VK_LEFT)) m_AngleXZ += RL_ANGLE_SPEED;

	//カメラの可動域を制限
	if (m_AngleYFlont < LIMIT_TOP_ANGLE) m_AngleYFlont = LIMIT_TOP_ANGLE;
	if (m_AngleYFlont > LIMIT_BOTTOM_ANGLE) m_AngleYFlont = LIMIT_BOTTOM_ANGLE;

	//度をラジアンに変換
	m_radXZ = m_AngleXZ * 3.14f / 180;
	m_radY = m_AngleYFlont * 3.14f / 180;

	//ほんの少し遅らせて視点移動
	m_lateXZ = (m_radXZ - m_lateXZ) * 0.7f + m_lateXZ;
	m_lateYFlont = (m_radY - m_lateYFlont) * 0.7f + m_lateYFlont;

	//注視点は、カメラを中心に回る
	m_look.x = m_pos.x + cosf(m_lateXZ) * 150;
	m_look.z = m_pos.z + sinf(m_lateXZ) * 150;
	m_look.y = m_pos.y + cosf(m_lateYFlont) * 150;

	//移動速度を調整
	vMove = XMVectorScale(vMove, 0.5f);

	//ベクターをフロート３に
	XMFLOAT3 move;
	XMStoreFloat3(&move, vMove);

	//上の計算結果を反映
	m_pos.x += move.x;
	m_pos.z += move.z;

	//上下移動はベクトルいらないので簡単に移動できる
	if (IsKeyPress(VK_SPACE)) m_pos.y += 1.0f;
	if (IsKeyPress(VK_CONTROL)) m_pos.y -= 1.0f;

	HINANPOS = m_look;

	m_look.x += AddPosX;
	m_look.y += AddPosY;
	AddPosX *= -0.9f;
	AddPosY *= -0.9f;
}

void BiblationCameraDebug()
{
	AddPosX = 5.0f;
	AddPosY = 5.0f;
}
