#pragma once
#include "Shot.h"
class CPoisonShot :
	public CShot
{
public:
	CPoisonShot(void);
	~CPoisonShot(void);
	void	Initialize(void) override;
	void	Update(void) override;
	void	Render(const Vector2& screenPos) override;
	void	Fire(const Vector2& startPos) override;
};

