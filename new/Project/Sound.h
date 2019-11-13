#pragma once

#include		"Mof.h"

/*サウンドの種類*/
enum tag_SOUNDTYPE {

	SUD_SOUNDEFFECT,SUD_SOUNDBGM, SUD_TYPECOUNT

};

/*サウンドを指定(BGMならループ)*/
enum tag_SOUND {

	SOUND_EFFECT, SOUND_BGM,

};

/*ストップの種類*/
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