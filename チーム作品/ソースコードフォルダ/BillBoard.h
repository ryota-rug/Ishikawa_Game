#ifndef ___BILLBOARD_H___
#define ___BILLBOARD_H___

#include "DirectX.h"
#include "SpriteManager.h"
#include "DirectXTex/Texture.h"
#include <map>

#include "CameraManager_Game.h"
#include "CameraBase.h"


class BillBoard
{
public:
	DirectX::XMFLOAT3 pos;		// ���S���W
	DirectX::XMFLOAT2 size;		// �傫��
	DirectX::XMFLOAT4 color;	// �F
	int texNum;	//�e�N�X�`���ԍ�

public:
	BillBoard(LPCSTR filePath, SpriteManager* pSM);
	~BillBoard();

	//�`��
	//���O��EnableDepth(false)���Ăяo���Ă�������
	void Draw();


	//�摜�̔��]
	//	bool reverseU : �������̔��]�t���O
	//		[true]  ���]����
	//		[false] ���]���Ȃ�
	//	bool reverseV : �c�����̔��]�t���O
	//		[true]  ���]����
	//		[false] ���]���Ȃ�
	void Reverse(bool reverseU, bool reverseV);


	//�e�N�X�`������
	//	float divisionU : �������̕�����
	//	float divisionV : �c�����̕�����
	void SetTexScale(float divisionU, float divisionV);

	//�A�j���[�V�����X�V
	//	UINT frame : �A�j���[�V�������X�V����Ԋu
	//	bool loop : �A�j���[�V�����̃��[�v�ݒ�
	void UpdateAnimation(UINT frame, bool loop = false);


	//�J�����̐ݒ�
	static void _SetCamera(CameraBase** ppCamera);

private:
	SpriteManager* m_pSpriteManager;	//�X�v���C�g�}�l�[�W��
	ID3D11ShaderResourceView* m_pImage;	//�C���[�W�\�[�X

	bool m_reverseU;	//�������̔��]�t���O
	bool m_reverseV;	//�c�����̔��]�t���O

	std::map<int, DirectX::XMFLOAT2> m_texPos;	//UV���W
	DirectX::XMFLOAT2 m_texScale;				//UV�̑傫��
	UINT m_divisionTexNum;						//�e�N�X�`��������

	UINT m_frame;	//�o�߃t���[����

	static CameraBase** m_ppCamera;	//���݂̃J�������
};


#endif // !___BILLBOARD_H___
