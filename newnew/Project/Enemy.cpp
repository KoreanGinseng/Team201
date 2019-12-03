#include "Enemy.h"



CEnemy::CEnemy()
	: CSubstance()
{

}


CEnemy::~CEnemy()
{
	Release();
}

void CEnemy::Initialize(void)
{
	CCharacter::Initialize();
	if (m_EnemyType == ENEMY_BAT)
	{
		m_bCollision = false;
	}
}

void CEnemy::Update(void)
{
	m_MvCntrl.Update();
	m_Anim.Update();
	
	m_Pos += m_MvCntrl.GetMove();

	if (IsStageOver())
	{
		m_bDead = true;
		m_bShow = false;
	}

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
	if (m_MvCntrl.GetMove().x < 0)
	{
		if (over.x > 0)
		{
			m_MvCntrl.MoveReverse();
		}
	}
	else if (m_MvCntrl.GetMove().x > 0)
	{
		if (over.x < 0)
		{
			m_MvCntrl.MoveReverse();
		}
	}

	if (m_MvCntrl.GetMove().y > 0)
	{
		if (over.y < 0)
		{
			m_MvCntrl.SetMove(Vector2(m_MvCntrl.GetMove().x, 0));
		}
	}
}
