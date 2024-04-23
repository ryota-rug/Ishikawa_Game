#include "Sound.h"



BGM::BGM(LPCSTR filePath, bool loop)
{
	HRESULT hr;

	//�I�[�f�B�I�t�@�C�����J��
	HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ | XAUDIO2_VOICE_NOSRC, NULL, OPEN_EXISTING, 0, NULL);
	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);


	//�t�@�C���̎�ނ��m�F
	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	_FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);

	DWORD dwFileType;
	_ReadChunkData(hFile, &dwFileType, sizeof(DWORD), dwChunkPosition);
	

	//fmt�`�����N �� WAVEFORMATEXTENSIBLE�\���� �ɃR�s�[
	_FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	_ReadChunkData(hFile, &m_wfx, dwChunkSize, dwChunkPosition);


	//data�`�����N ���o�b�t�@�[�ɓǂݎ��
	_FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	
	BYTE* pDataBuffer = new BYTE[dwChunkSize];
	_ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
	

	//XAUDIO2_BUFFER�\���� �ɒl��ݒ�
	m_buffer.AudioBytes = dwChunkSize; //�I�[�f�B�I�o�b�t�@�[�̃T�C�Y(�o�C�g�P��)
	m_buffer.pAudioData = pDataBuffer; //�o�b�t�@�[�Ƀf�[�^���i�[
	m_buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (loop) { m_buffer.LoopCount = XAUDIO2_LOOP_INFINITE; }


	//�\�[�X�������쐬
	hr = _GetXAudio2()->CreateSourceVoice(&m_pSourceVoice, (WAVEFORMATEX*)&m_wfx);
	if (FAILED(hr))
	{
		MessageBox(NULL, "SourceVoice�̍쐬�Ɏ��s", "BGM.cpp", MB_OK | MB_ICONERROR);
	}

	//�\�[�X������ XAUDIO2_BUFFER �𑗐M
	hr = m_pSourceVoice->SubmitSourceBuffer(&m_buffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, "XAUDIO2_BUFFER�̑��M�Ɏ��s", "BGM.cpp", MB_OK | MB_ICONERROR);
	}
}

BGM::~BGM()
{
	m_pSourceVoice->FlushSourceBuffers();
	delete m_buffer.pAudioData;
	m_pSourceVoice->DestroyVoice();
}



void BGM::Start()
{
	m_pSourceVoice->Start();
}

void BGM::Stop()
{
	m_pSourceVoice->Stop();
}

void BGM::SetVolume(float volume)
{
	if (volume < 0) { volume = 0; }
	if (volume > 1) { volume = 1; }

	m_pSourceVoice->SetVolume(volume);
}

void BGM::SetPitch(float pitch)
{
	m_pSourceVoice->SetFrequencyRatio(pitch);
}

