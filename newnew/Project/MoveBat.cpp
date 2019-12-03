#include "MoveBat.h"



CMoveBat::CMoveBat() :
CMove()
{
}


CMoveBat::~CMoveBat()
{
}

void CMoveBat::Initialize(void)
{
	m_TurnPosLeft = m_pPos->x - 64;
	m_TurnPosRight = m_pPos->x + 64;
	m_Spd = Vector2(5, 5);
	m_bFind = false;
}

void CMoveBat::Update(void)
{
	if (m_pPlayerPos->y <= m_pPos->y + 96 && m_bFind)
	{
		m_Move.y = 0;
		m_Move.x = -m_Spd.x;
		return;
	}

	if (m_bReverse)
	{
		if (m_pPlayerPos->x > m_pPos->x && m_pPlayerPos->x < m_pPos->x + 128 * 4)
		{
			m_Move.y = m_Spd.y;
			m_bFind = true;
		}
	}
	else
	{
		if (m_pPlayerPos->x < m_pPos->x && m_pPlayerPos->x > m_pPos->x - 128 * 3)
		{
			m_Move.y = m_Spd.y;
			m_bFind = true;
		}
	}
}
