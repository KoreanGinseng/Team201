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
	void Initialize(void) override;
	void Update(void) override;
	void SetEneType(const int& t) { m_EnemyType = t; }
	bool OverValue(CRectangle rec, Vector2& out) override;
	void CollisionStage(const Vector2 & over);
	void Reverse(const Vector2 & over);
};

