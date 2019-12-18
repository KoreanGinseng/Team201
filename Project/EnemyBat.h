#pragma once
#include "Enemy.h"
class CEnemyBat : public CEnemy
{
private:
	float	m_TurnPosLeft;
	float	m_TurnPosRight;
	bool	m_bFind;
	float	m_Measure;
public:
	CEnemyBat(void);
	~CEnemyBat(void);
	void Move(void) override;
};

