//#pragma once
#ifndef COLLISION_H
#define COLLISION_H
#include "DirectX.h"
#include <DirectXMath.h>

class Collision
{
public:
//�����蔻����s���`��
struct Plane
{
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 pos;
};

struct Triangle 
{
	DirectX::XMFLOAT3 p[3];	//�O�p�`�̍��W
};

struct Ray
{
	DirectX::XMFLOAT3 start;
	DirectX::XMFLOAT3 direction;
	float length;
};

//�����蔻��̌���
struct Result
{
	bool hit;
	DirectX::XMFLOAT3 point;
};

public :
	//�`�󂲂Ƃ̓����蔻�������
	static Result CheckRayPlane(Ray ray, Plane plane);
	static Result CheckPointTriangle(DirectX::XMFLOAT3 point, Triangle triangle);
	static bool CheckCircle(DirectX::XMFLOAT3 point1, float Length1, DirectX::XMFLOAT3 point2, float Length2);
	static bool CheckSquare(DirectX::XMFLOAT3 point1, float Length1, DirectX::XMFLOAT3 point2, float Length2);

private:


};

#endif //COLLISION_H

