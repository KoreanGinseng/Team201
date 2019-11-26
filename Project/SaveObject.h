#pragma once
#include "Empty.h"
class CSaveObject :
	public CEmpty
{
private:
	

public:
	CSaveObject();
	~CSaveObject();
	void Initialize(void);
	bool Load(void);
	void Update(const bool& me);
	CRectangle GetRect(const Vector2& pos, const CRectangle& src) const {
		CRectangle rect(pos.x, pos.y, pos.x + src.GetWidth(), pos.y + src.GetHeight());
		rect.Expansion(-128, -128);
		rect.Top += 64;
		rect.Bottom = rect.Top + 96;
		rect.Right -= 16;
		return rect;
	}
	int GetType(void) const { return OBJECT_SAVE; }

};

