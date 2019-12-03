/**
 * @file Enemy_RIGHTHAND.cpp
 * @brief 右手
 * @author 大西永遠
 * @date 更新日（12/3）
 */

#include "Enemy_RIGHTHAND.h"

CEnemy_RIGHTHAND::CEnemy_RIGHTHAND() :
	CEnemyMove(),
	m_MoveEndFlag(false),
	m_AimTime(0.0f),
	m_Limit(false){

}
CEnemy_RIGHTHAND::~CEnemy_RIGHTHAND() {

}
void CEnemy_RIGHTHAND::Initialize() {
	m_fXpos = 790;
	m_fYpos = 400;
	m_InitialPositionX = m_fXpos;
	m_InitialPositionY = m_fYpos;
	m_fEnemySpeed = EnemySpeed;
	m_MoveFlag = true;
	m_MoveEndFlag = false;
	m_AimTime = 0;
	m_Limit = false;
	m_Fire = false;
}

void CEnemy_RIGHTHAND::Start(float PlayerPosX) {
	PlayPosX = PlayerPosX;
	float dx = PlayerPosX - m_fXpos;
	float dy = MAXTOP - m_fYpos;

	float d = sqrt(dx*dx + dy * dy);
	dx = dx / d;
	dy = dy / d;
	m_fMoveX = dx * m_fEnemySpeed*2;
	m_fMoveY = dy * m_fEnemySpeed*2;

}

void CEnemy_RIGHTHAND::Start(float InitialPositionX,float InitialPositionY) {
	PlayPosX = InitialPositionX;
	float dx = InitialPositionX - m_fXpos;
	float dy = InitialPositionY - m_fYpos;

	float d = sqrt(dx*dx + dy * dy);
	dx = dx / d;
	dy = dy / d;
	m_fMoveX = dx * m_fEnemySpeed*2;
	m_fMoveY = dy * m_fEnemySpeed*2;

}

void CEnemy_RIGHTHAND::Update(float Xpos, float Ypos) {
	//最終形態
	if (m_Limit) {
		//本体に戻る
		if (m_MoveEndFlag) {
			if (m_fXpos < PlayPosX) {
				m_fXpos += m_fMoveX;
				m_fYpos += m_fMoveY;
			}
			else
			{
				m_MoveFlag = false;
			}
			return;
		}

		if (!m_MoveFlag) {
			return;
		}

		if (m_fXpos > PlayPosX&&m_AimTime == 0) {

			m_fXpos += m_fMoveX;
			m_fYpos += m_fMoveY;
		}
		else
		{

			if (m_AimTime == 0) {
				m_AimTime = AIMTIME;
			}
			else if (m_AimTime > 0)
			{
				//ロックオン中
				m_AimTime -= 1 * CUtilities::GetFrameSecond();
				/*if (m_fXpos > Xpos) {
					m_fXpos -= EnemySpeed * 2;
					if (m_fXpos < Xpos) {
						m_fXpos = Xpos;
					}
				}
				else if (m_fXpos < Xpos)
				{
					m_fXpos += EnemySpeed * 2;
					if (m_fXpos > Xpos) {
						m_fXpos = Xpos;
					}
				}*/
				return;
			}
			//叩きつける
			if (m_fMoveY < 0) {
				m_fMoveY = EnemySpeed;
			}
			if (m_AimTime <= 0) {

				m_fYpos += m_fMoveY * 5;
			}
		}



		return;
	}


	//本体に戻る
	if (m_MoveEndFlag) {
		if (m_fXpos < PlayPosX) {
			m_fXpos += m_fMoveX;
			m_fYpos += m_fMoveY;
		}
		else
		{
			m_MoveFlag = false;
		}
		return;
	}

	//画面外に出ると戻る
	if (m_fXpos<0 || m_fXpos>g_pGraphics->GetTargetWidth() || m_fYpos<0 || m_fYpos>g_pGraphics->GetTargetHeight()) {
		m_MoveFlag = false;
	}

	if (!m_MoveFlag) {
		return;
	}

	//プレイヤーの座標に飛んでいく
	if (m_fXpos> PlayPosX&&m_AimTime==0) {

		m_fXpos += m_fMoveX;
		m_fYpos += m_fMoveY;
	}
	else
	{

		if (m_AimTime==0) {
			m_AimTime = AIMTIME;
		}
		else if(m_AimTime>0)
		{
			//ロックオン中
			m_AimTime -= 1 * CUtilities::GetFrameSecond();
			if (m_fXpos>Xpos) {
				m_fXpos -= EnemySpeed*2;
				if (m_fXpos < Xpos) {
					m_fXpos = Xpos;
				}
			}
			else if(m_fXpos<Xpos)
			{
				m_fXpos += EnemySpeed*2;
				if (m_fXpos > Xpos) {
					m_fXpos = Xpos;
				}
			}
			return;
		}
		//叩きつける
		if (m_fMoveY<0) {
			m_fMoveY = EnemySpeed;
		}
		if (m_AimTime<=0) {

			m_fYpos += m_fMoveY * 5;
		}
	}

}

void CEnemy_RIGHTHAND::CollisionStage() {

	float ox = 0, oy = 0;
	float mx = m_fXpos, my = m_fYpos;
	/*if (mx < 200) {
		ox = 200 - mx;
	}
	else*/ if (mx > 800)
	{
		ox = 800 - mx;

	}
	if (my > 600) {
		oy = 600 - my-10;
	}

	if (ox || oy) {

		int x = 0;
		if (m_fMoveY) {
			int x = 0;
			//m_fMoveY = 1;
		}
	}
	m_fXpos += ox;
	m_fYpos += oy;
	if (oy < 0 && m_fMoveY>0) {
		m_fMoveY = 0;
		m_MoveEndFlag = true;
		Start(m_InitialPositionX,m_InitialPositionY);
		m_Fire = true;
	}
	else if (oy > 0 && m_fMoveY < 0) {
		m_fMoveY = 0;
		m_MoveEndFlag = true;
		Start(m_InitialPositionX, m_InitialPositionY);
		m_Fire = true;
	}
	if (ox < 0 && m_fMoveX>0) {
		m_fMoveX *= -1;
		m_bRevers = false;
		m_MoveEndFlag = true;
		Start(m_InitialPositionX, m_InitialPositionY);
		m_Fire = true;
	}
	else if (ox > 0 && m_fMoveX < 0) {
		m_fMoveX *= -1;
		m_bRevers = true;
		m_MoveEndFlag = true;
		Start(m_InitialPositionX, m_InitialPositionY);
		m_Fire = true;
	}
}
void CEnemy_RIGHTHAND::Render(float Xpos, float Ypos) {
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, EnemyRadius, MOF_COLOR_GREEN);

}
void CEnemy_RIGHTHAND::Release() {

}