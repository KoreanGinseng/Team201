/**
 * @file RayBullet.cpp
 * @brief 光線
 * @author 大西永遠
 * @date 更新日（11/15）
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
	m_Radian = 0;
	m_EraseTime = EraseTime;
	m_Texture.Load("Hp.png");
	for (int i = 0; i < ReflectCount - 1; i++) {
		m_ScaleMagnification[i] = 0;

	}
	for (int i = 0; i < ReflectCount - 1; i++) {
		m_RRadian[i] = 0;

	}
	for (int i = 0; i < ReflectCount - 1; i++) {
		m_AddNumber[i] = 0;

	}
	for (int i = 0; i < ReflectCount - 1; i++) {
		m_ScaleMagnification[i]=0;

	}
	for (int i = 0; i < ReflectCount; i++) {
		m_RPosX[i] = 0;
		m_RPosY[i] = 0;

	}
}
void CRayBullet::Fire(float px, float py, float sx, float sy, float pPosx, float pPosy) {
	m_PosX = px;
	m_PosY = py;
	m_RPosX[0] = px;
	m_RPosY[0] = py;
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
void CRayBullet::Update() {
	
	if (m_EraseTime==0) {
		for (int i = 0; i < ReflectCount - 1; i++) {
			if (m_AddNumber[i] > 0) {
				m_AddNumber[i] -= AddNumber;
				if (m_AddNumber[ReflectCount - 2] <= 0) {
					m_bShow = false;
				}
				break;
			}
		}
		return;
	}
	m_PosX += m_SpdX*5;
	m_PosY += m_SpdY*5;

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
	m_EraseTime -= 1 * CUtilities::GetFrameSecond();
	if (m_EraseTime<0) {
		m_EraseTime = 0;
	}

	if (m_PosX<0 || m_PosX>g_pGraphics->GetTargetWidth() || m_PosY<0 || m_PosY>g_pGraphics->GetTargetHeight()) {
		//m_bShow = false;
	}
	
	for (int i = 0; i < ReflectCount - 1; i++) {
		if (m_RPosX[i + 1] == 0) {
			break;
		}
		if (m_ScaleMagnification[i]>=m_AddNumber[i]) {
			m_AddNumber[i] += AddNumber;
			break;
		}
	}


	for (int i = 0; i < ReflectCount-1;i++) {
		if (m_RPosX[i+1]==0) {
			break;
		}
		SetRadius(m_RPosX[i],m_RPosY[i], m_RPosX[i+1], m_RPosY[i+1],i);
		SetDistance(m_RPosX[i],m_RPosY[i], m_RPosX[i+1], m_RPosY[i+1],i);
	}

}

void CRayBullet::Render() {
	
	if (m_EraseTime == 0) {
		for (int i = ReflectCount ; i > 0; i--) {

			m_Texture.RenderScaleRotate(m_RPosX[i], m_RPosY[i], m_AddNumber[i-1], 1.0f, m_RRadian[i-1] /*+ MOF_MATH_PI*/, TEXTUREALIGNMENT_CENTERLEFT);
		}
	}
	else
	{
		for (int i = 0; i < ReflectCount - 1; i++) {

			m_Texture.RenderScaleRotate(m_RPosX[i], m_RPosY[i], m_AddNumber[i], 1.0f, m_RRadian[i] + MOF_MATH_PI, TEXTUREALIGNMENT_CENTERLEFT);
		}
	}
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_PosX, m_PosY, BulletRadius, MOF_COLOR_RED);
}

void CRayBullet::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;

	if (oy < 0 && m_SpdY>0) {
		m_SpdY *= -1;
		m_BounceTimes--;
		SetPos();
	}
	else if (oy > 0 && m_SpdY < 0) {
		m_SpdY *= -1;
		SetPos();
		m_BounceTimes--;
	}
	if (ox < 0 && m_SpdX>0) {
		m_SpdX *= -1;
		SetPos();
		m_BounceTimes--;
	}
	else if (ox > 0 && m_SpdX < 0) {
		m_SpdX *= -1;
		SetPos();
		m_BounceTimes--;
	}

	if (m_BounceTimes == 0) {
	//	m_bShow = false;
	}

}


void CRayBullet::Release() {
	m_Texture.Release();
}

void CRayBullet::SetPos() {
	for (int i=0; i < ReflectCount;i++) {
		if (m_RPosX[i] == 0) {
			m_RPosX[i] = m_PosX;
			m_RPosY[i] = m_PosY;
			break;
		}
	}
}

void CRayBullet::SetRadius(float posx, float posy,float posx2, float posy2,int i) {
	float dx = posx - posx2;
	float dy = posy - posy2;
	//dx = sqrt(dx*dx);
	//dy = sqrt(dy*dy);
	//float C = atan2f(dy, dx);
	m_RRadian[i] = atan2f(dy, dx);
	//m_RRadian[i] = static_cast<int>((C * 180 / MOF_MATH_PI));
	//m_RRadian[i] = MOF_ToDegree(C);
}
void CRayBullet::SetDistance(float posx, float posy, float posx2, float posy2,int i) {
	float dx = posx - posx2;
	float d = sqrt(dx*dx);
	d /= m_Texture.GetWidth()/2;
	m_ScaleMagnification[i] = d;
}
