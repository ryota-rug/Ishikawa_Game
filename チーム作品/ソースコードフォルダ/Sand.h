#ifndef ___SAND_H___
#define ___SAND_H___

#include "BlockBase.h"
#include "Sound.h"


class CSand : public Block_Base
{
public:
	CSand(Stage_Base* MyStage, int PosX, int PosY);
	~CSand();

	void Update() override;
	void Update_Refuge() override;
	void Draw() override;

	void CollisionNavigate() override;

private:
	FloatPos m_moveDrawPos;
	const float m_moveSpeed;
	bool m_moving;

	SE* m_pSEFall;
	SE* m_pSEToClay;

	bool m_touchOnWater;
	int m_lateFrame;
	Effekseer::Handle m_HitHandle;
	bool m_TurnHit;

private:
	bool CheckWater(int posX, int posY);
	bool m_bEffect = false; // ’…’n‚µ‚½Žž‚Éˆê“x‚¾‚¯•\Ž¦‚µ‚½‚¢
};


#endif // !___SAND_H___