/*
 * @file Atack_POISONKURIBO.cpp
 * @brief 毒クリボーの攻撃
 * @author 大西永遠
 * @date 更新日（11/12）
 */

#include	"Atack_POISONKURIBO.h"

CAtack_POISONKURIBO::CAtack_POISONKURIBO() :
	CEnemyAtack() {

}
CAtack_POISONKURIBO::~CAtack_POISONKURIBO() {

}
void CAtack_POISONKURIBO::Initialize() {
	m_fAtackPosX = 0;
	m_fAtackPosY = 0;
	m_bShow = false;
	m_Shot = new CPoisonBullet();
	m_Shot->Initialize();
}
void CAtack_POISONKURIBO::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {
	if (m_bShow) {
		return;
	}


	if (EnemyPosY - Proximity_AtackY < PlayerPosY&&EnemyPosY + EnemyRadius > PlayerPosY) {
		if (EnemyRevers) {
			if (EnemyPosX + Proximity_AtackX > PlayerPosX&&EnemyPosX < PlayerPosX) {

				m_fAtackPosX = EnemyPosX + Atack_Position;
				m_fAtackPosY = EnemyPosY;
				m_bShow = true;
				return;
			}
		}
		else {
			if (EnemyPosX - Proximity_AtackX < PlayerPosX&&EnemyPosX > PlayerPosX) {
				m_fAtackPosX = EnemyPosX - Atack_Position;
				m_fAtackPosY = EnemyPosY;
				m_bShow = true;
				return;
			}
		}
	}

	if (EnemyPosY - AtackRangeY < PlayerPosY&&EnemyPosY + EnemyRadius > PlayerPosY) {
		if (EnemyRevers) {
			if (EnemyPosX + AtackRangeX > PlayerPosX&&EnemyPosX < PlayerPosX) {
				for (int i = 0; i < 1; i++) {
					if (m_Shot->GetShow()) {
						continue;
					}
					m_Shot->Initialize();
					m_Shot->Fire(EnemyPosX, EnemyPosY-Shot_Position, PoisonBulletSpeedX, PoisonBulletSpeedY, PlayerPosX, PlayerPosY);
					break;
				}
				
				
			}
		}
		else {
			if (EnemyPosX - AtackRangeX < PlayerPosX&&EnemyPosX > PlayerPosX) {
				for (int i = 0; i < 1; i++) {
					if (m_Shot->GetShow()) {
						continue;
					}
					m_Shot->Initialize();
					m_Shot->Fire(EnemyPosX, EnemyPosY-Shot_Position, -PoisonBulletSpeedX, -PoisonBulletSpeedY, PlayerPosX, PlayerPosY);
					break;
				}
				
			}
		}
	}

	for (int i = 0; i < 1; i++) {
		m_Shot->Update();

	}
}
void CAtack_POISONKURIBO::Render() {
	m_Shot->Render();
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fAtackPosX, m_fAtackPosY, EnemyRadius, MOF_COLOR_RED);
	m_bShow = false;
}
void CAtack_POISONKURIBO::Release() {
	if (m_Shot) {
		m_Shot->Release();
		delete 	m_Shot;
		m_Shot = NULL;

	}
}