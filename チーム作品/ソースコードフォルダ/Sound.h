//-------------------------------------------------------------
//�@���e�FBGM�N���X�ASE�N���X
//
//�@�N���X�P�ʂ�BGM�ESE���������Ƃ��ł��܂�
//
//�@delete ��Y���ƁA�Ƃ�ł��Ȃ��ʂ̃��������[�N��
//�@�������鋰�ꂪ����̂ŋC��t���Ă�������
//�@
//�@�����Ƃ� wav�t�@�C�� �����ǂݍ��߂Ȃ��̂ŁA
//�@mp3�Ȃǂ�ǂݍ��݂����ꍇ��
//�@�@https://online-audio-converter.com/ja/
//�@�� wav�t�@�C�� �ɕϊ����Ă�������
//
//�@BGM�̃v���O������
//�@�@BGM* bgm = new BGM("Sounds/bgm.wav", true);
//�@�@bgm->Start();�@�@�@�@�@Sleep(10000);
//�@�@bgm->SetVolume(0.5f);�@Sleep(10000);
//�@�@bgm->Stop();
//�@�@delete bgm;
//
//�@SE�̃v���O������
//�@�@SE* se = new SE("Sounds/se.wav");
//�@�@se->Play();�@Sleep(500);
//�@�@se->Play();�@Sleep(500);
//�@�@se->Play();
//�@�@delete se;
//-------------------------------------------------------------

#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <stdio.h>
#include <tchar.h>
#include <stdint.h>
#include <xaudio2.h>
#include <list>
#include <atlbase.h>

#pragma comment(lib, "xaudio2.lib")

#ifdef _XBOX
#define fourccRIFF 'RIFF'
#define fourccData 'data'
#define fourccFMT  'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccWSMP 'wsmp'
#define fourccSMPL 'smpl'
#define fourccDPDS 'dpds'
#define fourccSEEK 'seek'
#endif // _XBOX

#ifndef _XBOX
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT  ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccWSMP 'pmsw'
#define fourccSMPL 'lpms'
#define fourccDPDS 'sdpd'
#define fourccSEEK 'kees'
#endif // !_XBOX




//-----------------------------------
//�@����2�͕K���Ăяo���Ă�������
//-----------------------------------
HRESULT InitXAudio2();
void UninitXAudio2();

HRESULT _FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
HRESULT _ReadChunkData(HANDLE hFile, void* buffer, DWORD dwBufferSize, DWORD dwBufferOffset);
CComPtr<IXAudio2> _GetXAudio2();
IXAudio2MasteringVoice* _GetMasteringVoice();



class BGM
{
public:
	//�R���X�g���N�^
	//	LPCSTR filePath : �����t�@�C���̃p�X
	//	bool loop (=false) : ���[�v�ݒ�(�ȗ���)
	BGM(LPCSTR filePath, bool loop = false);

	//�f�X�g���N�^
	~BGM();

	//�Đ��J�n
	void Start();

	//�Đ��I��
	void Stop();

	//�{�����[���ݒ�
	//	float volume : �{�����[��(0.0f �` 1.0f)
	void SetVolume(float volume);

	//�X�s�[�h�ݒ�
	//	float pitch : �X�s�[�h(0.01f �` 2.0f ���炢)
	void SetPitch(float pitch);

private:
	WAVEFORMATEXTENSIBLE m_wfx{ 0 };
	XAUDIO2_BUFFER m_buffer{ 0 };
	IXAudio2SourceVoice* m_pSourceVoice;
};


class SE
{
public:
	//�R���X�g���N�^
	//	LPCSTR filePath : �����t�@�C���ւ̃p�X
	SE(LPCSTR filePath);

	//�f�X�g���N�^
	~SE();

	//�Đ�
	void Play();

	//�{�����[���ݒ�
	//	float volume : �{�����[��(0.0f �` 1.0f)
	void SetVolume(float volume);

	//�X�s�[�h�ݒ�
	//	float pitch : �X�s�[�h(0.01f �` 2.0f ���炢)
	void SetPitch(float pitch);


	static void _Destroy();	//SE�S�폜

private:
	WAVEFORMATEXTENSIBLE m_wfx{ 0 };
	XAUDIO2_BUFFER m_buffer{ 0 };
	IXAudio2SourceVoice* m_pSourceVoice;

	float m_volume;
	float m_pitch;

	static std::list<IXAudio2SourceVoice*> m_pDestroyVoiceList;
	static std::list<const BYTE*> m_pDestroyBufferList;

private:
	static void Remove(IXAudio2SourceVoice* voice); //�w��|�C���^��SE�폜
};


#endif // !___SOUND_H___

