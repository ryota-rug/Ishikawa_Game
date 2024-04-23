#include "Sound.h"

std::list<IXAudio2SourceVoice*> SE::m_pDestroyVoiceList;
std::list<const BYTE*> SE::m_pDestroyBufferList;




SE::SE(LPCSTR filePath) :
	m_volume(1.0f),
	m_pitch(1.0f)
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

	m_pDestroyVoiceList.push_back(m_pSourceVoice);
	m_pDestroyBufferList.push_back(m_buffer.pAudioData);
}

SE::~SE()
{
}

void SE::Play()
{
	Remove(m_pSourceVoice);

	_GetXAudio2()->CreateSourceVoice(&m_pSourceVoice, (WAVEFORMATEX*)&m_wfx);
	m_pSourceVoice->SubmitSourceBuffer(&m_buffer);
	m_pDestroyVoiceList.push_back(m_pSourceVoice);

	m_pSourceVoice->SetVolume(m_volume);
	m_pSourceVoice->SetFrequencyRatio(m_pitch);

	m_pSourceVoice->Start();
}

void SE::SetVolume(float volume)
{
	if (volume < 0) { m_volume = 0; }
	if (volume > 1) { m_volume = 1; }

	m_pSourceVoice->SetVolume(m_volume);
}

void SE::SetPitch(float pitch)
{
	m_pitch = pitch;
	m_pSourceVoice->SetFrequencyRatio(m_pitch);
}



void SE::_Destroy()
{
	for (auto it = m_pDestroyVoiceList.begin(); it != m_pDestroyVoiceList.end();)
	{
		(*it)->Stop();
		(*it)->FlushSourceBuffers();
		(*it)->DestroyVoice();
		it = m_pDestroyVoiceList.erase(it);
	}

	for (auto it = m_pDestroyBufferList.begin(); it != m_pDestroyBufferList.end();)
	{
		delete *it;
		it = m_pDestroyBufferList.erase(it);
	}

}

void SE::Remove(IXAudio2SourceVoice* voice)
{
	for (auto it = m_pDestroyVoiceList.begin(); it != m_pDestroyVoiceList.end(); it++)
	{
		if (*it == voice)
		{
			(*it)->Stop();
			(*it)->FlushSourceBuffers();
			(*it)->DestroyVoice();
			m_pDestroyVoiceList.erase(it);
			break;
		}
	}
}
