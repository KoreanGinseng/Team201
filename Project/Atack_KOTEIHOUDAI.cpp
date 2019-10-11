#include	"Atack_KOTEIHOUDAI.h"

CAtack_KOTEIHOUDAI::CAtack_KOTEIHOUDAI():
CEnemyAtack(){

}
CAtack_KOTEIHOUDAI::~CAtack_KOTEIHOUDAI() {

}
void CAtack_KOTEIHOUDAI::Initialize() {
	m_fAtackPosX = 0;
	m_fAtackPosY = 0;
	m_bShow = false;
	m_fAtackTimer=0;
	m_fCooltime=0;
	m_PlayerPlaceX=0;
	m_PlayerPlaceY=0;
	ddx=0;
	ddy=0;
}
void CAtack_KOTEIHOUDAI::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {

	float dx = PlayerPosX - EnemyPosX;
	float dy = PlayerPosY - EnemyPosY;
	m_Radian = atan2f(dy, dx);
	m_Radian = MOF_ToDegree(m_Radian);

	float Playerdx;
	float Playerdy;
	float d;
	


	if (m_fAtackTimer >= 0 && m_fCooltime <= 0) {
		m_fAtackTimer -= 1 * CUtilities::GetFrameSecond();

		m_fAtackPosX += (ddx * BulletSpeed);

		m_fAtackPosY += (ddy * BulletSpeed);

		if (m_fAtackTimer < 0) {
			m_fCooltime = CoolTime;
			m_bShow = false;
		}
	}
	if (m_fCooltime >= 0 && m_fAtackTimer <= 0) {
		m_fCooltime -= 1 * CUtilities::GetFrameSecond();
		if (m_fCooltime < 0) {
			m_fAtackTimer = AtackTimer;
			m_fAtackPosX = EnemyPosX;
			m_fAtackPosY = EnemyPosY;

			m_PlayerPlaceX = PlayerPosX;
			m_PlayerPlaceY = PlayerPosY;
			Playerdx = m_PlayerPlaceX - m_fAtackPosX;
			Playerdy = m_PlayerPlaceY - m_fAtackPosY;
			d = sqrt(Playerdx*Playerdx + Playerdy * Playerdy);
			ddx = dx / d;
			ddy = dy / d;

			m_bShow = true;
		}
	}

}
void CAtack_KOTEIHOUDAI::Render() {
	CGraphicsUtilities::RenderString(200,200,"%f",m_Radian);
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fAtackPosX,m_fAtackPosY,5,MOF_COLOR_RED);
}
void CAtack_KOTEIHOUDAI::Release() {

}