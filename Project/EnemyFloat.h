#pragma once
#include "Enemy.h"
class CEnemyFloat :
	public CEnemy
{
public:
	CEnemyFloat();
	~CEnemyFloat();
	void Move(void) override;
};

