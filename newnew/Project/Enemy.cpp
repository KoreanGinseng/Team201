#include "Enemy.h"



CEnemy::CEnemy()
{
	m_bDead = false;
	m_bShow = true;
}


CEnemy::~CEnemy()
{
	Release();
}

void CEnemy::Update(void)
{
	m_MvCntrl.Update();
	m_Anim.Update();
}
