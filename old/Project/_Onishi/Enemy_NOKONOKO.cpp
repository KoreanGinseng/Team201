/**
 * @file Enemy_NOKONOKO.cpp
 * @brief ƒmƒRƒmƒR
 * @author ‘å¼‰i‰“
 * @date XV“úi10/29j
 */

#include	"Enemy_NOKONOKO.h"

CENEMY_NOKONOKO::CENEMY_NOKONOKO():
CEnemyMove() {
}
CENEMY_NOKONOKO::~CENEMY_NOKONOKO() {

}

void CENEMY_NOKONOKO::Initialize() {
	m_fTimer = 0;
	m_fEnemySpeed = 2;
	m_fMoveX = -m_fEnemySpeed;
	m_fMoveY = GRAVITY;
}

void CENEMY_NOKONOKO::Update(float Xpos, float Ypos) {
	
	m_fMoveY += GRAVITY;
	if (m_fMoveY > 20.0f)
	{
		m_fMoveY = 20.0f;
	}
}
