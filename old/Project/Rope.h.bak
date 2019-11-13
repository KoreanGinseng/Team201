#pragma once
#include "Empty.h"
class CRope :
	public CEmpty
{
public:
	CRope();
	~CRope();
	void Update(const bool& me);
	CRectangle GetRect(const Vector2& pos, const CRectangle& src) const {
		CRectangle rect(pos.x, pos.y, pos.x + src.GetWidth(), pos.y + src.GetHeight());
		rect.Expansion(-64, 0);
		rect.Right -= 64;
		rect.Left = rect.Right - 64;
		return rect;
	}
	int GetType(void) const { return OBJECT_ROPE; }
};

