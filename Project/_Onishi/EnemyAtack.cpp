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
/**
 * @brief	クリボー更新
 * @param (EposX) エネミーのX座標
 * @param (EposY) エネミーのY座標
 * @param (ERevers) エネミーの方向
 * @return 無し
 */
/**
 * @brief	描画
 * @return 無し
 */