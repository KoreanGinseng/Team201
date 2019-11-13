/*
 * @file Atack_KURIBO.cpp
 * @brief クリボーの攻撃
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#include	"Atack_KURIBO.h"

CAtack_KURIBO::CAtack_KURIBO():
CEnemyAtack(){

}
CAtack_KURIBO::~CAtack_KURIBO() {

}
void CAtack_KURIBO::Initialize() {
	m_fAtackPosX = 0;
	m_fAtackPosY = 0;
	m_bShow = false;

}
void CAtack_KURIBO::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {
	if (m_bShow) {
		return;
	}
	if (EnemyPosY - 50 < PlayerPosY&&EnemyPosY + 10 > PlayerPosY) {
		if (EnemyRevers) {
			if (EnemyPosX + 50 > PlayerPosX&&EnemyPosX < PlayerPosX) {

				m_fAtackPosX = EnemyPosX + 50;
				m_fAtackPosY = EnemyPosY;
				m_bShow = true;
				return;
			}
		}
		else {
			if (EnemyPosX - 50 < PlayerPosX&&EnemyPosX > PlayerPosX) {
				m_fAtackPosX = EnemyPosX - 50;
				m_fAtackPosY = EnemyPosY;
				m_bShow = true;
				return;
			}
		}
	}
	/*if (EnemyRevers) {
		m_fAtackPosX = EnemyPosX + 50;
		m_fAtackPosY = EnemyPosY;
		m_bShow = true;

	}
	else
	{
		m_fAtackPosX = EnemyPosX - 50;
		m_fAtackPosY = EnemyPosY;
		m_bShow = true;

	}*/
}
void CAtack_KURIBO::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fAtackPosX, m_fAtackPosY, 10, MOF_COLOR_RED);
	m_bShow = false;
}
void CAtack_KURIBO::Release() {

}