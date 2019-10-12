#include	"Enemy_BAT.h"

CENEMY_BAT::CENEMY_BAT():
CEnemyMove() {

}
CENEMY_BAT::~CENEMY_BAT() {

}

void CENEMY_BAT::Initialize() {
	m_fEnemySpeed = 2;
	m_fMoveX = -m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
}

void CENEMY_BAT::Update(float Xpos, float Ypos){
	if (m_fYpos <= Ypos) {

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
	}
	m_fXpos += m_fMoveX;
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}