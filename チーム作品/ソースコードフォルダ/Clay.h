#ifndef ___CLAY_H___
#define ___CLAY_H___

#include "BlockBase.h"


class CClay : public Block_Base
{
public:
	CClay(Stage_Base* MyStage, int PosX, int PosY);
	~CClay();

	void Update() override;
	void Draw() override;
	
	void CollisionNavigate() override;
};


#endif // !___CLAY_H___