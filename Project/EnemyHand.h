#pragma once
#include "Enemy.h"
class CEnemyHand :
	public CEnemy
{
public:
	CEnemyHand();
	~CEnemyHand();
	void Move(void) override;
};

