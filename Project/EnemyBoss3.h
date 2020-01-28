#pragma once
#include "Enemy.h"
class CEnemyBoss3 :
	public CEnemy
{
public:
	CEnemyBoss3(void);
	~CEnemyBoss3(void);
	virtual void CreateMotion(const char* pName) override;
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(const Vector2& screenPos) override;
};

