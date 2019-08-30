#include "Enemy.h"


CEnemy::CEnemy() :
	m_bEnd(false),
	m_bRevers(false),
	m_bXpos(0.0f),
	m_bYpos(0.0f),
	m_bTimer(0) {
}

CEnemy::~CEnemy() {
}

void CEnemy::Initialize() {
	m_bEnd = false;
	m_bRevers = false;
	m_bXpos = 500;
	m_bYpos = 500;
	m_bTimer = 0;
}

void CEnemy::KUpdate() {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_bEnd) {
		return;
	}

	if (m_bRevers) {
		m_bXpos += EnemySpeed;
	}
	else {
		m_bXpos -= EnemySpeed;
	}
}

void CEnemy::NUpdate() {

	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bTimer=Timer;
	}

	if (m_bEnd) {
		m_bTimer = 0;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
			m_bEnd = false;
		}
		return;
	}

	if (m_bTimer > 0) {
		if (g_pInput->IsKeyPush(MOFKEY_A)) {
			m_bEnd = true;
		}
		m_bTimer -= 1 * CUtilities::GetFrameSecond();
	}
	else {
		if (m_bRevers) {
			m_bXpos += EnemySpeed;
		}
		else {
			m_bXpos -= EnemySpeed;
		}
	}
}

void CEnemy::TUpdate(float Xpos, float Ypos, bool pRevers) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_bEnd || (m_bRevers != pRevers)) {
		float dx = Xpos - m_bXpos;
		if (dx > 0) {
			m_bRevers = false;
		}
		else
		{
			m_bRevers = true;
		}
		return;
	}
	float dx = Xpos - m_bXpos;
	if (dx > 0) {
		m_bRevers = false;
	}
	else
	{
		m_bRevers = true;
	}
	float dy = Ypos - m_bYpos;
	float d = sqrt(dx*dx + dy * dy);
	dx /= d;
	dy /= d;
	m_bXpos += dx * EnemySpeed;

	m_bYpos += dy * EnemySpeed;
}

void CEnemy::Render() {
	CGraphicsUtilities::RenderFillCircle(m_bXpos,m_bYpos,10,MOF_COLOR_GREEN);
}