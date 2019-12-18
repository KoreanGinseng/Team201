#include "EnemyMash.h"



CEnemyMash::CEnemyMash() :
CEnemy()
{
	m_EnemyType = ENEMY_MASH;
	m_Spd.x = -2.0f;
}


CEnemyMash::~CEnemyMash()
{
}

void CEnemyMash::Move(void)
{
	m_Move.x += m_Spd.x;

	m_Move.x = MOF_CLIPING(m_Move.x, -MASH_MAXSPD, MASH_MAXSPD);
}

void CEnemyMash::Animation(void)
{
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
}
