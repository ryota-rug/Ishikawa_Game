#include "Collision.h"

Collision::Result Collision::CheckRayPlane(Collision::Ray ray, Collision::Plane plane)
{
	Collision::Result result = {};

	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&ray.start);		//�����̎n�܂�n�_
	DirectX::XMVECTOR vRayN		= DirectX::XMLoadFloat3(&ray.direction);	//�����̌���
	DirectX::XMVECTOR vPlaneN	= DirectX::XMLoadFloat3(&plane.normal);		//�ʂ̖@��(�^��)
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&plane.pos);		//�ʂ̈ʒu
	vRayN	= DirectX::XMVector3Normalize(vRayN);							//Ray�̃x�N�g���𐳋K��
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);							//�ʂ̖@���𐳋K��

	//1)���ʂ���n�_�܂ł̋���
	float P1;
	DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);/*���ʂ��烌�C�̎n�_�܂ł̃x�N�g��*/
	DirectX::XMVECTOR format = DirectX::XMVector3Dot(vPlaneN, vToStart);/*�ʂ̖@���Ǝn�_�Ɍ������x�N�g���Ɠ��ς̌��ʂ��v�Z*/
	DirectX::XMStoreFloat(&P1, format);/*�v�Z���ʂ�P1�֊i�[(���̒l���̔����A�\�ʂ̔䗦�Ɏg�p)*/

	//2)�I�_���畽�ʂ܂ł̋���
	float P2;
	DirectX::XMVECTOR RayVector = DirectX::XMVectorScale(vRayN, ray.length);	//���C�̃x�N�g��(�����A�傫��)
	DirectX::XMVECTOR vRayEnd	= DirectX::XMVectorAdd(vRayStart,RayVector);	//���C�̏I���n�_(���C�̎n�_+���C�̃x�N�g��)
	DirectX::XMVECTOR vToEnd	= DirectX::XMVectorSubtract(vRayEnd, vPlanePos);/*���ʂ��烌�C�̏I�_�܂ł̃x�N�g��*/
	format = DirectX::XMVector3Dot(vPlaneN, vToEnd);/*�ʂ̖@���ƏI�_�Ɍ������x�N�g���Ƃ̓��ς̌��ʂ��v�Z*/
	DirectX::XMStoreFloat(&P2, format);/*�v�Z���ʂ�P2�֊i�[(���̒l���̔����A���ʂ̔䗦�Ɏg�p)*/

		//3)���C����ʂ��ђʂ��Ă��邩
		bool UpDown;
		if ((UpDown = (P1 >= 0 && P2 <= 0)) || (P1 <= 0 && P2 >= 0))
		{
			result.hit = true;

			float Raito;		//���C�̎n�_���瓖�����Ă���Ƃ���(��)�܂ł̔䗦
			
			//�ォ�牺�ւ̃��C�̏ꍇ
			if (UpDown)		Raito = ray.length * (P1 / (P1 + (P2 * -1.0f)));	//�S�̂̒�������n�_�ƏՓ˂̒����̔䗦�̌v�Z
			//�������ւ̗�̏ꍇ
			else			Raito = ray.length * ((P1 * -1.0f) / ((P1 * -1.0f) + P2));

			DirectX::XMVECTOR rayLenght = DirectX::XMVectorScale(vRayN, Raito);		//���C���ʂƓ�����Ƃ���܂ł̒��������߂�
			DirectX::XMVECTOR Plane_Ray_HitPoint = DirectX::XMVectorAdd(vRayStart, rayLenght);		//���C�Ɩʂ��������Ă���|�W�V����

			DirectX::XMStoreFloat3(&result.point, Plane_Ray_HitPoint);	//�ۑ�
		}

		return result;
}

Collision::Result Collision::CheckPointTriangle(DirectX::XMFLOAT3 point, Collision::Triangle triangle)
{
	Collision::Result result = {};

	DirectX::XMVECTOR vCross[3];//�O�ς̌v�Z����
	DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point);	
	DirectX::XMVECTOR vTriStart = DirectX::XMLoadFloat3(&triangle.p[0]);

	for (int i = 0; i < 3; i++)
	{
		int Num = (i + 1) % 3;
		DirectX::XMVECTOR vTriEnd = DirectX::XMLoadFloat3(&triangle.p[Num]);
		DirectX::XMVECTOR vTriEdge = DirectX::XMVectorSubtract(vTriEnd, vTriStart);		//�ӂ̃x�N�g��
		DirectX::XMVECTOR vTriPoint = DirectX::XMVectorSubtract(vPoint, vTriStart);		//�_�Ɍ������x�N�g��
		vCross[i] = DirectX::XMVector3Cross(vTriEdge, vTriPoint);						//�O�όv�Z
		vCross[i] = DirectX::XMVector3Normalize(vCross[i]);								//���K��
		vTriStart = vTriEnd;															//���̏I�_���A���̎n�_�ɂȂ�
	}

	//����
	DirectX::XMVECTOR vDot[3] = {
		DirectX::XMVector3Dot(vCross[0],vCross[1]),
		DirectX::XMVector3Dot(vCross[1],vCross[2]),
		DirectX::XMVector3Dot(vCross[2],vCross[0]),
	};
	float match[3];

	//���ό��ʂ�float�ɕς��Ă��
	for (int i = 0; i < 3; i++)
	{
		DirectX::XMStoreFloat(&match[i], vDot[i]);
	}

	//���ς̌��ʂ��S�ē�����������
	if((match[0] > 0 && match[1] > 0 && match[2] > 0) ||
	(match[0] < 0 && match[1] < 0 && match[2] < 0))
	{
		result.hit = true;
		result.point = point;
	}

	return result;
}

//�ۓ��m�̓����蔻��
bool Collision::CheckCircle(DirectX::XMFLOAT3 point1, float Length1, DirectX::XMFLOAT3 point2, float Length2)
{
	bool b_Collision = false;
	float HarfLength1 = Length1 * 0.5f;
	float HarfLength2 = Length2 * 0.5f;
	float Distance = HarfLength1 + HarfLength2;

	if (((point1.x - point2.x) * (point1.x - point2.x)) +
		((point1.y - point2.y) * (point1.y - point2.y)) +
		((point1.z - point2.z) * (point1.z - point2.z)) <=
		Distance * Distance)
	{
		b_Collision = true;
	}

	return b_Collision;
}

//�l�p���m�̓����蔻��
bool Collision::CheckSquare(DirectX::XMFLOAT3 point1, float Length1, DirectX::XMFLOAT3 point2, float Length2)
{
	bool b_Collision = false;
	float HarfLength1 = Length1 * 0.5f;
	float HarfLength2 = Length2 * 0.5f;

	if (point1.x + HarfLength1 >= point2.x - HarfLength2 &&
		point1.x - HarfLength1 <= point2.x + HarfLength2 &&
		point1.y + HarfLength1 >= point2.y - HarfLength2 &&
		point1.y - HarfLength1 <= point2.y + HarfLength2 &&
		point1.z + HarfLength1 >= point2.z - HarfLength2 &&
		point1.z - HarfLength1 <= point2.z + HarfLength2)
	{
		b_Collision = true;
	}

	return b_Collision;
}