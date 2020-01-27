#pragma once
#include "TargetObj.h"
class CSavePosint :
	public CTargetObj
{
public:
	CSavePosint();
	virtual ~CSavePosint();
	virtual void Update(void) override;
	virtual void Render(const Vector2& screenPos) override;
};

