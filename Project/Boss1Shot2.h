#pragma once
#include "Shot.h"
class CBoss1Shot2 :
	public CShot
{
public:
	CBoss1Shot2(void);
	virtual ~CBoss1Shot2(void);
	void Initialize(void) override;
	void Update(void) override;
	void Fire(const Vector2& pos) override;
};

