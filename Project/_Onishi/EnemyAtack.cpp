#include "EnemyAtack.h"
#include "mof.h"

CEnemyAtack::CEnemyAtack() :
	m_fAtackPosX(0.0f),
	m_fAtackPosY(0.0f),
	m_fTime(0),
	m_bShow(false) {
}

CEnemyAtack::~CEnemyAtack() {
}
/**
 * @brief	初期化
 * @return 無し
 */
void CEnemyAtack::Initialize() {
	m_fAtackPosX = 0;
	m_fAtackPosY = 0;
	m_bShow = false;
	m_fTime = 0;
}
/**
 * @brief	クリボー更新
 * @param (EposX) エネミーのX座標
 * @param (EposY) エネミーのY座標
 * @param (ERevers) エネミーの方向
 * @return 無し
 */
void CEnemyAtack::KUpdate(float EposX, float EposY, bool ERevers) {
	if (m_bShow) {
		return;
	}
	if (ERevers) {
		m_fAtackPosX = EposX + 50;
		m_fAtackPosY = EposY;
		m_bShow = true;

	}
	else
	{
		m_fAtackPosX = EposX - 50;
		m_fAtackPosY = EposY;
		m_bShow = true;
	}
}
/**
 * @brief	描画
 * @return 無し
 */
void CEnemyAtack::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fAtackPosX, m_fAtackPosY, 10, MOF_COLOR_RED);
	m_bShow = false;
}