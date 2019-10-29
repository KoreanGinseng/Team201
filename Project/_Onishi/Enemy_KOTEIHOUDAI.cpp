#include	"Enemy_KOTEIHOUDAI.h"

CENEMY_KOTEIHOUDAI::CENEMY_KOTEIHOUDAI():
CEnemyMove() {

}

CENEMY_KOTEIHOUDAI::~CENEMY_KOTEIHOUDAI() {

}

void CENEMY_KOTEIHOUDAI::Initialize() {
	int c = g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_1])->GetAnimCount();
	m_Motion.Create(g_pAnimManager->GetResource(FileName[ANIMATION_ENEMY_1])->GetAnim(), c);
	m_fAtackTimer = AtackTimer;
	m_fCooltime = 0;
}

void CENEMY_KOTEIHOUDAI::Update(float Xpos, float Ypos) {
	if (m_fAtackTimer >= 0 && m_fCooltime <= 0) {
		m_fAtackTimer -= 1 * CUtilities::GetFrameSecond();
		if (m_fAtackTimer < 0) {
			m_fCooltime = CoolTime;
		}
	}
	if (m_fCooltime >= 0 && m_fAtackTimer <= 0) {
		m_fCooltime -= 1 * CUtilities::GetFrameSecond();
		if (m_fCooltime < 0) {
			m_fAtackTimer = AtackTimer;
		}
	}
}