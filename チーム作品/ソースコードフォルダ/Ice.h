#ifndef ___ICE_H___
#define ___ICE_H___

#include "BlockBase.h"
#include "Effect_Manager.h"


class CIce : public Block_Base
{
public:
	CIce(Stage_Base* MyStage, int PosX, int PosY);
	~CIce();

	void Update() override;
	void Draw() override;

	void CollisionNavigate() override;

private:
	bool m_isChangeBlock;
	int m_nEffeckFrame = 0;
	Effekseer::Handle m_IceHandle;
	bool m_bEffectFlg = true;
};


#endif // !___ICE_H___