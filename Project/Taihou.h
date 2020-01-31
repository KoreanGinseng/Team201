#pragma once
#include "Enemy.h"
#include	"AimShot.h"
class CTaihou :	public CEnemy
{
private:
	CRectangle m_HontaiRect;
	CRectangle m_TutuRect;
	CAimShot m_AimShot;

	float		m_Radian;

	int		m_ShotWait;
	int		m_OffsetShotWait;

public:
	CTaihou(void);
	virtual ~CTaihou(void);
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void CreateMotion(const char* pName) override;
};

