#pragma once
#include "Shot.h"
class CRayShot :
	public CShot
{
private:
	Vector2	m_RefrectPos[3];
	float	m_RefrectRad[3];
	int		m_Timer;
public:
	CRayShot(void);
	virtual ~CRayShot(void);
	virtual void Fire(const Vector2& startPos) override;
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(const Vector2& screenPos) override;
	CCircle GetShotCircle(void) const;
	void Refrect(void);
	void FireStop(void);
};

