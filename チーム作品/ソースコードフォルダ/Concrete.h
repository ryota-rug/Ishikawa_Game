#ifndef ___CONCRETE_H___
#define ___CONCRETE_H___

#include "BlockBase.h"


class CConcrete	: public Block_Base
{
public:
	CConcrete(Stage_Base* MyStage, int PosX, int PosY);
	~CConcrete();

	void Update() override;
	void Draw() override;

	void CollisionNavigate() override;
};


#endif // !___CONCRETE_H___
