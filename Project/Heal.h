#pragma once
#include "TargetObj.h"
class CHeal :
	public CTargetObj
{
private:
	int		m_CoolTime;
public:
	CHeal(void);
	virtual ~CHeal(void);
	void Update(void) override;
	bool OverValue(CRectangle rect, Vector2& out) override;
};

