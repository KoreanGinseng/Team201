/**
 * @file Enemy_FLOATING.cpp
 * @brief ’µ’e
 * @author ‘å¼‰i‰“
 * @date XV“úi11/12j
 */

#include "Enemy_FLOATING.h"

CENEMY_FLOATING::CENEMY_FLOATING() :
	CEnemyMove(),
	m_CrawlRange(0),
	m_CrawlRangeCount(0) {

}
CENEMY_FLOATING::~CENEMY_FLOATING() {

}
void CENEMY_FLOATING::Initialize() {
	m_fXpos = 500;
	m_fYpos = 400;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -m_fEnemySpeed;
	m_CrawlRange = CrawlRangeCenter;
	m_CrawlRangeCount = -1;
}
void CENEMY_FLOATING::Update(float Xpos, float Ypos) {
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
void CENEMY_FLOATING::Render(float Xpos, float Ypos) {
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, EnemyRadius, MOF_COLOR_GREEN);

}
void CENEMY_FLOATING::Release() {

}