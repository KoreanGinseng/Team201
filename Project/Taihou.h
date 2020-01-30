#pragma once
#include "Enemy.h"
class CTaihou :	public CEnemy
{
private:
public:
	CTaihou(void);
	virtual ~CTaihou(void);
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
};

