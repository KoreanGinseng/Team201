#pragma once
#include "TargetObj.h"
class CTreasure :
	public CTargetObj
{
private:
	bool	m_bKey;
public:
	CTreasure(void);
	virtual ~CTreasure(void);
	virtual void Render(const Vector2& screenPos) override;
	virtual bool OverValue(CRectangle rect, Vector2& out) override;
};

