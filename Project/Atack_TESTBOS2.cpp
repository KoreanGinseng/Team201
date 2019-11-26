/**
 * @file Atack_TESTBOS2.cpp
 * @brief �e�X�g�{�X2�̍U��
 * @author �吼�i��
 * @date �X�V���i11/15�j
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
	/*for (int i = 0; i < ShotCount; i++) {

	}*/
	m_ShotReflectArry = new CRayBullet();
	m_ShotReflectArry->Initialize();
	//m_Texture.Load("Hp.png");
	m_ScaleMagnification = 0;
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
				for (int i = 0; i < ShotCount; i++) {
					if (m_ShotReflectArry->GetShow()) {
						continue;
					}
					
					m_ShotReflectArry->Initialize();
					m_ShotReflectArry->Fire(EnemyPosX, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY);
					break;
				}
				m_fAtackPosX = EnemyPosX;
				m_fAtackPosY = EnemyPosY;
			}
		}

		m_bShow = true;

	}
	/*for (int i = 0; i < ShotCount; i++) {
	}*/
		m_ShotReflectArry->Update();
	
}
void CAtack_TESTBOS2::Render() {
	/*for (int i = 0; i < ShotCount; i++) {
	}*/
		m_ShotReflectArry->Render();
	//m_Texture.RenderScaleRotate(m_fAtackPosX,m_fAtackPosY,m_ScaleMagnification,1.0f, MOF_ToRadian(30));
	
}
void CAtack_TESTBOS2::Release() {
		if (m_ShotReflectArry) {
			m_ShotReflectArry->Release();
			delete[] m_ShotReflectArry;
			m_ShotReflectArry = NULL;
		}
	/*for (int i = 1; i < ShotCount; i++) {
	}*/
	//m_Texture.Release();

}