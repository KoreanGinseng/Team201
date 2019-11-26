#pragma once
#include "Substance.h"
class CEnemy :
	public CSubstance
{
private:
	int m_EnemyType;
public:
	CEnemy();
	~CEnemy();
	void Update(void) override;
	void SetEneType(const int& t) { m_EnemyType = t; }
	void CollisionStage(const Vector2 & over);
};

