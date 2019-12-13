/**
 * @file Enemy_KURIBIO.cpp
 * @brief クリボー
 * @author 大西永遠
 * @date 更新日（11/22）
 */

#include	"Enemy_KURIBO.h"

CEnemy_KURIBO::CEnemy_KURIBO():
CEnemyMove()
{
}
CEnemy_KURIBO::~CEnemy_KURIBO() {

}

void CEnemy_KURIBO::Initialize() {
	m_fXpos = 500;
	m_fYpos = 500;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -1 * m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
}

void CEnemy_KURIBO::ClonInitialize(int cnt) {


		m_PosX[cnt] = 300+cnt*CloningDistance;
		m_PosY[cnt] = 100;
	m_bEnd = false;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -1 * m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
	m_EndTime = ENDTIME;
}

void CEnemy_KURIBO::Update(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_bEnd) {
		return;
	}

	Gravity();
	

	if (m_fMoveX==0) {
		if (m_bRevers) {
			m_fMoveX =  m_fEnemySpeed;
		}
		else
		{
			m_fMoveX = -1 * m_fEnemySpeed;
		}
	}

	AtackRange(Xpos, Ypos);

	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}

bool CEnemy_KURIBO::ClonUpdate(int i) {

	if (m_bEnd) {
		return m_bEnd;
	}

	Gravity();

	m_EndTime -= CUtilities::GetFrameSecond();
	if (m_EndTime<=0) {
		m_EndTime = 0;
		m_bEnd = true;
	}

	if (m_fMoveX == 0) {
		if (m_bRevers) {
			m_fMoveX = m_fEnemySpeed;
		}
		else
		{
			m_fMoveX = -1 * m_fEnemySpeed;
		}
	}
	m_PosX[i] += m_fMoveX;
	m_PosY[i] += m_fMoveY;

	return m_bEnd;
}

void CEnemy_KURIBO::CollisionStage(int i) {
	float ox = 0, oy = 0;
	float mx = m_PosX[i], my = m_PosY[i];
	if (mx < 200) {
		ox = 200 - mx;
	}
	else if (mx > 800)
	{
		ox = 800 - mx;

	}
	if (my > 600) {
		oy = 600 - my;
	}
	m_PosX[i] += ox;
	m_PosY[i] += oy;
	if (oy < 0 && m_fMoveY>0) {
		m_fMoveY = 0;
	}
	else if (oy > 0 && m_fMoveY < 0) {
		m_fMoveY = 0;
	}
	if (ox < 0 && m_fMoveX>0) {
		m_fMoveX *= -1;
		m_bRevers = false;
	}
	else if (ox > 0 && m_fMoveX < 0) {
		m_fMoveX *= -1;
		m_bRevers = true;
	}
}

void CEnemy_KURIBO::Render(float Xpos, float Ypos) {
	if (m_bEnd) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, EnemyRadius, MOF_COLOR_GREEN);
}

void CEnemy_KURIBO::ClonRender(int i) {
	if (m_bEnd) {
		return;
	}
	CGraphicsUtilities::RenderFillCircle(m_PosX[i], m_PosY[i], EnemyRadius, MOF_COLOR_GREEN);
}


void CEnemy_KURIBO::Release() {

}