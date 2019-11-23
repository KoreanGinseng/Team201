#pragma once
#include "Substance.h"
class CEnemy :
	public CSubstance
{
public:
	CEnemy();
	~CEnemy();
	void Update(void) override;
};

