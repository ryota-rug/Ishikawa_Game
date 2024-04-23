//#pragma once
#ifndef POS_STRUCT_H
#define POS_STRUCT_H
#include<DirectXMath.h>


struct FloatPos
{
	float X;
	float Y;
	float Z;

	const FloatPos operator+ (const FloatPos fp) const
	{
		FloatPos tmp;
		tmp.X = X + fp.X;
		tmp.Y = Y + fp.Y;
		tmp.Z = Z + fp.Z;
		return tmp;
	}
};

struct FloatSize
{
	float X;
	float Y;
	float Z;
};

struct IntPos
{
	int X;
	int Y;
};


#endif // !POS_STRUCT_H
