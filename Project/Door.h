#pragma once
#include "TargetObj.h"
class CDoor :
	public CTargetObj
{
public:
	CDoor(void);
	virtual ~CDoor(void);
	void OpenTheDoor(void);
	virtual bool OverValue(CRectangle rect, Vector2& out) override;
};

