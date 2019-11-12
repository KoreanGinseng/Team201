/**
 * @file Enemy_POISONKURIBIO.cpp
 * @brief 毒クリボー
 * @author 大西永遠
 * @date 更新日（11/12）
 */

#include	"Enemy_POISONKURIBO.h"

CEnemy_POISONKURIBO::CEnemy_POISONKURIBO() :
	CEnemyMove()
{
}
CEnemy_POISONKURIBO::~CEnemy_POISONKURIBO() {
}
void CEnemy_POISONKURIBO::Initialize() {
	m_Texture.Load("Effect03.png");
	m_fXpos = 500;
	m_fYpos = 500;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -1 * m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
	m_bShow = false;

	SpriteAnimationCreate anim[] = {
				{
					"エフェクト",
					0,0,180,180,
					FALSE,{{3,0,0},{3,1,0},{3,2,0},{3,3,0},{3,4,0},{3,5,0},{3,6,0},{3,7,0},{3,8,0},{3,9,0},{3,10,0},
							{3,0,1},{3,1,1},{3,2,1},{3,3,1},{3,4,1},{3,5,1},{3,6,1},{3,7,1},{3,8,1},{3,9,1},{3,10,1}}
				},
	};
	m_Motion.Create(anim,1);
}

void CEnemy_POISONKURIBO::Update(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
		if (!m_bEnd) {
			return;
		}
		if (!m_bShow) {
			m_bShow = true;
		}
	}

	if (m_bShow) {
		m_Motion.AddTimer(CUtilities::GetFrameSecond());
		m_SrcRect = m_Motion.GetSrcRect();
		if (m_Motion.IsEndMotion()) {
			m_bShow = false;
			Initialize();
		}
		return;
	}
	if (m_bEnd) {
		return;
	}

//ここからmove
	Gravity();



	if (m_fYpos - AtackRangeY < Ypos&&m_fYpos + EnemyRadius > Ypos) {
		if (m_bRevers) {
			if (m_fXpos + AtackRangeX > Xpos&&m_fXpos < Xpos) {
				m_fMoveX = 0;
				return;
			}
		}
		else {
			if (m_fXpos - AtackRangeX < Xpos&&m_fXpos > Xpos) {
				m_fMoveX = 0;
				return;
			}
		}
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

	AtackRange(Xpos, Ypos);

	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}

void CEnemy_POISONKURIBO::Render(float Xpos, float Ypos) {
	if (m_bShow) {
		m_Texture.Render(m_fXpos-Exp_Pos, m_fYpos-Exp_Pos, m_SrcRect);
	}
	if (m_bEnd) {
		return;
	}
	//m_Atack->Render();
	CGraphicsUtilities::RenderFillCircle(m_fXpos, m_fYpos, EnemyRadius, MOF_COLOR_GREEN);
}

void CEnemy_POISONKURIBO::Release() {
	m_Texture.Release();
	m_Motion.Release();
}