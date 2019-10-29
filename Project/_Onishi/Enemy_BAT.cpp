/**
 * @file Enemy_BAT.cpp
 * @brief 蝙蝠の動き
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#include	"Enemy_BAT.h"

CENEMY_BAT::CENEMY_BAT():
CEnemyMove() {

}
CENEMY_BAT::~CENEMY_BAT() {

}

void CENEMY_BAT::Initialize() {
	m_fXpos = 500;
	m_fYpos = 100;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
	m_Texture.Load("TestEnemy.png");

	SpriteAnimationCreate anim[] = {
		{
			"BAT_MOVE",
			0,0,
			48,48,
			TRUE,{{5,0,1},{5,1,1},{5,2,1}}
		},
		{
			"BAT_DOWN",
			0,0,
			48,48,
			TRUE,{{5,0,0},{5,1,0},{5,2,0}}
		},
	};
	m_Motion.Create(anim, BAT_ANIMCOUNT);
}

void CENEMY_BAT::Update(float Xpos, float Ypos){
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_fYpos <= Ypos) {

		if (m_bRevers) {

			if (m_fXpos + 200 > Xpos&&m_fXpos < Xpos) {
				m_fYpos += 2 * m_fMoveY;
				if (m_Motion.GetMotionNo() == BAT_MOVE) {
					m_Motion.ChangeMotion(BAT_DOWN);
				}
				return;
			}
		}
		else {
			if (m_fXpos - 200 < Xpos&&m_fXpos > Xpos) {

				m_fYpos += 2 * m_fMoveY;
				if (m_Motion.GetMotionNo() == BAT_MOVE) {
					m_Motion.ChangeMotion(BAT_DOWN);
				}
				return;
			}
		}
	}
	if (m_Motion.GetMotionNo() == BAT_DOWN) {
		m_Motion.ChangeMotion(BAT_MOVE);
	}
	m_fXpos += m_fMoveX;
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

void CENEMY_BAT::Render(float Xpos, float Ypos) {
	if (m_bEnd) {
		return;
	}
	CRectangle dr = m_SrcRect;
	float px = m_fXpos;
	float py = m_fYpos;
	if (m_bRevers) {
		float temp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = temp;
	}
	m_Texture.Render(m_fXpos, m_fYpos, dr);
}

void CENEMY_BAT::Release() {
	m_Texture.Release();
	m_Motion.Release();
}