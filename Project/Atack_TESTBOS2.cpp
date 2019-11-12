/**
 * @file Atack_TESTBOS2.cpp
 * @brief テストボス2の攻撃
 * @author 大西永遠
 * @date 更新日（11/12）
 */

#include	"Atack_TESTBOS2.h"


CAtack_TESTBOS2::CAtack_TESTBOS2() :
	CEnemyAtack() {

}
CAtack_TESTBOS2::~CAtack_TESTBOS2() {

}
void CAtack_TESTBOS2::Initialize() {
	m_bShow = false;
	m_fAtackTimer = 0;
	m_fCooltime = 0;
	m_ShotReflectArry = new CReflectBullet();
	m_ShotReflectArry->Initialize();

}

void CAtack_TESTBOS2::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {

	if (EnemyPosX - BosAtackRange < PlayerPosX&&EnemyPosX + 10 > PlayerPosX) {
		if (m_fAtackTimer >= 0 && m_fCooltime <= 0) {
			m_fAtackTimer -= 1 * CUtilities::GetFrameSecond();
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
					if (m_ShotReflectArry->GetShow()) {
						continue;
					}
					m_ShotReflectArry->Initialize();
					m_ShotReflectArry->Fire(EnemyPosX, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY);
					break;
				}
			}
		}

		m_bShow = true;

	}
	m_ShotReflectArry->Update();
	
}
void CAtack_TESTBOS2::Render() {

	m_ShotReflectArry->Render();
	
}
void CAtack_TESTBOS2::Release() {
	if (m_ShotReflectArry) {
		m_ShotReflectArry->Release();
		delete[] m_ShotReflectArry;
		m_ShotReflectArry = NULL;
	}


}