#pragma once

#include	"Effect.h"

#define		EFFECTCOUNT		1

class CEffectManager {

private:

	CEffect		m_Effect[EFFECTCOUNT][EFC_TYPECOUNT];

	CTexture	m_Texture[EFC_TYPECOUNT];

	CEffectManager() = default;
	~CEffectManager() = default;
	static CEffectManager* m_pInstance;

public:
				
				
	bool		Load(void);
	void		Initialize(void);
	CEffect*	Start(float px, float py, int type);
	void		Update(void);
	void		Render(Vector2 scroll);
	void		Release(void);

	static CEffectManager Create() { return CEffectManager(); }

	static CEffectManager* GetInstance() {

		if (m_pInstance == nullptr) {

			m_pInstance = new CEffectManager();
		}

		return m_pInstance;
	}

};

#define		g_pEffectManager		CEffectManager::GetInstance()