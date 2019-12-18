#pragma once

#include	"Effect.h"

#define		EFFECTCOUNT		1

class CEffectManager {

private:

	CEffect		m_Effect[EFFECTCOUNT][EFC_TYPECOUNT];

	CTexturePtr	m_Texture[EFC_TYPECOUNT];

	CEffectManager() = default;
	~CEffectManager() = default;
public:
	bool		Load(void);
	void		Initialize(void);
	CEffect*	Start(float px, float py, int type);
	void		Update(void);
	void		Render(Vector2 scroll);
	void		Release(void);
	static CEffectManager* GetInstance(void) {
		static CEffectManager obj;
		return &obj;
	}
};

#define		g_pEffectManager		CEffectManager::GetInstance()