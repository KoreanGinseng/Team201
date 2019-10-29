#include	"Enemy_NOKONOKO.h"

CENEMY_NOKONOKO::CENEMY_NOKONOKO():
CEnemyMove() {
}
CENEMY_NOKONOKO::~CENEMY_NOKONOKO() {

}

void CENEMY_NOKONOKO::Initialize() {
	m_fTimer = 0;
	m_fEnemySpeed = 2;
	m_fMoveX = -1 * m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
}

void CENEMY_NOKONOKO::Update(float Xpos, float Ypos) {
	
	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}
