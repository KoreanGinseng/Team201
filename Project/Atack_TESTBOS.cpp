#include	"Atack_TESTBOS.h"


CAtack_TESTBOS::CAtack_TESTBOS():
CEnemyAtack(){

}
CAtack_TESTBOS::~CAtack_TESTBOS() {

}
void CAtack_TESTBOS::Initialize() {
	m_bShow = false;
	m_fAtackTimer = 0;
	m_fCooltime = 0;
	for (int i = 0; i < ENEMYSHOT_COUNT; i++) {
		m_ShotAimArry[i] = new CAimBullet();
		m_ShotAimArry[i]->Initialize();
	}

	m_ShotBounceArry = new CBounceBullet();
	m_ShotBounceArry->Initialize();
}

void CAtack_TESTBOS::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {
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
					if (m_ShotAimArry[i]->GetShow()) {
						continue;
					}
					m_ShotAimArry[i]->Initialize();
					m_ShotAimArry[i]->Fire(EnemyPosX, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY);
					break;
				}
			}
		}





		for (int i = 0; i < 1; i++) {
			if (m_ShotBounceArry->GetShow()) {
				continue;
			}
			m_ShotBounceArry->Initialize();
			m_ShotBounceArry->Fire(EnemyPosX, EnemyPosY, BosBulletSpeed, BosBulletSpeed, PlayerPosX, PlayerPosY);
			break;
		}

		m_bShow = true;

	}
		for (int i = 0; i < ENEMYSHOT_COUNT; i++) {
			m_ShotAimArry[i]->Update();

		}
		for (int i = 0; i < 1; i++) {
			m_ShotBounceArry->Update();

		}
}
void CAtack_TESTBOS::Render() {

	for (int i = 0; i < ENEMYSHOT_COUNT; i++) {
		m_ShotAimArry[i]->Render();
	}

	m_ShotBounceArry->Render();
}
void CAtack_TESTBOS::Release() {

}