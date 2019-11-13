
/**
 * @file Enemy_TESTBOS2.cpp
 * @brief テストボス2
 * @author 大西永遠
 * @date 更新日（11/5）
 */

#include	"Enemy_TESTBOS2.h"

CEnemy_TESTBOS2::CEnemy_TESTBOS2() :
	CEnemyMove(),
	m_HP(0) {

}
CEnemy_TESTBOS2::~CEnemy_TESTBOS2() {

}
void CEnemy_TESTBOS2::Initialize() {
	m_fXpos = 800;
	m_fYpos = 400;
	m_HP = 3;
}
void CEnemy_TESTBOS2::Update(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bDead = !m_bDead;
	}
	if (m_HP == 0) {
		m_bDead = true;
	}
}
void CEnemy_TESTBOS2::Render(float Xpos, float Ypos) {
	if (m_bDead) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, 10, MOF_COLOR_GREEN);
}
void CEnemy_TESTBOS2::Release() {

}