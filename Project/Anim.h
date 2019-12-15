#pragma once
#include	"GameDefine.h"

class CAnim
{
private:
	CSpriteMotionController*	m_pAnim;
public:
	CAnim() { m_pAnim = nullptr; }
	~CAnim() {}
	CRectangle	GetRect(void) const { return m_pAnim->GetSrcRect(); }
	void Initialize(void);
	void Update(void);
	void Create(const char* pName);
	void ChangeAnim(const int& animNo) { m_pAnim->ChangeMotion(animNo); }
	int  GetMotionNo(void) const { return m_pAnim->GetMotionNo(); }
	bool IsEndMotion(void) const { return m_pAnim->IsEndMotion(); }
	void Release(void) { NewPointerRelease(m_pAnim); }
};

