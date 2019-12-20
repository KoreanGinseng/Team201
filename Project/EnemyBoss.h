#pragma once
#include "Enemy.h"
class CEnemyBoss :
	public CEnemy
{
private:
	float m_Scale;
public:
	CEnemyBoss();
	~CEnemyBoss();
	void Render(const Vector2& screenPos) override;
	CRectangle GetSrcAddRect(void) override;
};

