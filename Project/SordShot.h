#pragma once
#include "Shot.h"
class CSordShot :
	public CShot
{
private:
	Vector2 m_WarpPos[5];
	int		m_WarpTime;
	int		m_No;
	int		m_OffsetWarpTime;
public:
	CSordShot(void);
	virtual ~CSordShot(void);
	void Fire(const Vector2& startPos) override;
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void SetWorpTime(const int& time);
	CRectangle GetRect(void) override;
};

