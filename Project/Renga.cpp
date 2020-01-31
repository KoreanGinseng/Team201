#include "Renga.h"



CRenga::CRenga(void) :
	CTargetObj()
{
	m_Type = OBJECT_RENGA;
	m_bSelectTarget = false;
}


CRenga::~CRenga(void)
{
}

void CRenga::Initialize(void)
{
	CTargetObj::Initialize();
	m_bShow = true;
	m_bDead = false;
}

void CRenga::Update(void)
{
}

void CRenga::Render(const Vector2 & screenPos)
{
	if (!m_bShow)
	{
		return;
	}
	Vector2 scroll = CCamera2D::GetSScroll();
	m_pTexture->Render(m_Pos.x - scroll.x, m_Pos.y - scroll.y);
#ifdef _DEBUG
	if (gbDebug)
	{
		CGraphicsUtilities::RenderRect(GetRect() - scroll, MOF_COLOR_BLUE);
	}
#endif // _DEBUG
}

CRectangle CRenga::GetRect(void)
{
	return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_pTexture->GetWidth(), m_pTexture->GetHeight());
}

bool CRenga::OverValue(CRectangle rect, Vector2 & out)
{
	bool re = false;
	CRectangle rec = GetRect();
	CRectangle prec = rect;
	if (!rec.CollisionRect(prec))
	{
		return re;
	}
	CRectangle br = prec;
	br.Expansion(-6, 0);
	br.Top = br.Bottom - 1;
	if (rec.CollisionRect(br))
	{
		re = true;
		float result = br.Bottom - rec.Top;
		out.y -= result;
		prec.Top -= result;
		prec.Bottom -= result;
	}
	CRectangle rr = prec;
	rr.Expansion(0, -6);
	rr.Left = rr.Right - 1;
	CRectangle lr = prec;
	lr.Expansion(0, -6);
	lr.Right = lr.Left + 1;
	if (rec.CollisionRect(rr))
	{
		re = true;
		float result = rr.Right - rec.Left;
		out.x -= result;
		prec.Left -= result;
		prec.Right -= result;
	}
	if (rec.CollisionRect(lr))
	{
		re = true;
		float result = rec.Right - lr.Left;
		out.x += result;
		prec.Left += result;
		prec.Right += result;
	}
	CRectangle tr = prec;
	tr.Expansion(-6, 0);
	tr.Bottom = tr.Top + 1;
	if (rec.CollisionRect(tr))
	{
		re = true;
		float result = tr.Top - rec.Bottom;
		out.y -= result;
		prec.Top -= result;
		prec.Bottom -= result;
	}
	return re;
}
