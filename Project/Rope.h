#pragma once
#include "TargetObj.h"
class CRope :
	public CTargetObj
{
public:
	CRope();
	virtual ~CRope();
	void Initialize(void) override;
	bool OverValue(CRectangle rec, Vector2 & out) override;
};

