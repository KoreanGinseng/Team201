#include "MoveMash.h"



CMoveMash::CMoveMash()
{
}


CMoveMash::~CMoveMash()
{
}

void CMoveMash::Initialize(void)
{
	m_Spd.x = -1 * MASH_SPD;
	m_Spd.y = GRAVITY;
}

void CMoveMash::Update(void)
{
	m_Move.x += m_Spd.x;

	m_Move.x = MOF_CLIPING(m_Move.x, -MASH_MAXSPD, MASH_MAXSPD);

	m_Move.y += m_Spd.y;
	if (m_Move.y > GRAVITYMAX)
	{
		m_Move.y += GRAVITYMAX;
	}
}
