/**
 * @file Enemy_KOTEIHOUDAI.cpp
 * @brief ŒÅ’è–C‘ä
 * @author ‘å¼‰i‰“
 * @date XV“úi11/12j
 */

#include	"Enemy_KOTEIHOUDAI.h"

CENEMY_KOTEIHOUDAI::CENEMY_KOTEIHOUDAI():
CEnemyMove() {

}

CENEMY_KOTEIHOUDAI::~CENEMY_KOTEIHOUDAI() {

}

void CENEMY_KOTEIHOUDAI::Initialize() {
	m_fXpos = 500;
	m_fYpos = 400;
	m_fAtackTimer = AtackTimer;
	m_fCooltime = 0;
}

void CENEMY_KOTEIHOUDAI::Update(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}

	Gravity();

	if (m_fAtackTimer >= 0 && m_fCooltime <= 0) {
		m_fAtackTimer -= 1 * CUtilities::GetFrameSecond();
		if (m_fAtackTimer < 0) {
			m_fCooltime = CoolTime;
		}
	}
	if (m_fCooltime >= 0 && m_fAtackTimer <= 0) {
		m_fCooltime -= 1 * CUtilities::GetFrameSecond();
		if (m_fCooltime < 0) {
			m_fAtackTimer = AtackTimer;
		}
	}
	m_fYpos += m_fMoveY;
}

void CENEMY_KOTEIHOUDAI::Render(float Xpos, float Ypos) {
	if (m_bEnd) {
		return;
	}
	if (m_fAtackTimer > 0) {
		float x = Xpos - m_fXpos;
		float y = Ypos - m_fYpos;




		float tx = sqrtf(x*x);
		float ty = sqrtf(y*y);

		if (Xpos <= m_fXpos) {
			tx = -tx;
		}

		if (Ypos <= m_fYpos) {
			ty = -ty;
		}
		CGraphicsUtilities::RenderLine(m_fXpos, m_fYpos, Xpos, Ypos, MOF_COLOR_RED);
	}
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, EnemyRadius, MOF_COLOR_GREEN);
}

void CENEMY_KOTEIHOUDAI::Release() {

}