/**
 * @file BounceBllet.cpp
 * @brief ’µ’e
 * @author ‘å¼‰i‰“
 * @date XV“úi11/12j
 */

#include	"BounceBullet.h"
CBounceBullet::CBounceBullet():
	CEnemyShot(),
	m_BounceTimes(0),
	m_ExplosionTime(0)
{

}
CBounceBullet::~CBounceBullet(){

}
void CBounceBullet::Initialize() {
	m_PosX = 0;
	m_PosY = 0;
	m_SpdX = -BosBulletSpeed;
	m_SpdY = -5;
	m_bShow = false;
	m_bShotEnd = false;
	m_BounceTimes = Bounce_Times;
	m_ExplosionTime = ExplosionTime;
}
void CBounceBullet::Fire(float px, float py, float sx, float sy, float pPosx, float pPosy) {
	m_PosX = px;
	m_PosY = py;
	m_bShow = true;
	m_bShotEnd = false;


}
bool CBounceBullet::Update() {
	if (!m_bShow) {
		return m_bShotEnd;
	}
	m_SpdY += GRAVITY;
	if (m_SpdY >=GravityMax) {
		m_SpdY = GravityMax;
	}

	float ox = 0, oy = 0;
	float mx = m_PosX, my = m_PosY;
	if (mx > Collision_Right)
	{
		ox = Collision_Right - mx;

	}
	if (my > Collision_Down) {
		oy = Collision_Down - my;
	}

	CollisionStage(ox, oy);

	m_PosX += m_SpdX;
	m_PosY += m_SpdY;
	return m_bShotEnd;
}
void CBounceBullet::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_PosX, m_PosY, BulletRadius, MOF_COLOR_RED);
	if (m_PosX<0 || m_PosX>g_pGraphics->GetTargetWidth() || m_PosY<0 || m_PosY>g_pGraphics->GetTargetHeight()) {
		m_bShow = false;
	}
}

void CBounceBullet::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;
	if (oy < 0 && m_PosY>0) {
		
		if (m_BounceTimes==2) {
			m_SpdY = Jumping_Power;
			m_BounceTimes--;
		}
		else if (m_BounceTimes == 1) {
			m_SpdY = Jumping_Power * Bounce_Factor;
			m_BounceTimes--;

		}
		else
		{
			m_SpdY = 0;
			m_SpdX = 0;
			m_ExplosionTime -= CUtilities::GetFrameSecond();
			if (m_ExplosionTime<=0) {
				m_bShow = false;
				m_bShotEnd = true;
			}			
		}
	}
	else if (oy > 0 && m_PosY < 0) {
		if (m_BounceTimes ==2) {
			m_SpdY = Jumping_Power;
			m_BounceTimes--;
		}
		else if (m_BounceTimes == 1) {
			m_SpdY = Jumping_Power * Bounce_Factor;
			m_BounceTimes--;

		}
		else
		{
			m_SpdY = 0;
			m_SpdX = 0;
			m_ExplosionTime -= CUtilities::GetFrameSecond();
			if (m_ExplosionTime<=0) {
				m_bShow = false;
				m_bShotEnd = true;
			}

		}
	}
	if (ox < 0 && m_PosX>0) {
		m_SpdX = 0;
	}
	else if (ox > 0 && m_PosX < 0) {
		m_SpdX = 0;
	}
}

void CBounceBullet::Release() {

}