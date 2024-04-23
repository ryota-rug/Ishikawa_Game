#include "CameraDebug.h"
#include "Input.h"
#include <DirectXMath.h>

using namespace DirectX;

float AddPosX;
float AddPosY;

//������ �@
CameraDebug::CameraDebug()
	:m_AngleXZ(90.0f), m_AngleYFlont(96.0f), m_radXZ(00.0f), m_radY(0.0f), m_lateXZ(0.0f), m_lateYFlont(0.0f)
{
	AddPosX = 0.0f;
	AddPosY = 0.0f;
	//�������ʒu�͓K���Ȃ̂Ō�ŕς��Ă�������
	m_pos.x = -5.0f;
	m_pos.z = -327.0f;
	m_pos.y = 0.0f;

	HINANPOS = m_look;
}

void CameraDebug::Update()
{
	m_look = HINANPOS;

	//�f�o�b�N�J�����̈ړ����@
	XMVECTOR vcamPos = XMLoadFloat3(&m_pos);	//m_pos��XM�x�N�^�[�^�ɕϊ�
	XMVECTOR vcamLook = XMLoadFloat3(&m_look);	//m_look����XM�x�N�^�[�^�ɕϊ�

	XMVECTOR vFront = XMVectorSubtract(vcamLook, vcamPos);	//���ʕ����̃x�N�g�����v�Z
	vFront = XMVector3Normalize(vFront);	//���K��

	XMMATRIX matRotSide = XMMatrixRotationY(90.0f * 3.14f / 180);	//Y���ɑ΂��Ē��p�̉�]�s����쐬
	XMVECTOR vSide = XMVector3TransformCoord(vFront, matRotSide);	//vFront�ɑ΂��Ē��p�̃x�N�g�����쐬

	XMVECTOR vMove = XMVectorZero();//0�ŏ�����
	if (IsKeyPress('W')) vMove = XMVectorAdd(vMove, vFront);		//��ʐ��ʂɈړ�
	if (IsKeyPress('S')) vMove = XMVectorSubtract(vMove, vFront);	//��ʌ���Ɉړ�
	if (IsKeyPress('D')) vMove = XMVectorAdd(vMove, vSide);			//��ʉE�Ɉړ�
	if (IsKeyPress('A')) vMove = XMVectorSubtract(vMove, vSide);	//��ʍ��Ɉړ�

	XMStoreFloat3(&f3Flont, vFront);	//XM�x�N�^�[�^��XMFloat3�^�ɕϊ�
	f3Flont.y = 0;	//y�����̌X����0�ɂ��ĉ��ړ����Ɏ΂߂ɍs���Ȃ��悤�ɂ���

	//�f�o�b�N�J�����̎��_����
	if (IsKeyPress(VK_UP)) m_AngleYFlont -= UD_ANGLE_SPEED;		
	if (IsKeyPress(VK_DOWN)) m_AngleYFlont += UD_ANGLE_SPEED;
	if (IsKeyPress(VK_RIGHT)) m_AngleXZ -= RL_ANGLE_SPEED;
	if (IsKeyPress(VK_LEFT)) m_AngleXZ += RL_ANGLE_SPEED;

	//�J�����̉���𐧌�
	if (m_AngleYFlont < LIMIT_TOP_ANGLE) m_AngleYFlont = LIMIT_TOP_ANGLE;
	if (m_AngleYFlont > LIMIT_BOTTOM_ANGLE) m_AngleYFlont = LIMIT_BOTTOM_ANGLE;

	//�x�����W�A���ɕϊ�
	m_radXZ = m_AngleXZ * 3.14f / 180;
	m_radY = m_AngleYFlont * 3.14f / 180;

	//�ق�̏����x�点�Ď��_�ړ�
	m_lateXZ = (m_radXZ - m_lateXZ) * 0.7f + m_lateXZ;
	m_lateYFlont = (m_radY - m_lateYFlont) * 0.7f + m_lateYFlont;

	//�����_�́A�J�����𒆐S�ɉ��
	m_look.x = m_pos.x + cosf(m_lateXZ) * 150;
	m_look.z = m_pos.z + sinf(m_lateXZ) * 150;
	m_look.y = m_pos.y + cosf(m_lateYFlont) * 150;

	//�ړ����x�𒲐�
	vMove = XMVectorScale(vMove, 0.5f);

	//�x�N�^�[���t���[�g�R��
	XMFLOAT3 move;
	XMStoreFloat3(&move, vMove);

	//��̌v�Z���ʂ𔽉f
	m_pos.x += move.x;
	m_pos.z += move.z;

	//�㉺�ړ��̓x�N�g������Ȃ��̂ŊȒP�Ɉړ��ł���
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
