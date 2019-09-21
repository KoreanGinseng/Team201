#pragma once

#include		"Sound.h"

#define		SOUNDCOUNT		1

class CSoundManager {

private:

	CSound			m_CSound[SOUNDCOUNT][SUD_TYPECOUNT];
	CSoundBuffer	m_Sound[SUD_TYPECOUNT];

public:
	CSoundManager();
	~CSoundManager();
	bool		Load(void);
	void		Initialize(void);
	void		Update(void);
	void		Release(void);
	
	CSound*		Start(int type,int loop);
	void		Stop(int type,int stopType);
};