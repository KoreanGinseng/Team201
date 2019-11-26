/**
 * @file EnemyMove.cpp
 * @brief 敵の動き
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#include "EnemyMove.h"


CEnemyMove::CEnemyMove() :
	m_bEnd(false),
	m_bRevers(false),
	m_fXpos(0.0f),
	m_fYpos(0.0f),
	m_fAtackTimer(0),
	m_fCooltime(0),
	m_fMoveX(0.0f),
	m_fMoveY(0.0f),
	m_MoveFlag(false){
}

CEnemyMove::~CEnemyMove() {
}

void CEnemyMove::Initialize() {


}

void CEnemyMove::Update(float Xpos, float Ypos) {

	
}

void CEnemyMove::KUpdate(float Xpos,float Ypos) {
	
}

void CEnemyMove::NUpdate() {
	
}

void CEnemyMove::TUpdate(float Xpos, float Ypos) {
	
}

void CEnemyMove::BUpdate(float Xpos, float Ypos) {
	
}

void CEnemyMove::KOUpdate() {
	
	
}

void CEnemyMove::CollisionStage(float ox, float oy, int Type) {
	if (Type==2) {
		m_fMoveX = m_fEnemySpeed;
		m_fMoveY = m_fEnemySpeed;
		return;
	}
	if (Type==3) {
		m_fMoveY = m_fEnemySpeed;
	}
	m_fXpos += ox;
	m_fYpos += oy;
	if (oy<0&&m_fMoveY>0) {
		m_fMoveY = 0;
	}else if (oy > 0 && m_fMoveY<0) {
		m_fMoveY = 0;
	}
	if (ox < 0 && m_fMoveX>0) {
		m_fMoveX *= -1;
		m_bRevers = false;
	}
	else if (ox > 0 && m_fMoveX < 0) {
		m_fMoveX *= -1;
		m_bRevers = true;
	}
}

void CEnemyMove::Render(float Xpos, float Ypos) {
	
}

void CEnemyMove::Release() {
	
}