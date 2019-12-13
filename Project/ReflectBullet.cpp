/**
 * @file ReflectBullet.cpp
 * @brief ���˒e
 * @author �吼�i��
 * @date �X�V���i11/5�j
 */

#include "ReflectBullet.h"

CReflectBullet::CReflectBullet() :
	CEnemyShot() {

}
CReflectBullet::~CReflectBullet() {

}
void CReflectBullet::Initialize() {
	m_PosX = 0;
	m_PosY = 0;
	m_SpdX = 0;
	m_SpdY = 0;
	m_BounceTimes = 3;
	m_bShow = false;
	m_bShotEnd = false;
}
void CReflectBullet::Fire(float px, float py, float sx, float sy, float pPosx, float pPosy) {
	m_PosX = px;
	m_PosY = py;

	m_bShow = true;
	m_bShotEnd = false;


	float dx = pPosx - px;
	float dy = pPosy - py;
	m_Radian = atan2f(dy, dx);
	m_Radian = MOF_ToDegree(m_Radian);

	float Playerdx;
	float Playerdy;
	float d;
	float ddx;
	float ddy;
	/*m_PlayerPlaceX = PlayerPosX;
	m_PlayerPlaceY = PlayerPosY;*/
	Playerdx = pPosx - px;
	Playerdy = pPosy - py;
	d = sqrt(Playerdx*Playerdx + Playerdy * Playerdy);
	ddx = dx / d;
	ddy = dy / d;
	m_SpdX = ddx * BulletSpeed;
	m_SpdY = ddy * BulletSpeed;
}
bool CReflectBullet::Update() {
	if (!m_bShow) {
		return m_bShotEnd;
	}
	m_PosX += m_SpdX;
	m_PosY += m_SpdY;

	float ox = 0, oy = 0;
	float mx = m_PosX, my = m_PosY;
	if (mx < Collision_Left) {
		ox = Collision_Left - mx;
	}
	else if (mx >Collision_Right)
	{
		ox = Collision_Right - mx;

	}
	if (my > Collision_Down) {
		oy = Collision_Down - my;
	}

	CollisionStage(ox, oy);

	if (m_PosX<0 || m_PosX>g_pGraphics->GetTargetWidth() || m_PosY<0 || m_PosY>g_pGraphics->GetTargetHeight()) {
		m_bShow = false;
		m_bShotEnd = true;
	}
	return m_bShotEnd;
}
void CReflectBullet::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_PosX, m_PosY, BulletRadius, MOF_COLOR_RED);
}

void CReflectBullet::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;

	if (oy < 0 && m_SpdY>0) {
		m_SpdY *= -1;
		m_BounceTimes--;
	}
	else if (oy > 0 && m_SpdY < 0) {
		m_SpdY *= -1;
		m_BounceTimes--;
	}
	if (ox < 0 && m_SpdX>0) {
		m_SpdX *= -1;
		m_BounceTimes--;
	}
	else if (ox > 0 && m_SpdX < 0) {
		m_SpdX *= -1;
		m_BounceTimes--;
	}

	if (m_BounceTimes==0) {
		m_bShow = false;
		m_bShotEnd = true;
	}

}


void CReflectBullet::Release() {

}
