#pragma once
#include "Enemy.h"
class CEnemyHand :
	public CEnemy
{
private:
	bool m_bFind;
	bool m_bGhost;
public:
	CEnemyHand();
	~CEnemyHand();
	void Move(void) override;
	void Render(const Vector2& screenPos) override;
	void RenderCircle(const Vector2& screenPos) override;
};

