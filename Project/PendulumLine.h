#pragma once

#include "Empty.h"

class CPendulumLine :
	public CEmpty
{

private:


public:
	CPendulumLine();
	~CPendulumLine();
	void Initialize(void);
	bool Load(void);
	void Update(const bool& me);
	CRectangle GetRect(const Vector2& pos, const CRectangle& src) const {
		return CRectangle(pos.x, pos.y, pos.x + src.GetWidth(), pos.y + src.GetHeight());
	}
	float GetCenterDown(float width) { GetRect().GetCenter + GetRect().Bottom; }
	int GetType(void) const { return OBJECT_MOVE; }
};