#include "EnemyMove.h"


CEnemyMove::CEnemyMove() :
	m_bEnd(false),
	m_bRevers(false),
	m_fXpos(0.0f),
	m_fYpos(0.0f),
	m_fTimer(0),
	m_fAtackTimer(0),
	m_fCooltime(0),
	m_fMoveX(0.0f),
	m_fMoveY(0.0f){
}

CEnemyMove::~CEnemyMove() {
}

void CEnemyMove::Initialize(int Type) {
	m_bEnd = false;
	m_bRevers = false;
	m_fXpos = 500;
	m_fYpos = 100;
	m_fTimer = 0;
	m_fAtackTimer = AtackTimer;
	m_fCooltime = 0;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -1*m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;
	m_Texture.Load("TestEnemy.png");
	switch (Type)
	{
		case ENEMY_BAT: {
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
			break;
		}
	}

}

void CEnemyMove::Update(float Xpos, float Ypos,int Type) {
	if (Type!=2) {
		m_fMoveY += GRAVITY;
		if (m_fMoveY >= 20.0f) {
			m_fMoveY = 20.0f;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_F1)) {
		Initialize(Type);
	}

	switch (Type)
	{
	case ENEMY_KURIBO:
		KUpdate(Xpos,Ypos);
		break;
	case ENEMY_NOKONOKO:
		NUpdate();
		break;
	case ENEMY_TERESA:
		TUpdate(Xpos, Ypos);
		break;
	case ENEMY_BAT:
		BUpdate(Xpos, Ypos);
		break;
	case ENEMY_KOTEIHOUDAI:
		KOUpdate();
		break;
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	
}

void CEnemyMove::KUpdate(float Xpos,float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_bEnd) {
		return;
	}

	if (m_fYpos - 50 < Ypos&&m_fYpos + 10 > Ypos) {
		if (m_bRevers) {
			if (m_fXpos + 50 > Xpos&&m_fXpos < Xpos) {
				m_Atack.KUpdate(m_fXpos, m_fYpos, m_bRevers);
				return;
			}
		}
		else {
			if (m_fXpos - 50 < Xpos&&m_fXpos > Xpos) {
				m_Atack.KUpdate(m_fXpos, m_fYpos, m_bRevers);
				return;
			}
		}
	}

	
	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}

void CEnemyMove::NUpdate() {
	if (m_bEnd) {
		m_fTimer = 0;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
			m_bEnd = false;
		}
		return;
	}
	if (m_fTimer > 0) {
		if (g_pInput->IsKeyPush(MOFKEY_A)) {
			m_bEnd = true;
		}
		m_fTimer -= 1 * CUtilities::GetFrameSecond();
		return;
	}

	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_fTimer=Timer;
		return;
	}
	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}

void CEnemyMove::TUpdate(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	float dx = Xpos - m_fXpos;
	if (dx > 0) {
		m_bRevers = true;
	}
	else
	{
		m_bRevers = false;
	}
	float dy = Ypos - m_fYpos;
	float d = sqrt(dx*dx + dy * dy);
	dx /= d;
	dy /= d;
	m_fXpos += (dx * m_fMoveX);

	m_fYpos += (dy * m_fMoveY);
}

void CEnemyMove::BUpdate(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_fYpos<=Ypos) {

		if (m_bRevers) {
		
			if (m_fXpos + 200 > Xpos&&m_fXpos<Xpos) {
				m_fYpos += 2*m_fMoveY;
				if (m_Motion.GetMotionNo()==BAT_MOVE) {
					m_Motion.ChangeMotion(BAT_DOWN);
				}
				return;
			}
		}
		else {
			if (m_fXpos-200<Xpos&&m_fXpos>Xpos) {

				m_fYpos += 2*m_fMoveY;
				if (m_Motion.GetMotionNo() == BAT_MOVE) {
					m_Motion.ChangeMotion(BAT_DOWN);
				}
				return;
			}
		}
	}
	if (m_Motion.GetMotionNo()== BAT_DOWN) {
		m_Motion.ChangeMotion(BAT_MOVE);
	}
	m_fXpos += m_fMoveX;
}

void CEnemyMove::KOUpdate() {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	
	if (m_fAtackTimer>=0&& m_fCooltime <= 0) {
		m_fAtackTimer -= 1 * CUtilities::GetFrameSecond();
		if (m_fAtackTimer<0) {
			m_fCooltime = CoolTime;
		}
	}
	if (m_fCooltime>=0&&m_fAtackTimer<=0) {
		m_fCooltime -= 1 * CUtilities::GetFrameSecond();
		if (m_fCooltime < 0) {
			m_fAtackTimer = AtackTimer;
		}
	}
	
}

void CEnemyMove::CollisionStage(float ox, float oy, int Type) {
	if (Type==2) {
		m_fMoveX = m_fEnemySpeed;
		m_fMoveY = m_fEnemySpeed;
		return;
	}
	if (Type==3) {
		m_fMoveY = m_fEnemySpeed;
	}
	m_fXpos += ox;
	m_fYpos += oy;
	if (oy<0&&m_fMoveY>0) {
		m_fMoveY = 0;
	}else if (oy > 0 && m_fMoveY<0) {
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

void CEnemyMove::Render(float Xpos, float Ypos,int Type) {
	if (m_bEnd) {
		return;
	}
	m_Atack.Render();
	CGraphicsUtilities::RenderFillCircle(m_fXpos,m_fYpos,10,MOF_COLOR_GREEN);
	if (Type == ENEMY_KOTEIHOUDAI) {
		if (m_fAtackTimer>0) {
			float x = Xpos - m_fXpos;
			float y = Ypos - m_fYpos;




			float tx = sqrtf(x*x);
			float ty = sqrtf(y*y);

			if (Xpos <= m_fXpos) {
				tx = -tx;
			}

			if (Ypos <= m_fYpos) {
				ty = -ty;
			}
			CGraphicsUtilities::RenderLine(m_fXpos, m_fYpos, tx * 1000, ty * 1000, MOF_COLOR_RED);
		}
	}
	CGraphicsUtilities::RenderString(100,100,"(%.0f,%.0f)", m_fXpos, m_fYpos);
	CRectangle dr=m_SrcRect;
	float px = m_fXpos;
	float py = m_fYpos;
	if (m_bRevers) {
		float temp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = temp;
	}
		m_Texture.Render(m_fXpos, m_fYpos, dr);
}