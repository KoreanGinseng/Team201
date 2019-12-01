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
	m_Spd = Vector2(2, 2);
}

void CMoveBat::Update(void)
{
	if (m_bReverse)
	{
		if (m_pPlayerPos->x < m_pPos->x && m_pPlayerPos->x > m_pPos->x + 32)
		{
			m_Move.y = m_Spd.y;
			return;
		}
		if (m_pPos->x > m_TurnPosRight)
		{
			MoveReverse();
		}
		m_Move.x = m_Spd.x;
	}
	else
	{
		if (m_pPlayerPos->x > m_pPos->x && m_pPlayerPos->x < m_pPos->x - 32)
		{
			m_Move.y = m_Spd.y;
			return;
		}
		if (m_pPos->x < m_TurnPosLeft)
		{
			MoveReverse();
		}
		m_Move.x = m_Spd.x;
	}
}
