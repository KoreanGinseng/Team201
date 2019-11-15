#pragma once
#include	"GameDefine.h"

class CAnim
{
private:
	CSpriteMotionController*	m_pAnim;
	CRectangle					m_SrcRect;
public:
	CAnim() {}
	~CAnim() {}
	CRectangle	GetRect(void) const { return m_SrcRect; }
	void Initialize(void);
	void Update(void);
	void Create(const char* pName);
	void ChangeAnim(const int& animNo) { m_pAnim->ChangeMotion(animNo); }
	void Release(void) { NewPointerRelease(m_pAnim); }
};

