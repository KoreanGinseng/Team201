#include	"Enemy_KURIBO.h"

CEnemy_KURIBO::CEnemy_KURIBO():
CEnemyMove()
{
}
CEnemy_KURIBO::~CEnemy_KURIBO() {

}
void CEnemy_KURIBO::Initialize() {
	m_fXpos = 500;
	m_fYpos = 500;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -1 * m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
}

void CEnemy_KURIBO::Update(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_bEnd) {
		return;
	}

	m_fMoveY += GRAVITY;
	if (m_fMoveY >= 20.0f) {
		m_fMoveY = 20.0f;
	}
	if (m_fYpos - 50 < Ypos&&m_fYpos + 10 > Ypos) {
		if (m_bRevers) {
			if (m_fXpos + 50 > Xpos&&m_fXpos < Xpos) {
				m_Atack.KUpdate(m_fXpos, m_fYpos, m_bRevers);
				return;
			}
		}
		else {
			if (m_fXpos - 50 < Xpos&&m_fXpos > Xpos) {
				m_Atack.KUpdate(m_fXpos, m_fYpos, m_bRevers);
				return;
			}
		}
	}


	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}

void CEnemy_KURIBO::Render(float Xpos, float Ypos) {
	if (m_bEnd) {
		return;
	}
	m_Atack.Render();
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, 10, MOF_COLOR_GREEN);
}

void CEnemy_KURIBO::Release() {

}