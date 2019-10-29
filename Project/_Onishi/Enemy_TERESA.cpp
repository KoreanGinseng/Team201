/**
 * @file Enemy_TERESA.cpp
 * @brief テレサ
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#include	"Enemy_TERESA.h"

CENEMY_TERESA::CENEMY_TERESA():
CEnemyMove() {
}
CENEMY_TERESA::~CENEMY_TERESA() {

}

void CENEMY_TERESA::Initialize() {
	m_fXpos = 500;
	m_fYpos = 500;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX =  m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
}

void CENEMY_TERESA::Update(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	float dx = Xpos - m_fXpos;
	if (dx > 0) {
		m_bRevers = true;
	}
	else
	{
		m_bRevers = false;
	}
	float dy = Ypos - m_fYpos;
	float d = sqrt(dx*dx + dy * dy);
	dx /= d;
	dy /= d;
	m_fXpos += (dx * m_fMoveX);

	m_fYpos += (dy * m_fMoveY);
}

void CENEMY_TERESA::Render(float Xpos, float Ypos) {
	if (m_bEnd) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, 10, MOF_COLOR_GREEN);
}
void CENEMY_TERESA::Release() {

}