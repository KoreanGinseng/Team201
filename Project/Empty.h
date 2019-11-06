#pragma once
#include	"GameDefine.h"
#include	"Mof.h"

class CEmpty
{
protected:
	int			m_RectCount;
	CRectangle	m_Rect;
	CRectangle* m_pRect;
public:
	CEmpty();
	~CEmpty();
	virtual void Initialize(void) = 0;
	virtual bool Lood(void) = 0;
	virtual void Update(const bool& me) = 0;
	virtual CRectangle GetRect(const Vector2& pos, const CRectangle& src) const = 0;
	virtual int GetType(void) const = 0;
};

