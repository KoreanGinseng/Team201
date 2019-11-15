/**
 * @file Enemy_BAT.cpp
 * @brief 蝙蝠の動き
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#include	"Enemy_BAT.h"

CENEMY_BAT::CENEMY_BAT():
CEnemyMove() {

}
CENEMY_BAT::~CENEMY_BAT() {

}

void CENEMY_BAT::Initialize() {
	/*int c = g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_3])->GetAnimCount();
	m_Motion.Create(g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_3])->GetAnim(), c);*/
	m_fEnemySpeed = 6;
	m_bReverse = false;
	m_fMoveX = -m_fEnemySpeed;
	m_fMoveY = 0;
	m_TurnLeft = m_fXpos - 320;
	m_TurnRight = m_fXpos + m_SrcRect.GetWidth() + 320;
}

void CENEMY_BAT::Update(float Xpos, float Ypos){
	/*if (m_fYpos <= Ypos) {

		if (m_bReverse) {

			if (m_fXpos + 200 > Xpos&&m_fXpos < Xpos) {
				m_fYpos += 2 * m_fMoveY;
				if (m_Motion.GetMotionNo() == BAT_MOVE) {
					m_Motion.ChangeMotion(BAT_DOWN);
				}
				return;
			}
		}
		else {
			if (m_fXpos - 200 < Xpos&&m_fXpos > Xpos) {

				m_fYpos += 2 * m_fMoveY;
				if (m_Motion.GetMotionNo() == BAT_MOVE) {
					m_Motion.ChangeMotion(BAT_DOWN);
				}
				return;
			}
		}
	}
	if (m_Motion.GetMotionNo() == BAT_DOWN) {
		m_Motion.ChangeMotion(BAT_MOVE);
	}*/
	
	if (m_fXpos < m_TurnLeft)
	{
		m_fXpos = m_TurnLeft;
		m_fMoveX *= -1;
		m_bReverse = true;
	}
	else if (m_fXpos > m_TurnRight)
	{
		m_fXpos = m_TurnRight - m_SrcRect.GetWidth();
		m_fMoveX *= -1;
		m_bReverse = false;
	}
}