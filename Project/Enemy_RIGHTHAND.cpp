/**
 * @file Enemy_RIGHTHAND.cpp
 * @brief �E��
 * @author �吼�i��
 * @date �X�V���i11/19�j
 */

#include "Enemy_RIGHTHAND.h"

CENEMY_RIGHTHAND::CENEMY_RIGHTHAND() :
	CEnemyMove(),
	m_CrawlRange(0),
	m_CrawlRangeCount(0) {

}
CENEMY_RIGHTHAND::~CENEMY_RIGHTHAND() {

}
void CENEMY_RIGHTHAND::Initialize() {
	m_fXpos = 500;
	m_fYpos = 400;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -m_fEnemySpeed;
	m_CrawlRange = CrawlRangeCenter;
	m_CrawlRangeCount = -1;
}
void CENEMY_RIGHTHAND::Update(float Xpos, float Ypos) {
	if (m_CrawlRange >= CrawlRange) {
		m_fMoveX = -m_fEnemySpeed;
		m_CrawlRangeCount = -m_CrawlRangeCount;
	}
	else if (m_CrawlRange <= 0)
	{
		m_fMoveX = m_fEnemySpeed;
		m_CrawlRangeCount = -m_CrawlRangeCount;
	}
	m_CrawlRange += m_CrawlRangeCount;
	m_fXpos += m_fMoveX;
}
void CENEMY_RIGHTHAND::Render(float Xpos, float Ypos) {
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, EnemyRadius, MOF_COLOR_GREEN);

}
void CENEMY_RIGHTHAND::Release() {

}