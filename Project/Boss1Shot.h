#pragma once
#include "Shot.h"
class CBoss1Shot1 :
	public CShot
{
public:
	CBoss1Shot1(void);
	virtual ~CBoss1Shot1(void);
	void Initialize(void) override;
	void Update(void) override;
	void Fire(const Vector2& pos) override;
	void CollisionStage(const Vector2& over) override;
};

