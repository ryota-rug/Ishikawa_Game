#include "Sound.h"


static CComPtr<IXAudio2> pXAudio2;
static IXAudio2MasteringVoice* pMasteringVoice;


HRESULT _FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
HRESULT _ReadChunkData(HANDLE hFile, void* buffer, DWORD dwBufferSize, DWORD dwBufferOffset);




HRESULT InitXAudio2()
{
	HRESULT hr;

	//XAudio2�̏�����
	hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr))
	{
		MessageBox(NULL, "XAudio2�̏������Ɏ��s", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	//�}�X�^�[�{�C�X�̍쐬
	hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�}�X�^�[�{�C�X�̍쐬�Ɏ��s", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	return hr;
}

void UninitXAudio2()
{
	//�}�X�^�[�{�C�X�̍폜
	pMasteringVoice->DestroyVoice();

	//XAudio2�̏I��
	pXAudio2.Release();
}



//_FindChunk() : RIFF�t�@�C���Ń`�����N����������
// �t�@�C���ւ̃|�C���^ : HANDLE hFile
// �f�[�^�t�H�[�}�b�g : DWORD fourcc
// �`�����N�̃T�C�Y : DWORD& dwChunkSize
// �`�����N�̏ꏊ : DWORD& dwChunkDataPosition
HRESULT _FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;

		if (!(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL)))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (!(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL)))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case fourccRIFF: //RIFF�t�@�C��
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;

			if (!(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL)))
			{
				hr = HRESULT_FROM_WIN32(GetLastError());
			}

			break;

		default: //���̑��̃t�@�C��
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
			{
				return HRESULT_FROM_WIN32(GetLastError());
			}

			break;
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) { return S_FALSE; }
	}

	return S_OK;
}


//_ReadChunkData() : �`�����N����f�[�^��ǂݎ��
// �t�@�C���ւ̃|�C���^ : HANDLE hFile
// �o�b�t�@�[�ւ̃|�C���^ : void* buffer
// �o�b�t�@�[�̃T�C�Y : DWORD dwBifferSize
// �o�b�t�@�[�̋��� : DWORD dwBufferOffset
HRESULT _ReadChunkData(HANDLE hFile, void* buffer, DWORD dwBufferSize, DWORD dwBufferOffset)
{
	HRESULT hr = S_OK;

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwBufferOffset, NULL, FILE_BEGIN))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD dwRead;
	if (!(ReadFile(hFile, buffer, dwBufferSize, &dwRead, NULL)))
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
	}

	return hr;
}



CComPtr<IXAudio2> _GetXAudio2() { return pXAudio2; }
IXAudio2MasteringVoice* _GetMasteringVoice(){ return pMasteringVoice; }