#pragma once

#include "Empty.h"

class CPendulumBlock :
	public CEmpty
{

private:

public:
	CPendulumBlock();
	~CPendulumBlock();
	void Initialize(void);
	bool Load(void);
	void Update(const bool& me);
	CRectangle GetRect(const Vector2& pos, const CRectangle& src) const {
		return CRectangle(pos.x-src.GetWidth()/2, pos.y-src.GetHeight()/2, pos.x + src.GetWidth()/2, pos.y + src.GetHeight()/2);
	}
	int GetType(void) const { return OBJECT_MOVE; }
};