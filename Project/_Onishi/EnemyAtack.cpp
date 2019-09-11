#include "EnemyAtack.h"
#include "mof.h"

CEnemyAtack::CEnemyAtack() :
	AposX(0.0f),
	AposY(0.0f),
	time(0),
	m_bShow(false) {
}

CEnemyAtack::~CEnemyAtack() {
}

void CEnemyAtack::Initialize() {
	AposX = 0;
	AposY = 0;
	m_bShow = false;
	time = 0;
}

void CEnemyAtack::KUpdate(float EposX, float EposY, bool ERevers) {
	if (m_bShow) {
		return;
	}
	if (ERevers) {
		AposX = EposX + 50;
		AposY = EposY;
		m_bShow = true;

	}
	else
	{
		AposX = EposX - 50;
		AposY = EposY;
		m_bShow = true;

	}
}

void CEnemyAtack::Render() {
	if (!m_bShow) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(AposX, AposY, 10, MOF_COLOR_RED);
	m_bShow = false;
}