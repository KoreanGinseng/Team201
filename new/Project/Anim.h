#pragma once
#include	"GameDefine.h"

class CAnim
{
private:
	CRectangle		m_SrcRect;
public:
	CAnim() {}
	~CAnim() {}
	CRectangle	GetRect(void) const { return m_SrcRect; }
};

