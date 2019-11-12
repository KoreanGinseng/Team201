/**
 * @file Enemy_KURIBIO.cpp
 * @brief クリボー
 * @author 大西永遠
 * @date 更新日（11/12）
 */

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

	Gravity();
	

	if (m_fMoveX==0) {
		if (m_bRevers) {
			m_fMoveX =  m_fEnemySpeed;
		}
		else
		{
			m_fMoveX = -1 * m_fEnemySpeed;
		}
	}

	AtackRange(Xpos, Ypos);

	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}

void CEnemy_KURIBO::Render(float Xpos, float Ypos) {
	if (m_bEnd) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, EnemyRadius, MOF_COLOR_GREEN);
}

void CEnemy_KURIBO::Release() {

}