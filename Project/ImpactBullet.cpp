/**
 * @file ImpactBullet.cpp
 * @brief �Ռ�
 * @author �吼�i��
 * @date �X�V���i12/3�j
 */

#include "ImpactBullet.h"

CImpactBullet::CImpactBullet() :
	CEnemyShot() {

}
CImpactBullet::~CImpactBullet() {

}
void CImpactBullet::Initialize() {
	m_PosX = 0;
	m_PosY = 0;
	m_SpdX = 0;
	m_SpdY = 0;
	m_bShow = false;
}


void CImpactBullet::Fire(float px, float py, float sx, float sy, float pPosx, float pPosy) {
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

	Playerdx = pPosx - px;
	Playerdy = pPosy - py;
	d = sqrt(Playerdx*Playerdx + Playerdy * Playerdy);
	ddx = dx / d;
	ddy = dy / d;
	m_SpdX = ddx * BulletSpeed;
	m_SpdY = ddy * BulletSpeed;
}

void CImpactBullet::Fire(float px, float py) {
	m_PosX = px;
	m_PosY = py;

	m_bShow = true;

	/*float dx = pPosx - px;
	float dy = pPosy - py;
	m_Radian = atan2f(dy, dx);
	m_Radian = MOF_ToDegree(m_Radian);

	float Playerdx;
	float Playerdy;
	float d;
	float ddx;
	float ddy;

	Playerdx = pPosx - px;
	Playerdy = pPosy - py;
	d = sqrt(Playerdx*Playerdx + Playerdy * Playerdy);
	ddx = dx / d;
	ddy = dy / d;*/
	m_SpdX = -BulletSpeed;
	m_SpdY = -BulletSpeed;
}

void CImpactBullet::Update() {
	if (!m_bShow) {
		return;
	}
	m_PosX += m_SpdX;
	/*m_PosY += m_SpdY;*/
	if (m_PosX<0 || m_PosX>g_pGraphics->GetTargetWidth() || m_PosY<0 || m_PosY>g_pGraphics->GetTargetHeight()) {
		m_bShow = false;
	}
}
void CImpactBullet::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillRect(m_PosX, m_PosY, m_PosX-100, m_PosY-100, MOF_COLOR_RED);
}

void CImpactBullet::Release() {

}
