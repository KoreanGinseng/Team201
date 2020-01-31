#pragma once
#include "Shot.h"
class CSordShot :
	public CShot
{
public:
	CSordShot(void);
	virtual ~CSordShot(void);
	void Fire(const Vector2& startPos) override;
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
};

