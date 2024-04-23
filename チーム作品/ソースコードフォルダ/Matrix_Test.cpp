#include "Matrix_Test.h"
#include <math.h>


Test_Matrix GetRotationX(float Radion);
Test_Matrix GetRotationY(float Radion);
Test_Matrix GetRotationZ(float Radion);
//Test_Matrix Matrix_Matrix(Test_Matrix mx, Test_Matrix my);
//st_Vector4 Vector_Matrix(st_Vector4 v, Test_Matrix m);

Test_Matrix GetRotationX(float Radion)
{
	Test_Matrix m;
	//XÇÃâÒì]çsóÒ
	m.m1 = 1.0f; m.m2 = 0.0f; m.m3 = 0.0f; m.m4 = 0.0f;
	m.m5 = 0.0f; m.m6 = cosf(Radion); m.m7 = -sin(Radion); m.m8 = 0.0f;
	m.m9 = 0.0f; m.m10 = sinf(Radion); m.m11 = cosf(Radion); m.m12 = 0.0f;
	m.m13 = 0.0f; m.m14 = 0.0f; m.m15 = 0.0f; m.m16 = 0.0f;

	return m;
}

Test_Matrix GetRotationY(float Radion)
{
	Test_Matrix m;
	//YÇÃâÒì]çsóÒ
	m.m1 = 1.0f; m.m2 = 0.0f; m.m3 = 0.0f; m.m4 = 0.0f;
	m.m5 = 0.0f; m.m6 = 1.0f; m.m7 = 0.0f; m.m8 = 0.0f;
	m.m9 = 0.0f; m.m10 = 0.0f; m.m11 = 1.0f; m.m12 = 0.0f;
	m.m13 = 0.0f; m.m14 = 0.0f; m.m15 = 0.0f; m.m16 = 0.0f;

	return m;
}

Test_Matrix GetRotationZ(float Radion)
{
	Test_Matrix m;
	//ZÇÃâÒì]çsóÒ
	m.m1 = 1.0f; m.m2 = 0.0f; m.m3 = 0.0f; m.m4 = 0.0f;
	m.m5 = 0.0f; m.m6 = 1.0f; m.m7 = 0.0f; m.m8 = 0.0f;
	m.m9 = 0.0f; m.m10 = 0.0f; m.m11 = 1.0f; m.m12 = 0.0f;
	m.m13 = 0.0f; m.m14 = 0.0f; m.m15 = 0.0f; m.m16 = 0.0f;

	return m;
}

//Test_Matrix Matrix_Matrix(Test_Matrix a, Test_Matrix b)
//{
//	return ;
//}
//
//st_Vector4 Vector_Matrix(st_Vector4 v, Test_Matrix m)
//{
//
//}
//
//st_Vector4 GetRotationPos(float Direction, float XRadion, float YRadion, float ZRadion)
//{
//	Test_Matrix xm, ym, zm;
//	st_Vector4 Pos = { 0.0f,0.0f,Direction , 1.0f};
//	xm = GetRotationX(XRadion);
//	ym = GetRotationY(YRadion);
//	zm = GetRotationZ(ZRadion);
//}