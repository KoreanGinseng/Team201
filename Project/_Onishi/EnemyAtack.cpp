#include "EnemyAtack.h"
#include "mof.h"

CEnemyAtack::CEnemyAtack() :
	m_fAposX(0.0f),
	m_fAposY(0.0f),
	m_fTime(0),
	m_bShow(false) {
}

CEnemyAtack::~CEnemyAtack() {
}

void CEnemyAtack::Initialize() {
	m_fAposX = 0;
	m_fAposY = 0;
	m_bShow = false;
	m_fTime = 0;
}

void CEnemyAtack::KUpdate(float EposX, float EposY, bool ERevers) {
	if (m_bShow) {
		return;
	}
	if (ERevers) {
		m_fAposX = EposX + 50;
		m_fAposY = EposY;
		m_bShow = true;

	}
	else
	{
		m_fAposX = EposX - 50;
		m_fAposY = EposY;
		m_bShow = true;

	}
}

void CEnemyAtack::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fAposX, m_fAposY, 10, MOF_COLOR_RED);
	m_bShow = false;
}