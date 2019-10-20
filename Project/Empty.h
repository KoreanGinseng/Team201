#pragma once
#include	"GameDefine.h"

class CEmpty
{
public:
	CEmpty();
	~CEmpty();
	virtual void Update(const bool& me) = 0;
	virtual CRectangle GetRect(const Vector2& pos, const CRectangle& src) const = 0;/* {
		CRectangle rect(pos.x, pos.y, pos.x + src.GetWidth(), pos.y + src.GetHeight());
		return rect;
	}*/
};

