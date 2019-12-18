#include "EnemyBat.h"



CEnemyBat::CEnemyBat() :
CEnemy()
{
	m_EnemyType = ENEMY_BAT;
	m_bGravity = false;
	m_bCollision = false;
}


CEnemyBat::~CEnemyBat()
{
}
