#include "EnemyFloat.h"



CEnemyFloat::CEnemyFloat() :
CEnemy()
{
	m_EnemyType = ENEMY_FLOATING;
	m_bGravity = false;
	m_Spd.x = -2.0f;
	m_OffsetWait = 300;
}


CEnemyFloat::~CEnemyFloat()
{
}

void CEnemyFloat::Move(void)
{
	m_Move.x = m_Spd.x;
}
