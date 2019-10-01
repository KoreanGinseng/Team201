#pragma once

#include		"Sound.h"

#define		SOUNDCOUNT		1

class CSoundManager {

private:

	CSound			m_CSound[SOUNDCOUNT][SUD_TYPECOUNT];
	CSoundBuffer	m_Sound[SUD_TYPECOUNT];

	CSoundManager() = default;
	~CSoundManager() = default;

	static CSoundManager* m_pInstance;
	
public:
	
	bool		Load(void);
	void		Initialize(void);
	void		Update(void);
	void		Release(void);
	
	CSound*		Start(int type,int loop);
	void		AllSetVolume(float volume);
	void		SetVolume(int type, float volume);
	void		Stop(int type,int stopType);

	float			RenderDebug(int type);

	static CSoundManager Create() { return CSoundManager(); }
	static CSoundManager* GetInstance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new CSoundManager();
		}
		return m_pInstance; }
};


#define g_pSoundManager		 CSoundManager::GetInstance()