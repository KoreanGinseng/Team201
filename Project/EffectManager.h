#pragma once

#include	"Effect.h"

#define		EFFECTCOUNT		1

class CEffectManager {

private:

	CEffect		m_Effect[EFFECTCOUNT][EFC_TYPECOUNT];

	CTexture	m_Texture[EFC_TYPECOUNT];
public:
				CEffectManager();
				~CEffectManager();
	bool		Load(void);
	void		Initialize(void);
	CEffect*	Start(float px, float py, int type);
	void		Update(void);
	void		Render(Vector2 scroll);
	void		Release(void);
};