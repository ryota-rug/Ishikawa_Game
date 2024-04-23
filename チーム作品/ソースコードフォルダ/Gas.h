#ifndef ___GAS_H___
#define ___GAS_H___

#include "BlockBase.h"
#include "Sound.h"

class CGas : public Block_Base
{
public:
	CGas(Stage_Base* MyStage, int PosX, int PosY);
	~CGas();

	void Update() override;
	void Draw() override;

	void CollisionNavigate() override;

	void ExplosionGas(int posX, int posY);



private:
	bool m_exploded;			//爆発終了フラグ (2回以上爆発しないために使用)

	FloatPos m_moveDrawPos;		//描画場所の移動量を保持する変数
	const float m_moveSpeed;	//m_moveDrawPos の移動するスピード
	bool m_moving;				//移動中フラグ (true ならマップ上の座標を変えない)

	SE* m_pSEExplosion;				//爆発時のSE
	SE* m_pSECollisionNormalBunker;	//通常杭が当たった時のSE
	SE* m_pBreak_ItemSE;

	float m_Angle;
	FloatPos m_MovePos;


private:
	int CheckLeft(int distance);	//左上にブロックがあればそこまでの距離を返す
	int CheckRight(int distance);	//右上にブロックがあればそこまでの距離を返す

	int CheckLeftGas(int distance);		//左(または上)にガスがあればそこまでの距離を返す
	int CheckRightGas(int distance);	//右(または上)にガスがあればそこまでの距離を返す

	void MoveGas(int leftDis, int rightDis);	//ガスの移動
	
	int m_bEffectFlg = 0;
};

#endif // !___GAS_H___