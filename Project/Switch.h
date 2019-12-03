#pragma once
#include "Empty.h"	
class CSwitch: public CEmpty
{
private:
	float m_bswitch;
public:
	CSwitch();
	~CSwitch();
	void Initialize(void);
	bool Load(void);
	void Update(const bool& me);
	CRectangle GetRect (const Vector2& pos, const CRectangle& src) const {
		CRectangle rect(pos.x, pos.y, pos.x + src.GetWidth(), pos.y + src.GetHeight());
		return rect;
	}

	bool Getste(void) { return m_bswitch; }
	void SetSwitch(bool b);
	
	int GetType(void) const { return OBJECT_SWITCH; }

};

