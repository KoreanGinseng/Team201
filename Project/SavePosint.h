#pragma once
#include "TargetObj.h"
class CSavePosint :
	public CTargetObj
{
public:
	CSavePosint();
	virtual ~CSavePosint();
	virtual void Update(void) override;
};

