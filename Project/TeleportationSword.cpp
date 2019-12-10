/**
 * @file TeleportationSword.cpp
 * @brief　瞬間移動剣
 * @author 大西永遠
 * @date 更新日（11/22）
 */

#include "TeleportationSword.h"

CTeleportationSword::CTeleportationSword() :
	CEnemyShot(){

}
CTeleportationSword::~CTeleportationSword() {

}
void CTeleportationSword::Initialize() {
	for (int i = 0; i < CloningCount; i++) {
		m_PosX[i] = 0;
		m_PosY[i] = 0;
	}
	m_SpdX = 0;
	m_SpdY = 0;
	m_bShow = false;
	m_ClonFrag = false;
	m_TleEnd = false;
	m_StopTime = STOPTIME;
	m_Wall = false;
	m_TleCount = 0;
}
void CTeleportationSword::Fire(float px, float py, float sx, float sy, float pPosx, float pPosy) {
	for (int i = 0; i < CloningCount;i++) {
		m_PosX[i] = (px+CloningDistance*i)-(CloningDistance*2);
		m_PosY[i] = py;
	}

	m_bShow = true;

	float dx = pPosx - px;
	float dy = pPosy - py;
	m_Radian = atan2f(dy, dx);
	m_Radian = MOF_ToDegree(m_Radian);

	float Playerdx=0;
	float Playerdy=0;
	float d=0;
	float ddx=0;
	float ddy=0;

	Playerdx = pPosx - px;
	Playerdy = pPosy - py;
	d = sqrt(Playerdx*Playerdx + Playerdy * Playerdy);
	ddx = dx / d;
	ddy = dy / d;
	m_SpdX = ddx * (BulletSpeed / 2);
	m_SpdY = ddy * (BulletSpeed / 2);
}

void CTeleportationSword::CloningFire(float px, float py, float sx, float sy, float pPosx, float pPosy, float rd, float ddx, float ddy) {
	/*m_PosX = px;
	m_PosY = py;*/

	m_bShow = true;

	
	m_SpdX = ddx * (BulletSpeed / 2);
	m_SpdY = ddy * (BulletSpeed / 2);
}

void CTeleportationSword::Update() {
	if (m_Wall) {

		m_StopTime -= 1 * CUtilities::GetFrameSecond();
		if (m_StopTime < 0) {
			m_StopTime = 0;
			m_bShow = false;
		}
		return;
	}
	if (!m_bShow) {
		return;
	}
	for (int i = 0; i < CloningCount; i++) {
		m_PosX[i] += m_SpdX;
		m_PosY[i] += m_SpdY;
	}
	/*m_PosX += m_SpdX;
	m_PosY += m_SpdY;*/
	if (m_PosX[m_TleCount]<0 || m_PosX[m_TleCount]>g_pGraphics->GetTargetWidth() || m_PosY[m_TleCount]<0 || m_PosY[m_TleCount ]>g_pGraphics->GetTargetHeight()) {
		Initialize();
	}

	float ox = 0, oy = 0;
	float mx = m_PosX[m_TleCount], my = m_PosY[m_TleCount];
	if (mx > Collision_Right)
	{
		ox = Collision_Right - mx;

	}
	if (my > Collision_Down) {
		oy = Collision_Down - my;
	}

	//ランダムに振り分ける
	m_TleTime -= 1 * CUtilities::GetFrameSecond();
	if (m_TleTime <= 0) {
		m_TleCount = rand() % 5;
		m_TleTime = TLeTime;
	}

	CollisionStage(ox, oy);

	

}
void CTeleportationSword::Render() {
	if (!m_bShow) {
		return;
	}

	CGraphicsUtilities::RenderFillCircle(m_PosX[m_TleCount], m_PosY[m_TleCount], BulletRadius, MOF_COLOR_RED);

}

void CTeleportationSword::Release() {

}

void CTeleportationSword::CollisionStage(float ox, float oy) {
	m_PosX[m_TleCount] += ox;
	m_PosY[m_TleCount] += oy;
	if (oy < 0 && m_PosY>0) {

		m_SpdY = 0;
		m_SpdX = 0;
		m_TleEnd = true;
		m_Wall = true;
	}
	else if (oy > 0 && m_PosY < 0) {
		m_SpdY = 0;
		m_SpdX = 0;
		m_TleEnd = true;
		m_Wall = true;

	}
	if (ox < 0 && m_PosX>0) {
		m_SpdX = 0;
		m_SpdY = 0;
		m_TleEnd = true;
		m_Wall = true;

	}
	else if (ox > 0 && m_PosX < 0) {
		m_SpdX = 0;
		m_SpdY = 0;
		m_TleEnd = true;
		m_Wall = true;

	}
}
