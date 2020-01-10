#pragma once
#include "Enemy.h"
class CEnemyMash :
	public CEnemy
{
private:
	bool m_bDmg;
	Vector2 m_DmgScale;
public:
	CEnemyMash(void);
	~CEnemyMash(void);
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void RenderCircle(const Vector2& screenPos) override;
	void Move(void) override;
	void Animation(void) override;
	bool Dmg(const int& dmg) override;
	CRectangle GetRect(void) override;
	CRectangle GetSrcAddRect(void) override;
};

