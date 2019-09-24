#include "EnemyMove.h"


CEnemyMove::CEnemyMove() :
	m_bEnd(false),
	m_bRevers(false),
	m_bXpos(0.0f),
	m_bYpos(0.0f),
	m_bTimer(0),
	m_bAtackTimer(0),
	m_bCooltime(0),
	m_bMoveX(0.0f),
	m_bMoveY(0.0f){
}

CEnemyMove::~CEnemyMove() {
}

void CEnemyMove::Initialize(int Type) {
	m_bEnd = false;
	m_bRevers = false;
	m_bXpos = 500;
	m_bYpos = 100;
	m_bTimer = 0;
	m_bAtackTimer = AtackTimer;
	m_bCooltime = 0;
	m_EnemySpeed = EnemySpeed;
	m_bMoveX = -1*m_EnemySpeed;
	m_bMoveY = m_EnemySpeed;
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
		m_bMoveY += GRAVITY;
		if (m_bMoveY >= 20.0f) {
			m_bMoveY = 20.0f;
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

	if (m_bYpos - 50 < Ypos&&m_bYpos + 10 > Ypos) {
		if (m_bRevers) {
			if (m_bXpos + 50 > Xpos&&m_bXpos < Xpos) {
				m_bAtack.KUpdate(m_bXpos, m_bYpos, m_bRevers);
				return;
			}
		}
		else {
			if (m_bXpos - 50 < Xpos&&m_bXpos > Xpos) {
				m_bAtack.KUpdate(m_bXpos, m_bYpos, m_bRevers);
				return;
			}
		}
	}

	
	m_bXpos += m_bMoveX;
	m_bYpos += m_bMoveY;
}

void CEnemyMove::NUpdate() {
	if (m_bEnd) {
		m_bTimer = 0;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
			m_bEnd = false;
		}
		return;
	}
	if (m_bTimer > 0) {
		if (g_pInput->IsKeyPush(MOFKEY_A)) {
			m_bEnd = true;
		}
		m_bTimer -= 1 * CUtilities::GetFrameSecond();
		return;
	}

	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bTimer=Timer;
		return;
	}
	m_bXpos += m_bMoveX;
	m_bYpos += m_bMoveY;
}

void CEnemyMove::TUpdate(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	float dx = Xpos - m_bXpos;
	if (dx > 0) {
		m_bRevers = false;
	}
	else
	{
		m_bRevers = true;
	}
	float dy = Ypos - m_bYpos;
	float d = sqrt(dx*dx + dy * dy);
	dx /= d;
	dy /= d;
	m_bXpos += (dx * m_bMoveX);

	m_bYpos += (dy * m_bMoveY);
}

void CEnemyMove::BUpdate(float Xpos, float Ypos) {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	if (m_bYpos<=Ypos) {

		if (m_bRevers) {
		
			if (m_bXpos + 200 > Xpos&&m_bXpos<Xpos) {
				m_bYpos += 2*m_bMoveY;
				if (m_Motion.GetMotionNo()==BAT_MOVE) {
					m_Motion.ChangeMotion(BAT_DOWN);
				}
				return;
			}
		}
		else {
			if (m_bXpos-200<Xpos&&m_bXpos>Xpos) {

				m_bYpos += 2*m_bMoveY;
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
	m_bXpos += m_bMoveX;
}

void CEnemyMove::KOUpdate() {
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		m_bEnd = !m_bEnd;
	}
	
	if (m_bAtackTimer>=0&& m_bCooltime <= 0) {
		m_bAtackTimer -= 1 * CUtilities::GetFrameSecond();
		if (m_bAtackTimer<0) {
			m_bCooltime = CoolTime;
		}
	}
	if (m_bCooltime>=0&&m_bAtackTimer<=0) {
		m_bCooltime -= 1 * CUtilities::GetFrameSecond();
		if (m_bCooltime < 0) {
			m_bAtackTimer = AtackTimer;
		}
	}
	
}

void CEnemyMove::CollisionStage(float ox, float oy, int Type) {
	if (Type==2) {
		m_bMoveX = m_EnemySpeed;
		m_bMoveY = m_EnemySpeed;
		return;
	}
	if (Type==3) {
		m_bMoveY = m_EnemySpeed;
	}
	m_bXpos += ox;
	m_bYpos += oy;
	if (oy<0&&m_bMoveY>0) {
		m_bMoveY = 0;
	}else if (oy > 0 && m_bMoveY<0) {
		m_bMoveY = 0;
	}
	if (ox < 0 && m_bMoveX>0) {
		m_bMoveX *= -1;
		m_bRevers = false;
	}
	else if (ox > 0 && m_bMoveX < 0) {
		m_bMoveX *= -1;
		m_bRevers = true;
	}
}

void CEnemyMove::Render(float Xpos, float Ypos,int Type) {
	if (m_bEnd) {
		return;
	}
	m_bAtack.Render();
	CGraphicsUtilities::RenderFillCircle(m_bXpos,m_bYpos,10,MOF_COLOR_GREEN);
	if (Type == ENEMY_KOTEIHOUDAI) {
		if (m_bAtackTimer>0) {
			float x = Xpos - m_bXpos;
			float y = Ypos - m_bYpos;




			float tx = sqrtf(x*x);
			float ty = sqrtf(y*y);

			if (Xpos <= m_bXpos) {
				tx = -tx;
			}

			if (Ypos <= m_bYpos) {
				ty = -ty;
			}
			CGraphicsUtilities::RenderLine(m_bXpos, m_bYpos, tx * 1000, ty * 1000, MOF_COLOR_RED);
		}
	}
	CGraphicsUtilities::RenderString(100,100,"(%.0f,%.0f)", m_bXpos, m_bYpos);
	CRectangle dr=m_SrcRect;
	float px = m_bXpos;
	float py = m_bYpos;
	if (m_bRevers) {
		float temp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = temp;
	}
		m_Texture.Render(m_bXpos, m_bYpos, dr);
}