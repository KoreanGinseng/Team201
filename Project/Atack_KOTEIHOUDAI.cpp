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
	for (int i = 0; i < ENEMYSHOT_COUNT;i++) {
		m_ShotArry[i] = new CBounceBullet();//�e�X�g
		m_ShotArry[i]->Initialize();
	}
}
void CAtack_KOTEIHOUDAI::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {

	

	
	


	if (m_fAtackTimer >= 0 && m_fCooltime <= 0) {
		m_fAtackTimer -= 1 * CUtilities::GetFrameSecond();

		/*m_fAtackPosX += (ddx * BulletSpeed);

		m_fAtackPosY += (ddy * BulletSpeed);*/

		if (m_fAtackTimer < 0) {
			m_fCooltime = CoolTime;
			m_bShow = false;
		}
	}
	if (m_fCooltime >= 0 && m_fAtackTimer <= 0) {
		m_fCooltime -= 1 * CUtilities::GetFrameSecond();
		if (m_fCooltime < 0) {
			m_fAtackTimer = AtackTimer;
			for (int i = 0; i < ENEMYSHOT_COUNT; i++) {
				if (m_ShotArry[i]->GetShow()) {
					continue;
				}
				m_ShotArry[i]->Initialize();
				m_ShotArry[i]->Fire(EnemyPosX,EnemyPosY,BulletSpeed,BulletSpeed, PlayerPosX, PlayerPosY);
				break;
			}
			

			m_bShow = true;
		}
	}


	for (int i = 0; i < ENEMYSHOT_COUNT; i++) {
		m_ShotArry[i]->Update();
	
	}
}
void CAtack_KOTEIHOUDAI::Render() {
	
	/*if (!m_bShow) {
		return;
	}*/
	for (int i = 0; i < ENEMYSHOT_COUNT; i++) {
		m_ShotArry[i]->Render();
	}
	//CGraphicsUtilities::RenderFillCircle(m_fAtackPosX,m_fAtackPosY,5,MOF_COLOR_RED);
}
void CAtack_KOTEIHOUDAI::Release() {

}