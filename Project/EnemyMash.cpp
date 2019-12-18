#include "EnemyMash.h"



CEnemyMash::CEnemyMash() :
CEnemy()
{
	m_Spd = Vector2(-2.0f, 0);
}


CEnemyMash::~CEnemyMash()
{
}

void CEnemyMash::Move(void)
{
	m_Move.x += m_Spd.x;

	m_Move.x = MOF_CLIPING(m_Move.x, -MASH_MAXSPD, MASH_MAXSPD);

	m_Move.y += m_Spd.y;
	if (m_Move.y > GRAVITYMAX)
	{
		m_Move.y += GRAVITYMAX;
	}
}

void CEnemyMash::Animation(void)
{
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
}
