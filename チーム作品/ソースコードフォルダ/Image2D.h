//---------------------------------------------------------------------------
//　クラスごとに2D画像を管理できます
//　Image2D のポインタを宣言して使ってください
//　パラメータの変更は、メンバ変数に直接アクセスして行ってください
//---------------------------------------------------------------------------
#ifndef ___IMAGE_2D_H___
#define ___IMAGE_2D_H___

#include "DirectX.h"
#include "SpriteManager.h"
#include "DirectXTex/Texture.h"
#include <map>


class Image2D
{
public:
	DirectX::XMFLOAT2 pos;		// 中心座標
	DirectX::XMFLOAT2 size;		// 大きさ
	DirectX::XMFLOAT3 angle;	// 角度 (360 = 0)
	DirectX::XMFLOAT4 color;	// 色
	int texNum;	//テクスチャ番号

public:
	Image2D(LPCSTR filePath, SpriteManager* pSM);	//コンストラクタ
	~Image2D();										//デストラクタ

	//描画
	//直前でEnableDepth(false)を呼び出してください
	void Draw();


	//画像の反転
	//	bool reverseU : 横方向の反転フラグ
	//		[true]  反転する
	//		[false] 反転しない
	//	bool reverseV : 縦方向の反転フラグ
	//		[true]  反転する
	//		[false] 反転しない
	void Reverse(bool reverseU, bool reverseV);


	//テクスチャ分割
	//	float divisionU : 横方向の分割数
	//	float divisionV : 縦方向の分割数
	void SetTexScale(float divisionU, float divisionV);


	//アニメーション更新
	//	UINT frame : アニメーションを更新する間隔
	//	bool loop : アニメーションのループ設定
	void UpdateAnimation(UINT frame, bool loop = false);


protected:
	SpriteManager* m_pSpriteManager;	//スプライトマネージャ
	ID3D11ShaderResourceView* m_pImage;	//イメージソース

	bool m_reverseU;	//横方向の反転フラグ
	bool m_reverseV;	//縦方向の反転フラグ

	std::map<int, DirectX::XMFLOAT2> m_texPos;	//UV座標
	DirectX::XMFLOAT2 m_texScale;				//UVの大きさ
	UINT m_divisionTexNum;						//テクスチャ分割数

	UINT m_frame;	//経過フレーム数
};

#endif // !___IMAGE_2D_H___
