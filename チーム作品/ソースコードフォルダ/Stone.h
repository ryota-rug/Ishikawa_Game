#ifndef ___STONE_H___
#define ___STONE_H___

#include "BlockBase.h"


class CStone : public Block_Base
{
public:
	CStone(Stage_Base* MyStage, int PosX, int PosY);
	~CStone();

	void Update() override;
	void Draw() override;

	void CollisionNavigate() override;
};


#endif // !___BEDROCK_H___