#include	"Enemy_KURIBO.h"

CEnemy_KURIBO::CEnemy_KURIBO():
CEnemyMove()
{
}
CEnemy_KURIBO::~CEnemy_KURIBO() {

}
void CEnemy_KURIBO::Initialize() {
	int c = g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_1])->GetAnimCount();
	m_Motion.Create(g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_1])->GetAnim(), c);
	m_fEnemySpeed = 2;
	m_fMoveX = -m_fEnemySpeed;
	m_fMoveY = 0;
}

void CEnemy_KURIBO::Update(float Xpos, float Ypos) {
	m_bAttack = false;
	m_fMoveY += GRAVITY;
	
	if (m_fMoveY >= 20.0f) {
		m_fMoveY = 20.0f;
	}
}