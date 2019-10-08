#include "EnemyAtack.h"
#include "mof.h"

CEnemyAtack::CEnemyAtack() :
	m_fAposX(0.0f),
	m_fAposY(0.0f),
	m_bShow(false) {
}

CEnemyAtack::~CEnemyAtack() {
}
/**
 * @brief	初期化
 * @return 無し
 */
void CEnemyAtack::Initialize() {
	m_fAposX = 0;
	m_fAposY = 0;
	m_bShow = false;
}
/**
 * @brief	クリボー更新
 * @param (EposX) エネミーのX座標
 * @param (EposY) エネミーのY座標
 * @param (ERevers) エネミーの方向
 * @return 無し
 */
void CEnemyAtack::Update(float EposX, float EposY, bool ERevers) {
	if (m_bShow) {
		return;
	}
	if (ERevers) {
		m_fAposX = EposX + 50;
		m_fAposY = EposY;
		m_bShow = true;

	}
	else
	{
		m_fAposX = EposX - 50;
		m_fAposY = EposY;
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
	CGraphicsUtilities::RenderFillCircle(m_fAposX, m_fAposY, 10, MOF_COLOR_RED);
	m_bShow = false;
}