/**
 * @file EnemyShot.cpp
 * @brief エネミーの弾
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#include "EnemyShot.h"

CEnemyShot::CEnemyShot() :
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_SpdX(0.0f),
	m_SpdY(0.0f),
	m_bShow(false),
	m_StopTime(0),
	m_Wall(false),
	m_bShotEnd(false)
{
}

CEnemyShot::~CEnemyShot()
{
}

void CEnemyShot::Initialize() {
	
}
void CEnemyShot::Fire(float px, float py, float sx, float sy, float pPosx, float pPosy) {

}
bool CEnemyShot::Update() {
	return false;
}
void CEnemyShot::Render() {
	
}