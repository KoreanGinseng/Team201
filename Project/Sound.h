#pragma once

#include		"Mof.h"

/*�T�E���h�̎��*/
enum tag_SOUNDTYPE {

	SUD_SOUNDEFFECT,SUD_SOUNDBGM, SUD_TYPECOUNT

};

/*�T�E���h���w��(BGM�Ȃ烋�[�v)*/
enum tag_SOUND {

	SOUND_EFFECT, SOUND_BGM,

};

/*�X�g�b�v�̎��*/
enum tag_STOPTYPE {

	STOP_SUDDEN,STOP_GRADUALLY,

};

class CSound {

private:
	CSoundBuffer*	m_pSound;
	bool			m_bLoop;
	bool			m_bPlay;
	bool			m_bStop;
	float			m_Volume;

public:
	CSound();
	~CSound();
	void	Initialize(void);
	void	Start(bool loop);
	void	Update(void);
	void	Stop(int stopType);
	void	SetSound(CSoundBuffer* ps) { m_pSound = ps; }
	bool	IsPlay(void) {return m_bPlay;}
};