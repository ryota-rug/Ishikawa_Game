#include "SpriteManager.h"
#include "DirectXTex/Texture.h"

using namespace std;
using namespace DirectX;


//----- �萔��` -----
const float WindowLeft(0.0f);       // ��ʍ��[�̍��W
const float WindowRight(1280.0f);	// ��ʉE�[�̍��W
const float WindowBottom(720.0f);	// ��ʉ��[�̍��W
const float WindowTop(0.0f);        // ��ʏ�[�̍��W
const float NearZ(-1.0f);           // Z�����Ŏʂ���ŏ��l
const float FarZ(1.0f);             // Z�����Ŏʂ���ő�l

BlendState* SpriteManager::m_pBlend;


//--------------------
// �R���X�g���N�^
//--------------------
SpriteManager::SpriteManager()
{
	m_pSampler = new SamplerState;
}


//--------------------
// �f�X�g���N�^
//--------------------
SpriteManager::~SpriteManager()
{
	delete m_pSampler;
}


//-------------------------
// 2D�`��̐ݒ�
//-------------------------
void SpriteManager::Init()
{
	m_pBlend = new BlendState;

	// �u�����h�X�e�[�g
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
// �e�N�X�`���̉��
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
// �`��
//--------------------
void SpriteManager::Draw
(
	DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 angle,
	DirectX::XMFLOAT2 uvPos, DirectX::XMFLOAT2 uvScale,
	DirectX::XMFLOAT4 color,
	ID3D11ShaderResourceView* pptex
)
{
	// �r���[�s��
	XMFLOAT4X4 fView;
	XMStoreFloat4x4(&fView, XMMatrixIdentity());   // �P�ʍs����쐬

	// �v���W�F�N�V�����s��
	XMFLOAT4X4 fProj;
	XMMATRIX matProj = XMMatrixOrthographicOffCenterLH(WindowLeft, WindowRight, WindowBottom, WindowTop, NearZ, FarZ);
	XMStoreFloat4x4(&fProj, XMMatrixTranspose(matProj));

	// ���[���h�s��
	// ��ʂ̉𑜓x�����ɑ傫���ƕ\���ʒu���v�Z
	XMFLOAT4X4 fWorld;
	XMMATRIX T  = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	XMMATRIX Rx = XMMatrixRotationX(XMConvertToRadians(angle.x));
	XMMATRIX Ry = XMMatrixRotationY(XMConvertToRadians(angle.y));
	XMMATRIX Rz = XMMatrixRotationZ(XMConvertToRadians(angle.z));
	XMMATRIX S  = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX matWorld = S * Rx * Ry * Rz * T;
	XMStoreFloat4x4(&fWorld, XMMatrixTranspose(matWorld));


	// �X�v���C�g�̐ݒ�
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
// �r���{�[�h�`��
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
	// �J�����̃r���[�t�s��
	XMFLOAT4X4 fInv = pCamera->GetViewMatrix();
	XMMATRIX matInv = XMMatrixTranspose( XMLoadFloat4x4(&fInv) );
	XMStoreFloat4x4(&fInv, matInv);
	fInv._41 = 0.0f;
	fInv._42 = 0.0f;
	fInv._43 = 0.0f;
	matInv = XMMatrixInverse(nullptr, XMLoadFloat4x4(&fInv));
	XMStoreFloat4x4(&fInv, matInv);


	// �r���[�s��
	XMFLOAT4X4 fView = pCamera->GetViewMatrix();

	// �v���W�F�N�V�����s��
	XMFLOAT4X4 fProj = pCamera->GetProjectionMatrix();

	// ���[���h�s��
	XMFLOAT4X4 fWorld;
	XMMATRIX T = XMMatrixTranslation(pos.x, pos.y, pos.z);
	XMMATRIX matWorld = matInv * T;
	XMStoreFloat4x4(&fWorld, XMMatrixTranspose(matWorld));


	// �X�v���C�g�̐ݒ�
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
