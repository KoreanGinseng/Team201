#include "EnemyMove.h"


CEnemyMove::CEnemyMove() :
	m_bEnd(false),
	m_bRevers(false),
	m_fXpos(0.0f),
	m_fYpos(0.0f),
	m_fAtackTimer(0),
	m_fCooltime(0),
	m_fMoveX(0.0f),
	m_fMoveY(0.0f){
}

CEnemyMove::~CEnemyMove() {
}

void CEnemyMove::Initialize() {
	/*m_bEnd = false;
	m_bRevers = false;
	
	m_fTimer = 0;
	m_fEnemySpeed = EnemySpeed;
	m_fMoveX = -1*m_fEnemySpeed;
	m_fMoveY = m_fEnemySpeed;*/
	//m_fAtackTimer = AtackTimer;
	//m_fCooltime = 0;
	//m_Texture.Load("TestEnemy.png");
	//switch (Type)
	//{
	//	case ENEMY_BAT: {
	//		SpriteAnimationCreate anim[] = {
	//			{
	//				"BAT_MOVE",
	//				0,0,
	//				48,48,
	//				TRUE,{{5,0,1},{5,1,1},{5,2,1}}
	//			},
	//			{
	//				"BAT_DOWN",
	//				0,0,
	//				48,48,
	//				TRUE,{{5,0,0},{5,1,0},{5,2,0}}
	//			},
	//		};
	//		m_Motion.Create(anim, BAT_ANIMCOUNT);
	//		break;
	//	}
	//}

}

void CEnemyMove::Update(float Xpos, float Ypos) {
	/*if (Type!=2) {
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
	m_SrcRect = m_Motion.GetSrcRect();*/
	
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
				m_Atack.Update(m_fXpos, m_fYpos, m_bRevers);
				return;
			}
		}
		else {
			if (m_fXpos - 50 < Xpos&&m_fXpos > Xpos) {
				m_Atack.Update(m_fXpos, m_fYpos, m_bRevers);
				return;
			}
		}
	}

	
	m_fXpos += m_fMoveX;
	m_fYpos += m_fMoveY;
}

void CEnemyMove::NUpdate() {
	
}

void CEnemyMove::TUpdate(float Xpos, float Ypos) {
	
}

void CEnemyMove::BUpdate(float Xpos, float Ypos) {
	
}

void CEnemyMove::KOUpdate() {
	
	
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

void CEnemyMove::Render(float Xpos, float Ypos) {
	/*if (m_bEnd) {
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
		m_Texture.Render(m_fXpos, m_fYpos, dr);*/
}

void CEnemyMove::Release() {
	
}