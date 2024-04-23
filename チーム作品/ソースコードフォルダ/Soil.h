#ifndef ___SOIL_H___
#define ___SOIL_H___

#include "BlockBase.h"


class CSoil : public Block_Base
{
public:
	CSoil(Stage_Base* MyStage, int PosX, int PosY);
	~CSoil();

	void Update() override;
	void Draw() override;

	void CollisionNavigate() override;
};


#endif // !___SOIL_H___