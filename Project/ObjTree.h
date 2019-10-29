#pragma once
#include "Empty.h"
class CObjTree :
	public CEmpty
{
public:
	CObjTree();
	~CObjTree();
	int GetType(void) const { return OBJECT_TREE01; }
	void Update(const bool& me);
	CRectangle GetRect(const Vector2& pos, const CRectangle& src) const {
		return CRectangle(pos.x, pos.y, pos.x + src.GetWidth(), pos.y + src.GetHeight());
	}
};

