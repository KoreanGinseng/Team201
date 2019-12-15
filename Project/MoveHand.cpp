#include "MoveHand.h"



CMoveHand::CMoveHand() :
m_bFind(false)
{
}


CMoveHand::~CMoveHand()
{
}

void CMoveHand::Initialize(void)
{
	m_bFind = false;
	m_Spd = Vector2(5, 5);
}

void CMoveHand::Update(void)
{
	if (m_pPlayerPos->x > m_pPos->x && !m_bFind)
	{
		m_bFind = true;
	}
	if (!m_bFind)
	{
		return;
	}
	Vector2 d = *m_pPos - *m_pPlayerPos;
	float c = sqrt(d.x * d.x + d.y * d.y);
	m_Move = -((d / c) * m_Spd);
}
