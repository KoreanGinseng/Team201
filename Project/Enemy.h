#pragma once
#include "Substance.h"
#include "EnemyDefine.h"
#include "Shot.h"

class CEnemy : public CSubstance {
protected:
	int m_EnemyType;
	bool m_bGravity;
	bool m_bBoss;
	bool m_bCameraMove;
public:
	CEnemy(void);
	virtual ~CEnemy(void);
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Move(void);
	virtual void Animation(void);
	virtual bool OverValue(CRectangle rec, Vector2& out) override;
	void CollisionStage(const Vector2 & over);
	void Reverse(const Vector2 & over);
	int	 GetEnemyType(void) const { return m_EnemyType; }
	bool Dmg(const CRectangle& pre, const int& preWait);
	virtual bool Dmg(const int& dmg);
	bool KnockBack(const CRectangle& pre, const int& preWait);
	virtual CRectangle GetSrcAddRect(void);
	void SetBoss(void); 
	void SetCameraMove(const bool& b);
	bool IsBoss(void) const;
};