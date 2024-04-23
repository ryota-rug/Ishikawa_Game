#include "Sound.h"


static CComPtr<IXAudio2> pXAudio2;
static IXAudio2MasteringVoice* pMasteringVoice;


HRESULT _FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
HRESULT _ReadChunkData(HANDLE hFile, void* buffer, DWORD dwBufferSize, DWORD dwBufferOffset);




HRESULT InitXAudio2()
{
	HRESULT hr;

	//XAudio2の初期化
	hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr))
	{
		MessageBox(NULL, "XAudio2の初期化に失敗", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	//マスターボイスの作成
	hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(NULL, "マスターボイスの作成に失敗", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	return hr;
}

void UninitXAudio2()
{
	//マスターボイスの削除
	pMasteringVoice->DestroyVoice();

	//XAudio2の終了
	pXAudio2.Release();
}



//_FindChunk() : RIFFファイルでチャンクを検索する
// ファイルへのポインタ : HANDLE hFile
// データフォーマット : DWORD fourcc
// チャンクのサイズ : DWORD& dwChunkSize
// チャンクの場所 : DWORD& dwChunkDataPosition
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
		case fourccRIFF: //RIFFファイル
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;

			if (!(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL)))
			{
				hr = HRESULT_FROM_WIN32(GetLastError());
			}

			break;

		default: //その他のファイル
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


//_ReadChunkData() : チャンクからデータを読み取る
// ファイルへのポインタ : HANDLE hFile
// バッファーへのポインタ : void* buffer
// バッファーのサイズ : DWORD dwBifferSize
// バッファーの距離 : DWORD dwBufferOffset
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