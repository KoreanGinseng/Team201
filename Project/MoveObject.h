#pragma once

#include "Empty.h"

class CMoveObject :
	public CEmpty
{

private:

	Vector2		m_Pos;
	Vector2		m_Move;

public:
	CMoveObject();
	~CMoveObject();
	void Initialize(void);
	bool Load(void);
	void Update(const bool& me);
	CRectangle GetRect(const Vector2& pos, const CRectangle& src) const {
		return CRectangle(pos.x, pos.y, pos.x + src.GetWidth(), pos.y + src.GetHeight());
	}
	int GetType(void) const { return OBJECT_MOVE; }
};