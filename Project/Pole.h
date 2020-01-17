#pragma once
#include "TargetObj.h"
class CPole :
	public CTargetObj
{
public:
	CPole(void);
	~CPole(void);
	void Initialize(void) override;
	virtual bool OverValue(CRectangle rec, Vector2 & out) override;
};

