#pragma once
#include "Enemy.h"
class CEnemyMash :
	public CEnemy
{
public:
	CEnemyMash();
	~CEnemyMash();
	void Update(void) override;
	void Move(void);
	void Animation(void);
};

