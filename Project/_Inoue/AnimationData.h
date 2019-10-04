#pragma once
#include	"../GameDefine.h"

class CAnimationData
{
private:
	CTexturePtr	m_pTexture;
	CMotionPtr	m_pMotion;
public:
	CAnimationData(void);
	~CAnimationData(void);
	bool Load(const char* pName);
	CTexturePtr GetTexture(void) { return m_pTexture; }
	CMotionPtr GetMotion(void) { return m_pMotion; }
	void Release(void);
};

