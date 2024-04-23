#include "Stage.h"
#include <vector>

const float X_BoxSize = 3.0f;
const float Y_BoxSize = 3.0f;
const float Z_BoxSize = 3.0f;

void Stage::CreateDrawBox(float PosX, float PosY, float PosZ, float SizeX, float SizeY, float SizeZ, float Angle_AxisX, float Angle_AxisY, float Angle_AxisZ, POS_TYPE type)
{
	if (CreateBoxNum + 1 > m_blockNum)
	{
		return;
	}
	//サイズの設定
	m_pBlocks[CreateBoxNum].size.x = SizeX * X_BoxSize;
	m_pBlocks[CreateBoxNum].size.y = SizeY * Y_BoxSize;
	m_pBlocks[CreateBoxNum].size.z = SizeZ * Z_BoxSize;

	//角度の設定
	m_pBlocks[CreateBoxNum].rot.x = Angle_To_Radion(Angle_AxisX);
	m_pBlocks[CreateBoxNum].rot.y = Angle_To_Radion(Angle_AxisY);
	m_pBlocks[CreateBoxNum].rot.z = Angle_To_Radion(Angle_AxisZ);

	switch (type)
	{
	case MIDDLE:	//真ん中で座標を入れている
		m_pBlocks[CreateBoxNum].pos.x = PosX * X_BoxSize;
		m_pBlocks[CreateBoxNum].pos.y = PosY * Y_BoxSize;
		m_pBlocks[CreateBoxNum].pos.z = PosZ * Z_BoxSize;
		break;
	case EDGE:		//端で座標を入れている
		DirectX::XMFLOAT3 Pos;
		Pos.x = PosX * X_BoxSize + (SizeX * X_BoxSize * 0.5f);
		Pos.y = PosY * Y_BoxSize + (SizeY * Y_BoxSize * 0.5f);
		Pos.z = PosZ * Z_BoxSize + (SizeZ * Z_BoxSize * 0.5f);
		m_pBlocks[CreateBoxNum].pos = Pos;
		break;
	}

	CreateBoxNum++;

}

void Stage::CreateDrawBox(float PosX, float PosY, float PosZ, float SizeX, float SizeY, float SizeZ, POS_TYPE type)
{
	CreateDrawBox(PosX, PosY, PosZ, SizeX, SizeY, SizeZ, 0.0f, 0.0f, 0.0f, type);
}