//-------------------------------------------------------------
//　内容：BGMクラス、SEクラス
//
//　クラス単位でBGM・SEを扱うことができます
//
//　delete を忘れると、とんでもない量のメモリリークが
//　発生する恐れがあるので気を付けてください
//　
//　両方とも wavファイル しか読み込めないので、
//　mp3などを読み込みたい場合は
//　　https://online-audio-converter.com/ja/
//　で wavファイル に変換してください
//
//　BGMのプログラム例
//　　BGM* bgm = new BGM("Sounds/bgm.wav", true);
//　　bgm->Start();　　　　　Sleep(10000);
//　　bgm->SetVolume(0.5f);　Sleep(10000);
//　　bgm->Stop();
//　　delete bgm;
//
//　SEのプログラム例
//　　SE* se = new SE("Sounds/se.wav");
//　　se->Play();　Sleep(500);
//　　se->Play();　Sleep(500);
//　　se->Play();
//　　delete se;
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
//　この2つは必ず呼び出してください
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
	//コンストラクタ
	//	LPCSTR filePath : 音声ファイルのパス
	//	bool loop (=false) : ループ設定(省略可)
	BGM(LPCSTR filePath, bool loop = false);

	//デストラクタ
	~BGM();

	//再生開始
	void Start();

	//再生終了
	void Stop();

	//ボリューム設定
	//	float volume : ボリューム(0.0f ～ 1.0f)
	void SetVolume(float volume);

	//スピード設定
	//	float pitch : スピード(0.01f ～ 2.0f ぐらい)
	void SetPitch(float pitch);

private:
	WAVEFORMATEXTENSIBLE m_wfx{ 0 };
	XAUDIO2_BUFFER m_buffer{ 0 };
	IXAudio2SourceVoice* m_pSourceVoice;
};


class SE
{
public:
	//コンストラクタ
	//	LPCSTR filePath : 音声ファイルへのパス
	SE(LPCSTR filePath);

	//デストラクタ
	~SE();

	//再生
	void Play();

	//ボリューム設定
	//	float volume : ボリューム(0.0f ～ 1.0f)
	void SetVolume(float volume);

	//スピード設定
	//	float pitch : スピード(0.01f ～ 2.0f ぐらい)
	void SetPitch(float pitch);


	static void _Destroy();	//SE全削除

private:
	WAVEFORMATEXTENSIBLE m_wfx{ 0 };
	XAUDIO2_BUFFER m_buffer{ 0 };
	IXAudio2SourceVoice* m_pSourceVoice;

	float m_volume;
	float m_pitch;

	static std::list<IXAudio2SourceVoice*> m_pDestroyVoiceList;
	static std::list<const BYTE*> m_pDestroyBufferList;

private:
	static void Remove(IXAudio2SourceVoice* voice); //指定ポインタのSE削除
};


#endif // !___SOUND_H___

