#include "Collision.h"

Collision::Result Collision::CheckRayPlane(Collision::Ray ray, Collision::Plane plane)
{
	Collision::Result result = {};

	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&ray.start);		//光線の始まり地点
	DirectX::XMVECTOR vRayN		= DirectX::XMLoadFloat3(&ray.direction);	//光線の向き
	DirectX::XMVECTOR vPlaneN	= DirectX::XMLoadFloat3(&plane.normal);		//面の法線(真上)
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&plane.pos);		//面の位置
	vRayN	= DirectX::XMVector3Normalize(vRayN);							//Rayのベクトルを正規化
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);							//面の法線を正規化

	//1)平面から始点までの距離
	float P1;
	DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);/*平面からレイの始点までのベクトル*/
	DirectX::XMVECTOR format = DirectX::XMVector3Dot(vPlaneN, vToStart);/*面の法線と始点に向かうベクトルと内積の結果を計算*/
	DirectX::XMStoreFloat(&P1, format);/*計算結果をP1へ格納(制の値化の判定や、表面の比率に使用)*/

	//2)終点から平面までの距離
	float P2;
	DirectX::XMVECTOR RayVector = DirectX::XMVectorScale(vRayN, ray.length);	//レイのベクトル(方向、大きさ)
	DirectX::XMVECTOR vRayEnd	= DirectX::XMVectorAdd(vRayStart,RayVector);	//レイの終了地点(レイの始点+レイのベクトル)
	DirectX::XMVECTOR vToEnd	= DirectX::XMVectorSubtract(vRayEnd, vPlanePos);/*平面からレイの終点までのベクトル*/
	format = DirectX::XMVector3Dot(vPlaneN, vToEnd);/*面の法線と終点に向かうベクトルとの内積の結果を計算*/
	DirectX::XMStoreFloat(&P2, format);/*計算結果をP2へ格納(負の値化の判定や、裏面の比率に使用)*/

		//3)レイが画面を貫通しているか
		bool UpDown;
		if ((UpDown = (P1 >= 0 && P2 <= 0)) || (P1 <= 0 && P2 >= 0))
		{
			result.hit = true;

			float Raito;		//レイの始点から当たっているところ(面)までの比率
			
			//上から下へのレイの場合
			if (UpDown)		Raito = ray.length * (P1 / (P1 + (P2 * -1.0f)));	//全体の長さから始点と衝突の長さの比率の計算
			//下から上への例の場合
			else			Raito = ray.length * ((P1 * -1.0f) / ((P1 * -1.0f) + P2));

			DirectX::XMVECTOR rayLenght = DirectX::XMVectorScale(vRayN, Raito);		//レイが面と当たるところまでの長さを求める
			DirectX::XMVECTOR Plane_Ray_HitPoint = DirectX::XMVectorAdd(vRayStart, rayLenght);		//レイと面が当たっているポジション

			DirectX::XMStoreFloat3(&result.point, Plane_Ray_HitPoint);	//保存
		}

		return result;
}

Collision::Result Collision::CheckPointTriangle(DirectX::XMFLOAT3 point, Collision::Triangle triangle)
{
	Collision::Result result = {};

	DirectX::XMVECTOR vCross[3];//外積の計算結果
	DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point);	
	DirectX::XMVECTOR vTriStart = DirectX::XMLoadFloat3(&triangle.p[0]);

	for (int i = 0; i < 3; i++)
	{
		int Num = (i + 1) % 3;
		DirectX::XMVECTOR vTriEnd = DirectX::XMLoadFloat3(&triangle.p[Num]);
		DirectX::XMVECTOR vTriEdge = DirectX::XMVectorSubtract(vTriEnd, vTriStart);		//辺のベクトル
		DirectX::XMVECTOR vTriPoint = DirectX::XMVectorSubtract(vPoint, vTriStart);		//点に向かうベクトル
		vCross[i] = DirectX::XMVector3Cross(vTriEdge, vTriPoint);						//外積計算
		vCross[i] = DirectX::XMVector3Normalize(vCross[i]);								//正規化
		vTriStart = vTriEnd;															//今の終点が、次の始点になる
	}

	//内積
	DirectX::XMVECTOR vDot[3] = {
		DirectX::XMVector3Dot(vCross[0],vCross[1]),
		DirectX::XMVector3Dot(vCross[1],vCross[2]),
		DirectX::XMVector3Dot(vCross[2],vCross[0]),
	};
	float match[3];

	//内積結果をfloatに変えてやる
	for (int i = 0; i < 3; i++)
	{
		DirectX::XMStoreFloat(&match[i], vDot[i]);
	}

	//内積の結果が全て同じだったら
	if((match[0] > 0 && match[1] > 0 && match[2] > 0) ||
	(match[0] < 0 && match[1] < 0 && match[2] < 0))
	{
		result.hit = true;
		result.point = point;
	}

	return result;
}

//丸同士の当たり判定
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

//四角同士の当たり判定
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