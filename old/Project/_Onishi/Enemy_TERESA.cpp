#include	"Enemy_TERESA.h"

CENEMY_TERESA::CENEMY_TERESA():
CEnemyMove() {
}
CENEMY_TERESA::~CENEMY_TERESA() {

}

void CENEMY_TERESA::Initialize() {
	m_fEnemySpeed = 2;
	m_fMoveX =  m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
}

void CENEMY_TERESA::Update(float Xpos, float Ypos) {
	float dx = Xpos - m_fXpos;
	if (dx > 0) {
		m_bReverse = true;
	}
	else
	{
		m_bReverse = false;
	}
	float dy = Ypos - m_fYpos;
	float d = sqrt(dx*dx + dy * dy);
	dx /= d;
	dy /= d;
	m_fXpos += (dx * m_fMoveX);

	m_fYpos += (dy * m_fMoveY);
}