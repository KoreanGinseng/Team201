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
				if (m_pMotion->GetMotionNo() == BAT_MOVE) {
					m_pMotion->ChangeMotion(BAT_DOWN);
				}
				return;
			}
		}
		else {
			if (m_fXpos - 200 < Xpos&&m_fXpos > Xpos) {

				m_fYpos += 2 * m_fMoveY;
				if (m_pMotion->GetMotionNo() == BAT_MOVE) {
					m_pMotion->ChangeMotion(BAT_DOWN);
				}
				return;
			}
		}
	}
	if (m_pMotion->GetMotionNo() == BAT_DOWN) {
		m_pMotion->ChangeMotion(BAT_MOVE);
	}
	m_fXpos += m_fMoveX;
	m_pMotion->AddTimer(CUtilities::GetFrameSecond());
}