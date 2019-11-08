/**
 * @file Enemy_Atack.cpp
 * @brief エネミーの攻撃
 * @author 大西永遠
 * @date 更新日（10/29）
 */

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

}
/**
 * @brief	クリボー更新
 * @param (EposX) エネミーのX座標
 * @param (EposY) エネミーのY座標
 * @param (ERevers) エネミーの方向
 * @return 無し
 */
void CEnemyAtack::Update(float EemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {
	
}
/**
 * @brief	描画
 * @return 無し
 */
void CEnemyAtack::Render() {

}