#pragma once
#include	"GameDefine.h"

class CSceneEffectBase
{
protected:
	bool	m_bStart[2];
	bool	m_bEnd;
	int		m_Alpha;
	int		m_Spd;
	CTexturePtr m_pMaskTexture;
public:
	CSceneEffectBase();
	virtual	~CSceneEffectBase();
	bool    Frame(void);
	bool	IsEnd(void) const { return m_bEnd; }
	bool	IsStart(void) const { return (m_bStart[0] || m_bStart[1]); }
	virtual bool In(const int& spd) = 0;
	virtual bool Out(const int& spd) = 0;
	virtual bool Render(void) = 0;
};

#include	"EffectFade.h"