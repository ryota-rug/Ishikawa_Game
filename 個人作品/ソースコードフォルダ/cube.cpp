
#include "renderer.h"
#include "cube.h"
#include "CreateTexture.h"
#include "input.h"

namespace {
	DirectX::XMFLOAT3 g_Position[8] = {
		{-0.5f, -0.5f, -0.5f},	// �����O
		{ 0.5f, -0.5f, -0.5f},	// �E���O
		{-0.5f,  0.5f, -0.5f},	// ����O
		{ 0.5f,  0.5f, -0.5f},	// �E��O
		{-0.5f, -0.5f,  0.5f},	// ������
		{ 0.5f, -0.5f,  0.5f},	// �E����
		{-0.5f,  0.5f,  0.5f},	// �����
		{ 0.5f,  0.5f,  0.5f},	// �E���
	};
	DirectX::XMFLOAT3 g_Normal[6] = {
		{-1.0f,  0.0f,  0.0f},	// ��
		{ 1.0f,  0.0f,  0.0f},	// �E
		{ 0.0f, -1.0f,  0.0f},	// ��
		{ 0.0f,  1.0f,  0.0f},	// ��
		{ 0.0f,  0.0f, -1.0f},	// �O
		{ 0.0f,  0.0f,  1.0f},	// ��
	};
	DirectX::XMFLOAT4 g_Diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
	DirectX::XMFLOAT2 g_TexCoord[24] = {
		{0.0f, 0.0f},	// ���ʍ���
		{1.0f, 0.0f},	// ���ʉE��
		{0.0f, 1.0f},	// ���ʍ���
		{1.0f, 1.0f},	// ���ʉE��

		{0.0f, 0.0f},	// �E�ʍ���
		{1.0f, 0.0f},	// �E�ʉE��
		{0.0f, 1.0f},	// �E�ʍ���
		{1.0f, 1.0f},	// �E�ʉE��

		{0.0f, 0.0f},	// ���ʍ���
		{1.0f, 0.0f},	// ���ʉE��
		{0.0f, 1.0f},	// ���ʍ���
		{1.0f, 1.0f},	// ���ʉE��

		{0.0f, 0.0f},	// ��ʍ���
		{1.0f, 0.0f},	// ��ʉE��
		{0.0f, 1.0f},	// ��ʍ���
		{1.0f, 1.0f},	// ��ʉE��

		{0.0f, 0.0f},	// �O�ʍ���
		{1.0f, 0.0f},	// �O�ʉE��
		{0.0f, 1.0f},	// �O�ʍ���
		{1.0f, 1.0f},	// �O�ʉE��

		{0.0f, 0.0f},	// ��ʍ���
		{1.0f, 0.0f},	// ��ʉE��
		{0.0f, 1.0f},	// ��ʍ���
		{1.0f, 1.0f},	// ��ʉE��
	};
	UINT g_Taple[24 /* *3 */] = {
		6, //0,  0,
		2, //0,  1,
		4, //0,  2,
		0, //0,  3,

		3, //1,  4,
		7, //1,  5,
		1, //1,  6,
		5, //1,  7,

		0, //2,  8,
		1, //2,  9,
		4, //2, 10,
		5, //2, 11,

		6, //3, 12,
		7, //3, 13,
		2, //3, 14,
		3, //3, 15,

		2, //4, 16,
		3, //4, 17,
		0, //4, 18,
		1, //4, 19,

		7, //5, 20,
		6, //5, 21,
		5, //5, 22,
		4, //5, 23,
	};
}

void Cube::Init(const char* TextureName)
{
	VERTEX_3D vertex[24];
	for (int i = 0; i < 24; ++i) {
		vertex[i].Position = g_Position[g_Taple[i]];
		vertex[i].Normal = g_Normal[i / 4];
		vertex[i].Diffuse = g_Diffuse;
		vertex[i].TexCoord = g_TexCoord[i];
	}

	UINT index[36] = {
		 0,  1,  2,  2,  1,  3,
		 4,  5,  6,  6,  5,  7,
		 8,  9, 10, 10,  9, 11,
		12, 13, 14, 14, 13, 15,
		16, 17, 18, 18, 17, 19,
		20, 21, 22, 22, 21, 23,
	};

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( VERTEX_3D ) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer( &bd, &sd, &m_VertexBuffer );


	// �C���f�b�N�X�o�b�t�@����
	//D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(UINT) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = index;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);


	// �e�N�X�`���ǂݍ���
	CreateTextureFromFile(Renderer::GetDevice(), TextureName, &m_Texture);
	assert( m_Texture );

}


void Cube::Uninit()
{

	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();

}


void Cube::Draw()
{

	// ���_/�C���f�b�N�X �o�b�t�@�ݒ�
	UINT stride = sizeof( VERTEX_3D );
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory( &material, sizeof(material) );
	material.Diffuse = DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
	material.TextureEnable = TRUE;
	Renderer::SetMaterial( material );

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// �|���S���`��
	Renderer::GetDeviceContext()->DrawIndexed( 36, 0, 0 );

}
