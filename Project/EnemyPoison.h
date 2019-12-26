#pragma once
#include "Enemy.h"
class CEnemyPoison :
	public CEnemy
{
private:
	bool m_bDmg;
	Vector2 m_DmgScale;
	bool m_bAttack;
	CDynamicArray<CShot*> m_ShotArray;
public:
	CEnemyPoison(void);
	virtual ~CEnemyPoison(void);
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void Move(void) override;
	void Animation(void) override;
	CRectangle GetRect(void) override;
	CRectangle GetSrcAddRect(void) override;
	bool Dmg(const int& dmg) override;
	bool OverValue(CRectangle rec, Vector2& out) override;
	bool IsDmg(void) const { return m_bDmg; }
};

