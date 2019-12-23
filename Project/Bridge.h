#pragma once
#include "TargetObj.h"
class CBridge :
	public CTargetObj
{
public:
	CBridge();
	virtual ~CBridge();
	bool OverValue(CRectangle rec, Vector2 & out) override;
};

