#pragma once
#include "Shot.h"
class CAimShot : public CShot
{
private:
	Vector2 m_TargetPos;
	float	m_RotateRad;
public:
	CAimShot(void);
	virtual ~CAimShot(void);
	virtual void Fire(const Vector2& startPos) override;
	virtual void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
};

