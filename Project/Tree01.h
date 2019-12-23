#pragma once
#include "TargetObj.h"
class CTree01 :
	public CTargetObj
{
public:
	CTree01();
	virtual ~CTree01();
	bool OverValue(CRectangle rec, Vector2 & out) override;
};

