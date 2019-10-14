#include "EnemyMove.h"


CEnemyMove::CEnemyMove() :
	m_bReverse(false),
	m_fAtackTimer(0),
	m_fCooltime(0),
	m_fMoveX(0.0f),
	m_fMoveY(0.0f){
	int c = g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_1])->GetAnimCount();
	m_Motion.Create(g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_1])->GetAnim(), c);
}

CEnemyMove::~CEnemyMove() {
}