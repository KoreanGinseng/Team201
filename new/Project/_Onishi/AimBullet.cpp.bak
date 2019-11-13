#include "AimBullet.h"

CAimBullet::CAimBullet():
CEnemyShot(){

}
CAimBullet::~CAimBullet() {

}
void CAimBullet::Initialize() {
	m_PosX = 0;
	m_PosY = 0;
	m_SpdX = 0;
	m_SpdY = 0;
	m_bShow = false;
}
void CAimBullet::Fire(float px, float py, float sx, float sy, float pPosx, float pPosy) {
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
	Playerdy = pPosy - px;
	d = sqrt(Playerdx*Playerdx + Playerdy * Playerdy);
	ddx = dx / d;
	ddy = dy / d;
	m_SpdX = ddx* BulletSpeed;
	m_SpdY = ddy* BulletSpeed;
}
void CAimBullet::Update() {
	if (!m_bShow) {
		return;
	}
	m_PosX += m_SpdX;
	m_PosY += m_SpdY;
	if (m_PosX<0 || m_PosX>g_pGraphics->GetTargetWidth() || m_PosY<0 || m_PosY>g_pGraphics->GetTargetHeight()) {
		m_bShow = false;
	}
}
void CAimBullet::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_PosX, m_PosY, 5, MOF_COLOR_RED);
}

void CAimBullet::Release() {

}
