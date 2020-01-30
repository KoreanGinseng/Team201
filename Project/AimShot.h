#pragma once
#include "Shot.h"
class CAimShot : public CShot
{
private:
	Vector2 m_TargetPos;
	float	m_RotateRad;
	float	m_TexScale;
public:
	CAimShot(void);
	virtual ~CAimShot(void);
	virtual void Fire(const Vector2& startPos) override;
	virtual void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	CRectangle GetRect(void) override;
	float GetRad(void) const;
	float GetScale(void) const;
	void SetScale(const float& s);
	void SetSpd(const Vector2& spd);
};

