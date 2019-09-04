#include "Enemy.h"


CEnemy::CEnemy() :
	m_bEnd(false),
	m_bRevers(false),
	m_bXpos(0.0f),
	m_bYpos(0.0f),
	m_bTimer(0),
	m_bMoveX(0.0f),
	m_bMoveY(0.0f){
}

CEnemy::~CEnemy() {
}

void CEnemy::Initialize() {
	m_bEnd = false;
	m_bRevers = false;
	m_bXpos = 500;
	m_bYpos = 500;
	m_bTimer = 0;
	m_bMoveX = EnemySpeed;
	m_bMoveY = EnemySpeed;
}

void CEnemy::Update(float Xpos, float Ypos, bool pRevers,int Type) {
	if (Type!=2) {
		m_bMoveY += GRAVITY;
		if (m_bMoveY >= 20.0f) {
			m_bMoveY = 20.0f;
		}
	}
	switch (Type)
	{
	case ENEMY_KURIBO:
		KUpdate();
		break;
	case ENEMY_NOKONOKO:
		NUpdate();
		break;
	case ENEMY_TERESA:
		TUpdate(Xpos, Ypos, pRevers);
		break;
	}


	
}

void CEnemy::KUpdate() {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_bEnd) {
		return;
	}
	m_bXpos += m_bMoveX;
	m_bYpos += m_bMoveY;
}

void CEnemy::NUpdate() {
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
		return;
	}

	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bTimer=Timer;
		return;
	}
	m_bXpos += m_bMoveX;
	m_bYpos += m_bMoveY;
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
	m_bXpos += dx * m_bMoveX;

	m_bYpos += dy * m_bMoveY;
}

void CEnemy::CollisionStage(float ox, float oy, int Type) {
	if (Type==2) {
		m_bMoveX = EnemySpeed;
		m_bMoveY = EnemySpeed;
		return;
	}
	m_bXpos += ox;
	m_bYpos += oy;
	if (oy<0&&m_bMoveY>0) {
		m_bMoveY = 0;
	}else if (oy > 0 && m_bMoveY<0) {
		m_bMoveY = 0;
	}
	if (ox < 0 && m_bMoveX>0) {
		m_bMoveX *= -1;
		m_bRevers = false;
	}
	else if (ox > 0 && m_bMoveX < 0) {
		m_bMoveX *= -1;
		m_bRevers = true;
	}
}

void CEnemy::Render() {
	CGraphicsUtilities::RenderFillCircle(m_bXpos,m_bYpos,10,MOF_COLOR_GREEN);
}