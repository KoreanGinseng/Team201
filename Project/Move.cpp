#include "Move.h"

Vector2* CMove::m_pPlayerPos = nullptr;

CMove::CMove() :
m_bReverse(false),
m_MotionNo(0),
m_Move(),
m_pPos(nullptr),
m_Spd()
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
