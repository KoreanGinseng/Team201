#include "Enemy.h"



CEnemy::CEnemy(void) :
CSubstance(),
m_bGravity(true)
{
	m_SubType = SUB_ENE;
	m_SubStatus = SUBSTATUS_NOMAL;
	m_bReverse = true;
	m_Spd.y = GRAVITY;
	m_bShow = false;
}


CEnemy::~CEnemy(void)
{
	Release();
}

void CEnemy::Initialize(void)
{
}

void CEnemy::Update(void)
{
	if (m_bDead)
	{
		return;
	}
	if (!m_bShow)
	{
		if (CCordinate::GetMainCameraRect().Right > m_Pos.x)
		{
			m_bShow = true;
		}
		return;
	}
	if (!m_bAnimStop)
	{
		Move();
	}
	if (CCordinate::IsCameraCntrl())
	{
		m_Move.x = 0;
		if (!m_bGravity)
		{
			m_Move.y = 0;
		}
	}

	if (m_bGravity)
	{
		m_Move.y += m_Spd.y;
		if (m_Move.y > GRAVITYMAX)
		{
			m_Move.y += GRAVITYMAX;
		}
	}

	m_Pos += m_Move;

	if (!m_bAnimStop)
	{
		Animation();
	}

	if (m_bAnimStop)
	{
		m_WaitCount--;
		if (m_WaitCount < 0)
		{
			m_WaitCount = 0;
			m_bAnimStop = false;
			m_SubStatus = SUBSTATUS_NOMAL;
		}
	}

	if (IsStageOver())
	{
		m_bDead = true;
		m_bShow = false;
	}
	if (m_Move.x < 0)
	{
		m_bReverse = true;
	}
	else if (m_Move.x > 0)
	{
		m_bReverse = false;
	}

	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

void CEnemy::Move(void)
{
}

void CEnemy::Animation(void)
{
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
}

bool CEnemy::OverValue(CRectangle rec, Vector2 & out)
{
	bool re = false;
	CRectangle r = rec;
	for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
	{
		CRectangle er = GetRectArray(i);
		//下埋まり値計算
		CRectangle brec = r;
		brec.Top = brec.Bottom + 1;
		brec.Expansion(-6, 0);
		if (er.CollisionRect(brec))
		{
			re = true;
			out.y += er.Top - brec.Bottom;
			r.Top += er.Top - brec.Bottom;
			r.Bottom += er.Top - brec.Bottom;
		}
		//左
		CRectangle lrec = r;
		lrec.Right = lrec.Left + 1;
		lrec.Expansion(0, -6);
		//右
		CRectangle rrec = r;
		rrec.Left = rrec.Right - 1;
		rrec.Expansion(0, -6);
		if (er.CollisionRect(lrec))
		{
			re = true;
			out.x += er.Right - lrec.Left;
			r.Left += er.Right - lrec.Left;
			r.Right += er.Right - lrec.Left;
		}
		if (er.CollisionRect(rrec))
		{
			re = true;
			out.x += er.Left - rrec.Right;
			r.Left += er.Left - rrec.Right;
			r.Right += er.Left - rrec.Right;
		}
		//ue
		CRectangle trec = r;
		trec.Bottom = trec.Top - 1;//
		trec.Expansion(-6, 0);//
		//上と当たり判定
		if (er.CollisionRect(trec))
		{
			re = true;
			//上の埋まりなのでチップした端から矩形の上端を
			out.y += er.Bottom - trec.Top;
			r.Top += er.Bottom - trec.Top;
			r.Bottom += er.Bottom - trec.Top;
		}
	}

	return re;
}

void CEnemy::CollisionStage(const Vector2 & over)
{
	m_Pos += over;
	Reverse(over);
}

void CEnemy::Reverse(const Vector2 & over)
{
	if (m_Move.x < 0)
	{
		if (over.x > 0)
		{
			m_Move.x = 0;
			m_Spd.x *= -1;
			m_bReverse = !m_bReverse;
		}
	}
	else if (m_Move.x > 0)
	{
		if (over.x < 0)
		{
			m_Move.x = 0;
			m_Spd.x *= -1;
			m_bReverse = !m_bReverse;
		}
	}

	if (m_Move.y > 0)
	{
		if (over.y < 0)
		{
			m_Move.y = 0;
		}
	}
}

bool CEnemy::Dmg(const CRectangle & pre, const int& preWait)
{
	CRectangle erec = GetRect();
	CRectangle prec = pre;

	if (m_DamageWait > 0 || preWait > 0)
	{
		return false;
	}
	m_DamageWait = 60;
	if (prec.Left < erec.Left)
	{
		m_Move.x = -5.0f;
		m_bReverse = false;
	}
	else
	{
		m_Move.x = 5.0f;
		m_bReverse = true;
	}
	//m_Motion.ChangeMotion(MOTION_DAMAGE);
	return true;
}

bool CEnemy::Dmg(const int & dmg)
{
	m_HP -= dmg;
	return true;
}

bool CEnemy::KnockBack(const CRectangle & pre, const int& preWait)
{
	CRectangle erec = GetRect();
	CRectangle prec = pre;
	if (preWait > 0)
	{
		return false;
	}
	if (prec.Left < erec.Left)
	{
		m_Pos.x += 64.0f;
		m_Pos.y -= 64.0f;
		m_bReverse = true;
	}
	else
	{
		m_Pos.x -= 64.0f;
		m_Pos.y -= 64.0f;
		m_bReverse = false;
	}
	return true;
}

CRectangle CEnemy::GetSrcAddRect(void)
{
	return CRectangle(0, 0, GetSrcRect().GetWidth(), GetSrcRect().GetHeight());
}
