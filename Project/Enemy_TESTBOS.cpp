
/**
 * @file Enemy_TESTBOS.cpp
 * @brief �e�X�g�{�X
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#include	"Enemy_TESTBOS.h"

CEnemy_TESTBOS::CEnemy_TESTBOS():
CEnemyMove(),
m_HP(0){

}
CEnemy_TESTBOS::~CEnemy_TESTBOS() {

}
void CEnemy_TESTBOS::Initialize() {
	m_fXpos = 800;
	m_fYpos = 400;
	m_HP = 3;
}
void CEnemy_TESTBOS::Update(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_HP==0) {
		m_bEnd = true;
	}
}
void CEnemy_TESTBOS::Render(float Xpos, float Ypos) {
	if (m_bEnd) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, 10, MOF_COLOR_GREEN);
}
void CEnemy_TESTBOS::Release() {

}