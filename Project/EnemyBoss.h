#pragma once
#include "Enemy.h"
#include "AimShot.h"
class CEnemyBoss :
	public CEnemy
{
private:
	float m_Scale;
	CAimShot				m_AnimShot;
	CDynamicArray<CShot*>	m_BoundShotArray;
	bool m_bShotA;
public:
	CEnemyBoss(void);
	~CEnemyBoss(void);
	void Initialize(void) override;
	void Render(const Vector2& screenPos) override;
	void RenderCircle(const Vector2& screenPos) override;
	CRectangle GetSrcAddRect(void) override;
	//CDynamicArray<CShot*>*	GetAnimShotArray(void);
	CDynamicArray<CShot*>*	GetBoundShotArray(void);
	void Move(void) override;
	void Animation(void) override;
	virtual bool Dmg(const int& dmg) override;
};

