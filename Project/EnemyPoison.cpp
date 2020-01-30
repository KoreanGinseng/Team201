#include "EnemyPoison.h"



CEnemyPoison::CEnemyPoison(void) :
	CEnemy(),
	m_bDmg(false),
	m_DmgScale(Vector2(1, 1)),
	m_bAttack(false),
	m_pPoisonTexture(nullptr),
	m_PoisonMotion()
{
	m_EnemyType = ENEMY_POISUNMASH;
	m_Spd.x = -3.0f;
	m_OffsetWait = 240;
}


CEnemyPoison::~CEnemyPoison(void)
{
}

void CEnemyPoison::Initialize(void)
{
	CEnemy::Initialize();
}

void CEnemyPoison::Update(void)
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

	for (int i = 0; i < m_ShotArray.GetArrayCount(); i++)
	{
		m_ShotArray[i]->Update();
	}

	if (m_bDmg)
	{
		m_Move = Vector2(0, 0);
		m_DmgScale.x += 0.1f;
		m_DmgScale.y -= 0.05f;
		if (m_DmgScale.y < 0)
		{
			m_DmgScale.y = 0;
			//ここで毒をまく処理
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

void CEnemyPoison::Render(const Vector2 & screenPos)
{
	if (!m_bShow)
	{
		return;
	}
	CRectangle r = GetSrcRect();
	float dx = r.GetWidth() * 0.5f;
	if (!m_bReverse)
	{
		r.Left = GetSrcRect().Right;
		r.Right = GetSrcRect().Left;
	}

	if (m_bDmg)
	{
		m_pTexture->RenderScale(screenPos.x + dx, screenPos.y + r.GetHeight(), m_DmgScale.x, m_DmgScale.y, r, TEXTUREALIGNMENT_BOTTOMCENTER);
		if (m_DmgScale.y <= 0)
		{
			CRectangle rect = GetRect();
			Vector2 scroll = CCamera2D::GetSScroll();
			Vector2 pos = rect.GetTopLeft() - scroll;
			CTexturePtr pt = g_pTextureManager->GetTexture("Poison_Dmg.png");
			float xw = (pt->GetWidth() * 0.6f - rect.GetWidth()) * 0.5f;
			float yh = (pt->GetHeight() * 0.5f - rect.GetHeight()) * 0.5f;
			pt->RenderScale(pos.x - xw, pos.y - yh, 0.6f, 0.5f);
		}
	}
	else
	{
		m_pTexture->Render(screenPos.x, screenPos.y, r);
	}
	Vector2 scroll = CCamera2D::GetSScroll();
	for (int i = 0; i < m_ShotArray.GetArrayCount(); i++)
	{
		Vector2 sp = ScreenTransration(scroll, m_ShotArray[i]->GetPos());
		m_ShotArray[i]->Render(sp);
	}
#ifdef _DEBUG
	if (gbDebug)
	{
		CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
		CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
		for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
		{
			CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
				screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
			CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
			CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 60, "%d", m_Motion.GetFrameNo());
		}
	}
#endif // _DEBUG
}

void CEnemyPoison::RenderCircle(const Vector2 & screenPos)
{
	if (!m_bShow)
	{
		return;
	}
	CRectangle r = GetSrcRect();
	float dx = r.GetWidth() * 0.5f;
	if (!m_bReverse)
	{
		r.Left = GetSrcRect().Right;
		r.Right = GetSrcRect().Left;
	}
	if (m_bDmg)
	{
		m_pTexture->RenderScale(screenPos.x + dx, screenPos.y + r.GetHeight(), m_DmgScale.x, m_DmgScale.y, r, MOF_ARGB(128, 255, 255, 255), TEXTUREALIGNMENT_BOTTOMCENTER);
	}
	else
	{
		m_pTexture->Render(screenPos.x, screenPos.y, r, MOF_ARGB(128, 255, 255, 255));
	}
}

void CEnemyPoison::Move(void)
{
	if (m_Motion.GetFrameNo() >= 9 && m_Motion.GetMotionNo() == 1)
	{
		Vector2 shotPos = m_Pos + Vector2(-10, 30);
		m_ShotArray[0]->Fire(shotPos);
	}
	m_Move.x += m_Spd.x;

	m_Move.x = MOF_CLIPING(m_Move.x, -MASH_MAXSPD, MASH_MAXSPD);

	//ATTACK
	if (m_bAttack)
	{
		m_Move.x = 0;
		if (m_ShotArray.GetArrayCount() < 1)
		{
			m_ShotArray.Add(NEW CPoisonShot());
			m_ShotArray[0]->Initialize();
			m_Motion.ChangeMotion(1);
		}
		else if (!m_ShotArray[0]->IsShot() && m_Motion.GetMotionNo() == 0)
		{
			m_Motion.ChangeMotion(1);
		}
		//m_bAttack = false;
		return;
	}
	if (m_bReverse)
	{
		float px = CCordinate::GetPlayerPos().x;
		if (m_Pos.x - 64 * 3 < px && m_Pos.x > px)
		{
			m_Move.x = 0;
			m_bAttack = true;
		}
	}
}

void CEnemyPoison::Animation(void)
{
	if (m_Motion.GetMotionNo() == 1 && m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(0);
		m_bAttack = false;
	}
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
}

CRectangle CEnemyPoison::GetRect(void)
{
	CRectangle rec = CCharacter::GetRect();
	rec.Expansion(-30, -10);
	if (m_bDmg)
	{
		rec.Top = rec.Bottom - 10;
	}
	return rec;
}

CRectangle CEnemyPoison::GetSrcAddRect(void)
{
	CRectangle rect(0, 0, GetSrcRect().GetWidth(), GetSrcRect().GetHeight());
	rect.Expansion(-30, -10);
	return rect;
}

bool CEnemyPoison::Dmg(const int & dmg)
{
	m_HP -= dmg;
	if (m_HP <= 0)
	{
		m_HP = 0;
		m_bDmg = true;
	}
	return true;
}

bool CEnemyPoison::OverValue(CRectangle rec, Vector2 & out)
{
	bool re = false;
	CRectangle r = rec;
	CRectangle er = GetRect();
	if (m_ShotArray.GetArrayCount() > 0)
	{
		CRectangle sr = m_ShotArray[0]->GetRect();
		if (sr.CollisionRect(r))
		{
			re = true;
			out.x += r.Right - sr.Left;
			r.Left += r.Right - sr.Left;
			r.Right += r.Right - sr.Left;
			m_ShotArray[0]->SetShot(false);
		}
	}
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

	return re;
}
