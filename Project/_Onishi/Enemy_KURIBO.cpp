#include	"Enemy_KURIBO.h"

CEnemy_KURIBO::CEnemy_KURIBO():
CEnemyMove()
{
}
CEnemy_KURIBO::~CEnemy_KURIBO() {

}
void CEnemy_KURIBO::Initialize() {
	m_fEnemySpeed = 2;
	m_fMoveX = -1 * m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
}

void CEnemy_KURIBO::Update(float Xpos, float Ypos) {
	m_bAttack = false;
	m_fMoveY += GRAVITY;
	if (m_fMoveY >= 20.0f) {
		m_fMoveY = 20.0f;
	}
	if (m_fYpos - 50 < Ypos&&m_fYpos + 10 > Ypos)
	{
		if (m_bReverse)
		{
			if (m_fXpos + 50 > Xpos&&m_fXpos < Xpos) 
			{
				m_bAttack = true;
				return;
			}
		}
		else
		{
			if (m_fXpos - 50 < Xpos&&m_fXpos > Xpos) 
			{
				m_bAttack = true;
				return;
			}
		}
	}


	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}