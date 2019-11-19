/**
 * @file Enemy_TESTBOS3.cpp
 * @brief テストボス3
 * @author 大西永遠
 * @date 更新日（11/19）
 */

#include	"Enemy_TESTBOS3.h"

CEnemy_TESTBOS3::CEnemy_TESTBOS3() :
	CEnemyMove(),
	m_HP(0) {

}
CEnemy_TESTBOS3::~CEnemy_TESTBOS3() {

}
void CEnemy_TESTBOS3::Initialize() {
	m_fXpos = 600;
	m_fYpos = 100;
	m_HP = 3;
}
void CEnemy_TESTBOS3::Update(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_HP == 0) {
		m_bEnd = true;
	}
}
void CEnemy_TESTBOS3::Render(float Xpos, float Ypos) {
	if (m_bEnd) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, EnemyRadius, MOF_COLOR_GREEN);
}
void CEnemy_TESTBOS3::Release() {

}