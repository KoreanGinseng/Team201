#pragma once
#include "TargetObj.h"
class CRenga :
	public CTargetObj
{
public:
	CRenga(void);
	virtual ~CRenga(void);
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	CRectangle GetRect(void) override;
	bool OverValue(CRectangle rect, Vector2& out) override;
};

