#pragma once
#include	"GameDefine.h"

class CAnimationData
{
private:
	CTexturePtr	m_pTexture;
	SpriteAnimationCreate* m_pAnim;
	int			m_AnimCount;
public:
	CAnimationData(void);
	~CAnimationData(void);
	bool Load(const char* pName);
	CTexturePtr GetTexture(void) { return m_pTexture; }
	SpriteAnimationCreate* GetAnim(void) { return m_pAnim; }
	int GetAnimCount(void) const { return m_AnimCount; }
	void Release(void);
};

