#include "EnemyMove.h"


CEnemyMove::CEnemyMove() :
	m_bReverse(false),
	m_fAtackTimer(0),
	m_fCooltime(0),
	m_fMoveX(0.0f),
	m_fMoveY(0.0f) {
}

CEnemyMove::~CEnemyMove() {
}

void CEnemyMove::Animation(void)
{
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

void CEnemyMove::MotionCreate(std::shared_ptr<CAnimationData> m)
{
	int c =m->GetAnimCount();
	m_Motion.Create(m->GetAnim(), c);
}
