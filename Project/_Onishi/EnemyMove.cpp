/**
 * @file EnemyMove.cpp
 * @brief “G‚Ì“®‚«
 * @author ‘å¼‰i‰“
 * @date XV“úi10/29j
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
	m_fMoveY(0.0f){
}

CEnemyMove::~CEnemyMove() {
}

void CEnemyMove::Initialize() {


}

void CEnemyMove::Update(float Xpos, float Ypos) {

	
}

void CEnemyMove::KUpdate(float Xpos,float Ypos) {
	/*if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {

		m_bEnd = !m_bEnd;
	}
	if (m_bEnd) {
		return;
	}

	if (m_fYpos - 50 < Ypos&&m_fYpos + 10 > Ypos) {
		if (m_bRevers) {
			if (m_fXpos + 50 > Xpos&&m_fXpos < Xpos) {
				
				return;
			}
		}
		else {
			if (m_fXpos - 50 < Xpos&&m_fXpos > Xpos) {
				
				return;
			}
		}
	}

	
	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;*/
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