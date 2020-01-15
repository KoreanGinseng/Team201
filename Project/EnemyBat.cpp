#include "EnemyBat.h"



CEnemyBat::CEnemyBat() :
CEnemy()
{
	m_EnemyType = ENEMY_BAT;
	m_bGravity = false;
	m_bCollision = false;
	m_Spd = Vector2(5, 5);
	m_bFind = false;
	m_Measure = 0;
	m_OffsetWait = 300;
}


CEnemyBat::~CEnemyBat()
{
}

void CEnemyBat::Move(void)
{
	if (m_bFind)
	{
		m_Move.y = 0;
		m_Move.x = -m_Spd.x;
		m_Measure += fabs(m_Move.x);
	}

	if (m_bReverse)
	{
		if (CCordinate::GetPlayerPos().x + 128 * 4 > m_Pos.x && CCordinate::GetPlayerPos().x < m_Pos.x + 128 * 4)
		{
			m_Move.y = m_Spd.y;
			m_bFind = true;
		}
	}
	else
	{
		if (CCordinate::GetPlayerPos().x < m_Pos.x && CCordinate::GetPlayerPos().x > m_Pos.x - 128 * 3)
		{
			m_Move.y = m_Spd.y;
			m_bFind = true;
		}
	}

	if (m_bFind)
	{
		if (m_Measure > 128 * 3)
		{
			m_Move.y = -m_Spd.y;
		}
	}
}
