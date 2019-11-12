/**
 * @file RayBullet.cpp
 * @brief 光線
 * @author 大西永遠
 * @date 更新日（11/12）
 */

#include "RayBullet.h"

CRayBullet::CRayBullet() :
	CEnemyShot() {

}
CRayBullet::~CRayBullet() {

}
void CRayBullet::Initialize() {
	m_PosX = 0;
	m_PosY = 0;
	m_SpdX = 0;
	m_SpdY = 0;
	m_BounceTimes = 3;
	m_bShow = false;
	m_Texture.Load("Hp.png");
	m_ScaleMagnification = 0;
}
void CRayBullet::Fire(float px, float py, float sx, float sy, float pPosx, float pPosy) {
	m_PosX = px;
	m_PosY = py;

	m_bShow = true;

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
void CRayBullet::Update() {
	if (!m_bShow) {
		return;
	}
	m_PosX += m_SpdX;
	m_PosY += m_SpdY;

	float ox = 0, oy = 0;
	float mx = m_PosX, my = m_PosY;
	if (mx < Collision_Left) {
		ox = Collision_Left - mx;
	}
	else if (mx > Collision_Right)
	{
		ox = Collision_Right - mx;

	}
	if (my > Collision_Down) {
		oy = Collision_Down - my;
	}

	CollisionStage(ox, oy);

	if (m_PosX<0 || m_PosX>g_pGraphics->GetTargetWidth() || m_PosY<0 || m_PosY>g_pGraphics->GetTargetHeight()) {
		m_bShow = false;
	}
}

void CRayBullet::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_PosX, m_PosY, BulletRadius, MOF_COLOR_RED);
	m_Texture.RenderScaleRotate(, , m_ScaleMagnification, 1.0f,m_Radian);
}

void CRayBullet::CollisionStage(float ox, float oy) {
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

	if (m_BounceTimes == 0) {
		m_bShow = false;
	}

}


void CRayBullet::Release() {
	m_Texture.Release();
}
