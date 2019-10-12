#include "EnemyMove.h"


CEnemyMove::CEnemyMove() :
	m_bReverse(false),
	m_fAtackTimer(0),
	m_fCooltime(0),
	m_fMoveX(0.0f),
	m_fMoveY(0.0f){
	m_pMotion = g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_1])->GetMotion();
}

CEnemyMove::~CEnemyMove() {
}