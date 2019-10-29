#include	"Enemy_NOKONOKO.h"

CENEMY_NOKONOKO::CENEMY_NOKONOKO():
CEnemyMove() {
}
CENEMY_NOKONOKO::~CENEMY_NOKONOKO() {

}

void CENEMY_NOKONOKO::Initialize() {
	int c = g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_2])->GetAnimCount();
	m_Motion.Create(g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_2])->GetAnim(), c);
	m_fTimer = 0;
	m_fEnemySpeed = 2;
	m_fMoveX = -m_fEnemySpeed;
	m_fMoveY = GRAVITY;
}

void CENEMY_NOKONOKO::Update(float Xpos, float Ypos) {
	
	m_fMoveY += GRAVITY;
	if (m_fMoveY > 20.0f)
	{
		m_fMoveY = 20.0f;
	}
}
