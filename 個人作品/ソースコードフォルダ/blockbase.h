#pragma once
#include "gameObject.h"
class BlockBase : public GameObject
{
	
public:
	enum BlockType
	{
		None,
		Normal,		 // �m�[�}��
		Unbreakable, // �󂹂Ȃ�
		Max,
	};
	void Init() override;
	void SetBlock(DirectX::XMFLOAT3 pos, BlockType type);
	BlockType GetType() { return m_Type; }
private:
	BlockType m_Type;
	
};

