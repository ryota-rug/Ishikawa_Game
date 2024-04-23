#include "SpriteManager.h"
#include "DirectXTex/Texture.h"

using namespace std;
using namespace DirectX;


//----- 定数定義 -----
const float WindowLeft(0.0f);       // 画面左端の座標
const float WindowRight(1280.0f);	// 画面右端の座標
const float WindowBottom(720.0f);	// 画面下端の座標
const float WindowTop(0.0f);        // 画面上端の座標
const float NearZ(-1.0f);           // Z方向で写せる最小値
const float FarZ(1.0f);             // Z方向で写せる最大値

BlendState* SpriteManager::m_pBlend;


//--------------------
// コンストラクタ
//--------------------
SpriteManager::SpriteManager()
{
	m_pSampler = new SamplerState;
}


//--------------------
// デストラクタ
//--------------------
SpriteManager::~SpriteManager()
{
	delete m_pSampler;
}


//-------------------------
// 2D描画の設定
//-------------------------
void SpriteManager::Init()
{
	m_pBlend = new BlendState;

	// ブレンドステート
	D3D11_RENDER_TARGET_BLEND_DESC blend = {};
	blend.BlendEnable = TRUE;
	blend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend.SrcBlendAlpha = D3D11_BLEND_ONE;
	blend.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend.DestBlendAlpha = D3D11_BLEND_ONE;
	blend.BlendOp = D3D11_BLEND_OP_ADD;
	blend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	m_pBlend->Create(blend);
	m_pBlend->Bind();
}


//-------------------------
// テクスチャの解放
//-------------------------
void SpriteManager::TextureRelease(ID3D11ShaderResourceView* pptex)
{
	if (pptex != nullptr)
	{
		pptex->Release();
		pptex = nullptr;
	}
}


//--------------------
// 描画
//--------------------
void SpriteManager::Draw
(
	DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 angle,
	DirectX::XMFLOAT2 uvPos, DirectX::XMFLOAT2 uvScale,
	DirectX::XMFLOAT4 color,
	ID3D11ShaderResourceView* pptex
)
{
	// ビュー行列
	XMFLOAT4X4 fView;
	XMStoreFloat4x4(&fView, XMMatrixIdentity());   // 単位行列を作成

	// プロジェクション行列
	XMFLOAT4X4 fProj;
	XMMATRIX matProj = XMMatrixOrthographicOffCenterLH(WindowLeft, WindowRight, WindowBottom, WindowTop, NearZ, FarZ);
	XMStoreFloat4x4(&fProj, XMMatrixTranspose(matProj));

	// ワールド行列
	// 画面の解像度を元に大きさと表示位置を計算
	XMFLOAT4X4 fWorld;
	XMMATRIX T  = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	XMMATRIX Rx = XMMatrixRotationX(XMConvertToRadians(angle.x));
	XMMATRIX Ry = XMMatrixRotationY(XMConvertToRadians(angle.y));
	XMMATRIX Rz = XMMatrixRotationZ(XMConvertToRadians(angle.z));
	XMMATRIX S  = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX matWorld = S * Rx * Ry * Rz * T;
	XMStoreFloat4x4(&fWorld, XMMatrixTranspose(matWorld));


	// スプライトの設定
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	Sprite::SetSize(size);
	Sprite::SetUVPos(uvPos);
	Sprite::SetUVScale(uvScale);
	Sprite::SetColor(color);
	Sprite::SetTexture(pptex);
	Sprite::Draw();
}


//--------------------
// ビルボード描画
//--------------------
void SpriteManager::DrawBillBoard
(
	XMFLOAT3 pos, XMFLOAT2 size,
	XMFLOAT2 uvPos, XMFLOAT2 uvScale, 
	XMFLOAT4 color,
	ID3D11ShaderResourceView* pptex,
	CameraBase* pCamera
)
{
	// カメラのビュー逆行列
	XMFLOAT4X4 fInv = pCamera->GetViewMatrix();
	XMMATRIX matInv = XMMatrixTranspose( XMLoadFloat4x4(&fInv) );
	XMStoreFloat4x4(&fInv, matInv);
	fInv._41 = 0.0f;
	fInv._42 = 0.0f;
	fInv._43 = 0.0f;
	matInv = XMMatrixInverse(nullptr, XMLoadFloat4x4(&fInv));
	XMStoreFloat4x4(&fInv, matInv);


	// ビュー行列
	XMFLOAT4X4 fView = pCamera->GetViewMatrix();

	// プロジェクション行列
	XMFLOAT4X4 fProj = pCamera->GetProjectionMatrix();

	// ワールド行列
	XMFLOAT4X4 fWorld;
	XMMATRIX T = XMMatrixTranslation(pos.x, pos.y, pos.z);
	XMMATRIX matWorld = matInv * T;
	XMStoreFloat4x4(&fWorld, XMMatrixTranspose(matWorld));


	// スプライトの設定
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	Sprite::SetSize(size);
	Sprite::SetUVPos(uvPos);
	Sprite::SetUVScale(uvScale);
	Sprite::SetColor(color);
	Sprite::SetTexture(pptex);
	Sprite::Draw();
}
