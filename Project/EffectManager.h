#pragma once

#include	"Effect.h"

#define		EFFECTCOUNT		100

class CEffectManager {

private:

	CEffect		m_Effect[EFFECTCOUNT][EFFECT_TYPECOUNT];

	CTexturePtr	m_Texture[EFFECT_TYPECOUNT];

	CEffectManager() = default;
	~CEffectManager() = default;
public:
	bool		Load(void);
	void		Initialize(void);
	CEffect*	Start(float px, float py, int type);
	void		Update(void);
	void		Render(const Vector2& scroll);
	void		Release(void);
	static CEffectManager* GetInstance(void) {
		static CEffectManager obj;
		return &obj;
	}
};

#define		g_pEffectManager		CEffectManager::GetInstance()