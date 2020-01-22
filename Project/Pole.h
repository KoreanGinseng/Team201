#pragma once
#include "TargetObj.h"
class CPole :
	public CTargetObj
{
private:
	float m_PoleScale;
public:
	CPole(void);
	~CPole(void);
	void Initialize(void) override;
	void Render(const Vector2& screenPos) override;
	virtual bool OverValue(CRectangle rec, Vector2 & out) override;
	virtual void SetPoleScale(const float& scale);
};

