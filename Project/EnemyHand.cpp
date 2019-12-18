#include "EnemyHand.h"



CEnemyHand::CEnemyHand() :
CEnemy()
{
	m_EnemyType = ENEMY_HAND;
	m_bGravity = false;
	m_bCollision = false;
}


CEnemyHand::~CEnemyHand()
{
}

void CEnemyHand::Move(void)
{

}
