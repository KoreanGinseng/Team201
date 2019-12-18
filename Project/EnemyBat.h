#pragma once
#include "Enemy.h"
class CEnemyBat : public CEnemy
{
private:
	bool	m_bFind;
	float	m_Measure;
public:
	CEnemyBat(void);
	~CEnemyBat(void);
	void Move(void) override;
};

