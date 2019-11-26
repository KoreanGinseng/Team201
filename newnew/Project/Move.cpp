#include "Move.h"



CMove::CMove()
{
}


CMove::~CMove()
{
}

void CMove::MoveReverse(void)
{
	m_bReverse = !m_bReverse;
	m_Spd.x *= -1;
	m_Move.x = 0;
}
