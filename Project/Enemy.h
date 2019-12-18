#pragma once
#include "Substance.h"
#include "EnemyDefine.h"
#include "Shot.h"

class CEnemy : public CSubstance {
private:
	int m_EnemyType;
public:
	CEnemy(void);
	virtual ~CEnemy(void);
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Move(void);
	virtual void Animation(void);
	bool OverValue(CRectangle rec, Vector2& out) override;
	void CollisionStage(const Vector2 & over);
	void Reverse(const Vector2 & over);
	int	 GetEnemyType(void) const { return m_EnemyType; }
	bool Dmg(const CRectangle& pre, const int& preWait);
	bool KnockBack(const CRectangle& pre, const int& preWait);
};