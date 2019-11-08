/**
 * @file Enemy_NOKONOKO.cpp
 * @brief ƒmƒRƒmƒR
 * @author ‘å¼‰i‰“
 * @date XV“úi11/8j
 */

#include	"Enemy_NOKONOKO.h"

CENEMY_NOKONOKO::CENEMY_NOKONOKO():
CEnemyMove() {
}
CENEMY_NOKONOKO::~CENEMY_NOKONOKO() {

}

void CENEMY_NOKONOKO::Initialize() {
	m_fTimer = 0;
	m_fXpos = 500;
	m_fYpos = 500;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -1 * m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
}

void CENEMY_NOKONOKO::Update(float Xpos, float Ypos) {
	if (m_bEnd) {
		m_fTimer = 0;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
			m_bEnd = false;
		}
		return;
	}
	Gravity();
	if (m_fTimer > 0) {
		if (g_pInput->IsKeyPush(MOFKEY_A)) {
			m_bEnd = true;
		}
		m_fTimer -= 1 * CUtilities::GetFrameSecond();
		return;
	}

	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_fTimer = Timer;
		return;
	}
	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}

void CENEMY_NOKONOKO::Render(float Xpos, float Ypos) {
	if (m_bEnd) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, 10, MOF_COLOR_GREEN);
}

void CENEMY_NOKONOKO::Release() {

}