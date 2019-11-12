/**
 * @file PoisonBllet.cpp
 * @brief “Å’e
 * @author ‘å¼‰i‰“
 * @date XV“úi11/12j
 */

#include	"PoisonBullet.h"
CPoisonBullet::CPoisonBullet() :
	CEnemyShot(),
	m_BounceTimes(0),
	m_PoisonTime(0)
{

}
CPoisonBullet::~CPoisonBullet() {

}
void CPoisonBullet::Initialize() {
	m_PosX = 0;
	m_PosY = 0;
	m_SpdX = -BosBulletSpeed;
	m_SpdY = -5;
	m_bShow = false;
	//m_BounceTimes = Bounce_Times;
	m_PoisonTime = PoisonTime;
}
void CPoisonBullet::Fire(float px, float py, float sx, float sy, float pPosx, float pPosy) {
	m_PosX = px;
	m_PosY = py;
	m_SpdX = sx;
	m_SpdY = sy;
	m_bShow = true;


}
void CPoisonBullet::Update() {
	if (!m_bShow) {
		return;
	}
	m_SpdY += GRAVITY;
	if (m_SpdY >= GravityMax) {
		m_SpdY = GravityMax;
	}

	float ox = 0, oy = 0;
	float mx = m_PosX, my = m_PosY;
	/*if (mx < 200) {
		ox = 200 - mx;
	}
	else */if (mx > Collision_Right)
	{
		ox = Collision_Right - mx;

	}
	if (my > Collision_Down) {
		oy = Collision_Down - my;
	}

	CollisionStage(ox, oy);

	m_PosX += m_SpdX;
	m_PosY += m_SpdY;
}
void CPoisonBullet::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_PosX, m_PosY, BulletRadius, MOF_COLOR_RED);
	if (m_PosX<0 || m_PosX>g_pGraphics->GetTargetWidth() || m_PosY<0 || m_PosY>g_pGraphics->GetTargetHeight()) {
		m_bShow = false;
	}
}

void CPoisonBullet::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;
	if (oy < 0 && m_PosY>0) {
		
			m_SpdY = 0;
			m_SpdX = 0;
			m_PoisonTime -= CUtilities::GetFrameSecond();
			if (m_PoisonTime <= 0) {
				m_bShow = false;
			}
	}
	else if (oy > 0 && m_PosY < 0) {
		
			m_SpdY = 0;
			m_SpdX = 0;
			m_PoisonTime -= CUtilities::GetFrameSecond();
			if (m_PoisonTime <= 0) {
				m_bShow = false;
			}
	}
	if (ox < 0 && m_PosX>0) {
		m_SpdX = 0;
	}
	else if (ox > 0 && m_PosX < 0) {
		m_SpdX = 0;
	}
}

void CPoisonBullet::Release() {

}