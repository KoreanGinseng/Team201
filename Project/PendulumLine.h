#pragma once

#include "Empty.h"

class CPendulumLine :
	public CEmpty
{

private:

	float* m_pRectCenter;

public:
	CPendulumLine();
	~CPendulumLine();
	void Initialize(void);
	bool Load(void);
	void Update(const bool& me);
	Vector2	GetRectCenter(void);
	CRectangle GetRect(const Vector2& pos, const CRectangle& src) const {
		return CRectangle(0,0,0,0);
	}
	
	int GetType(void) const { return OBJECT_MOVE; }
};