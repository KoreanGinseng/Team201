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
		return CRectangle(pos.x, pos.y, pos.x + src.GetWidth(), pos.y + src.GetHeight());
	}
	int GetType(void) const { return OBJECT_MOVE; }
};