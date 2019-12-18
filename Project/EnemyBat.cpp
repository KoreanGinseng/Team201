#include "EnemyBat.h"



CEnemyBat::CEnemyBat() :
CEnemy()
{
	m_EnemyType = ENEMY_BAT;
	m_bGravity = false;
	m_bCollision = false;
	m_TurnPosLeft = m_Pos.x - 64;
	m_TurnPosRight = m_Pos.x + 64;
	m_Spd = Vector2(5, 5);
	m_bFind = false;
	m_Measure = 0;
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
	else
	{
		m_Move.x = -m_Spd.x;
		if (m_Pos.x < m_TurnPosLeft && m_bReverse)
		{
			m_Spd.x *= -1;
			m_bReverse = false;
		}
		else if (m_Pos.x > m_TurnPosRight && !m_bReverse)
		{
			m_Spd.x *= -1;
			m_bReverse = true;
		}
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
