#pragma once
#include "Enemy.h"
class CEnemyMash :
	public CEnemy
{
public:
	CEnemyMash();
	~CEnemyMash();
	void Move(void) override;
	void Animation(void) override;
	CRectangle GetRect(void) override;
	CRectangle GetSrcAddRect(void) override;
};

