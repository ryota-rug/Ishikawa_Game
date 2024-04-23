#include "Image2D.h"

using namespace DirectX;


Image2D::Image2D(LPCSTR filePath, SpriteManager* pSM) :
	pos(640.0f, 360.0f),
	size(100.0f, 100.0f),
	angle(0.0f, 0.0f, 0.0f),
	color(1.0f, 1.0f, 1.0f, 1.0f),
	texNum(0)
{
	m_pSpriteManager = pSM;
	LoadTextureFromFile(filePath, &m_pImage);	//テクスチャ読み込み

	m_reverseU = false;
	m_reverseV = false;

	m_texPos[0] = { 0.0f, 0.0f };
	m_texScale = { 1.0f, 1.0f };

	m_frame = 0;
}

Image2D::~Image2D()
{
	for (auto it = m_texPos.begin(); it != m_texPos.end();)
	{
		it = m_texPos.erase(it);
	}

	m_pSpriteManager->TextureRelease(m_pImage);
}

void Image2D::Draw()
{
	//テクスチャ番号が-1なら描画しない
	if (texNum == -1) { return; }


	//サイズのYがマイナスじゃないと表示されないので仮でマイナスにする
	XMFLOAT2 tmpSize = size;
	tmpSize.y *= -1.0f;

	//UV座標を反転させる
	XMFLOAT2 texPos = m_texPos[texNum];
	if (m_reverseU) { texPos.x -= m_texScale.x; }
	if (m_reverseV) { texPos.y -= m_texScale.y; }


	//描画
	m_pSpriteManager->Draw
	(
		pos, tmpSize, angle,	// 座標・大きさ・角度
		texPos, m_texScale,		// UV座標・UVの大きさ
		color,					// 色
		m_pImage				// 画像データ
	);
}



void Image2D::Reverse(bool reverseU, bool reverseV)
{
	m_reverseU = reverseU;
	m_reverseV = reverseV;


	//---X方向の反転
	if (reverseU)
	{
		//「UVの大きさ」が正の値であれば負の値にする
		if (m_texScale.x > 0.0f) { m_texScale.x = -m_texScale.x; }
	}
	else
	{
		//「UVの大きさ」が負の値であれば正の値にする
		if (m_texScale.x < 0.0f) { m_texScale.x = -m_texScale.x; } 
	}


	//---Y方向の反転
	if (reverseV)
	{
		//「UVの大きさ」が正の値であれば負の値にする
		if (m_texScale.y > 0.0f) { m_texScale.y = -m_texScale.y; }
	}
	else
	{
		//「UVの大きさ」が負の値であれば正の値にする
		if (m_texScale.y < 0.0f) { m_texScale.y = -m_texScale.y; }
	}
}

void Image2D::SetTexScale(float divisionU, float divisionV)
{
	//大きさの設定
	m_texScale = {1.0f/divisionU, 1.0f/divisionV};


	//座標の設定
	for (int i = 0; i < divisionV; i++)
	{
		for (int j = 0; j < divisionU; j++)
		{
			float scaleU = m_texScale.x * j;
			float scaleV = m_texScale.y * i;
			m_texPos[i*divisionU + j] = { scaleU, scaleV };
		}
	}

	//テクスチャ分割数
	m_divisionTexNum = divisionU * divisionV;
}

void Image2D::UpdateAnimation(UINT frame, bool loop)
{
	m_frame++;

	if (m_frame >= frame)
	{
		m_frame = 0;
		texNum++;

		if (loop)
		{
			texNum %= m_divisionTexNum; 
		}
		else
		{
			if (texNum >= m_divisionTexNum) { texNum = -1; }
		}
	}
}
