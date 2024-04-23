#ifndef ___BEDROCK_H___
#define ___BEDROCK_H___

#include "BlockBase.h"


class CBedrock : public Block_Base
{
public:
	CBedrock(Stage_Base* MyStage, int PosX, int PosY);
	virtual ~CBedrock();

	void Update() override;
	void Draw() override;

	void CollisionNavigate() override;
};


#endif // !___BEDROCK_H___