#include "Sound.h"



CSound::CSound(void) :
m_pSound(nullptr),
m_bPlay(false)
{
}


CSound::~CSound(void)
{
}

CSoundBuffer * CSound::GetSoundBuffer(void)
{
	return m_pSound;
}

bool CSound::IsPlay(void) const
{
	return m_bPlay;
}

void CSound::Play(void)
{
	m_pSound->Play();
	m_bPlay = true;
}

bool CSound::Load(const std::string & str)
{
	m_pSound = new CSoundBuffer();
	if (!m_pSound->Load(str.c_str()))
	{
		return false;
	}
	return true;
}

void CSound::Update(void)
{
	//�Đ��t���O�������Ă��Ȃ��ꍇ�X�L�b�v
	if (!m_bPlay)
	{
		return;
	}
	//�Đ��I�����Ă���Ȃ�t���O��܂�
	if (!m_pSound->IsPlay())
	{
		m_bPlay = false;
	}
}

void CSound::Release(void)
{
	m_pSound->Release();
	MOF_SAFE_DELETE(m_pSound);
}
