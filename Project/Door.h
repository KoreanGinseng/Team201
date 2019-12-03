#pragma once
#include "Empty.h"
class Door:public CEmpty
{
public:
	Door();
	~Door();
	void Initialize(void){}
	bool Load(void) { return true; }
	void Update(const bool& me);
	CRectangle GetRect(const Vector2& pos, const CRectangle& src) const {
	return CRectangle(pos.x, pos.y, pos.x + src.GetWidth(), pos.y + src.GetHeight());
	}
	int GetType(void) const { return OBJECT_DOOR; }
};