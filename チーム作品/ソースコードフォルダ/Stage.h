//#pragma once
#ifndef STAGE_H_
#define STAGE_H_

#include <DirectXMath.h>
#include "Geometory.h"
#include "CameraBase.h"

enum POS_TYPE
{
	MIDDLE = 0,		//中央
	EDGE			//端
};

class Stage {
public: 
	struct Info {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
		DirectX::XMFLOAT3 rot;
	};
	

public :
	Stage() : m_pBlocks(nullptr), m_blockNum(20) {
		/*必要なブロックの数を考え、ブロックの情報を設定する*/
		m_pBlocks = new Info[m_blockNum];

		POS_TYPE Type = EDGE;

		CreateDrawBox(0.0f, 0.0f, 0.0f, 9.0f, 1.0f, 8.0f,Type);
		CreateDrawBox(7.0f, 1.0f, 2.0f, 2.0f, 1.0f, 4.0f,Type);
		CreateDrawBox(0.0f, 1.0f, 4.0f, 7.0f, 2.0f, 4.0f,Type);
		CreateDrawBox(7.0f, 1.0f, 6.0f, 2.0f, 2.0f, 2.0f,Type);
		CreateDrawBox(0.0f, 0.0f, 8.0f, 6.0f, 5.0f, 3.0f, Type);
		CreateDrawBox(7.0f, 3.0f, 9.0f, 1.0f, 1.0f, 1.0f, Type);
		float Hankei = sqrtf(2.0f * 2.0f + 2.0f * 2.0f);

		CreateDrawBox(1.0f, 3.0f, 8.0f, 2.0f, Hankei, Hankei, 45.0f, 0.0f, 0.0f, MIDDLE);
	}

	~Stage() {
		delete[] m_pBlocks;
	}

	void Draw() {
		for (int i = 0; i < CreateBoxNum; ++i)
		{
			SetGeometoryTranslate(m_pBlocks[i].pos.x, m_pBlocks[i].pos.y, m_pBlocks[i].pos.z);
			SetGeometoryScaling(m_pBlocks[i].size.x, m_pBlocks[i].size.y, m_pBlocks[i].size.z);
			SetGeometoryRotation(m_pBlocks[i].rot.x, m_pBlocks[i].rot.y, m_pBlocks[i].rot.z);
			DrawBox();
		}
	}

private:
	Info* m_pBlocks;
	int m_blockNum;

	int CreateBoxNum = 0;

private:
	void CreateDrawBox(float PosX, float PosY, float PosZ, float SizeX, float SizeY, float SizeZ, float Angle_AxisX, float Angle_AxisY, float Angle_AxisZ, POS_TYPE type);
	void CreateDrawBox(float PosX, float PosY, float PosZ, float SizeX, float SizeY, float SizeZ, POS_TYPE type);

};

#endif	//
