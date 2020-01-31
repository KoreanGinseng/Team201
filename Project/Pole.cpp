#include "Pole.h"



CPole::CPole(void) :
	CTargetObj()
{
	m_Type = OBJECT_POLE;
	m_bReverse = true;
	m_PoleScale = 1.0f;
}


CPole::~CPole(void)
{
}

void CPole::Initialize(void)
{
}

void CPole::Render(const Vector2 & screenPos)
{
	if (!m_bShow)
	{
		return;
	}
	CRectangle r = GetSrcRect();
	if (!m_bReverse)
	{
		r.Left = GetSrcRect().Right;
		r.Right = GetSrcRect().Left;
	}
	//m_pTexture->Render(screenPos.x, screenPos.y, r);
	float h = r.GetHeight();
	m_pTexture->RenderScale(screenPos.x, screenPos.y + h, m_PoleScale, m_PoleScale, r, TEXALIGN_BOTTOM);

	Vector2 scroll = CCamera2D::GetSScroll();

#ifdef _DEBUG
	if (gbDebug)
	{
		CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
		CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
		for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
		{
			CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left,
				screenPos.y + m_SrcRectArray[i].Top + m_SrcRectArray[i].GetHeight() * (1.0f - m_PoleScale),
				screenPos.x + m_SrcRectArray[i].Right - m_SrcRectArray[i].GetWidth() * (1.0f - m_PoleScale),
				screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
			CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
		}
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 60, "SubStatus : %d", m_SubStatus);
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 90, "Scale     : %.1f", m_PoleScale);
	}
#endif // _DEBUG

	CRectangle sRect = GetRect();
	if (m_bTarget)
	{
		CGraphicsUtilities::RenderRect(sRect - scroll, MOF_COLOR_GREEN);
	}
}

bool CPole::OverValue(CRectangle rec, Vector2 & out)
{
	bool re = false;
	if (m_SubStatus == SUBSTATUS_TRIP)
	{
		return re;
	}
	CRectangle rect = GetRectArray(0);
	CRectangle prec = rec;
	rect.Right -= rect.GetWidth() * (1.0f - m_PoleScale);
	rect.Top += rect.GetHeight() * (1.0f - m_PoleScale);
	if (!rect.CollisionRect(prec))
	{
		return re;
	}
	CRectangle br = prec;
	br.Expansion(-6, 0);
	br.Top = br.Bottom - 1;
	if (rect.CollisionRect(br))
	{
		re = true;
		float result = br.Bottom - rect.Top;
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
	if (rect.CollisionRect(rr))
	{
		re = true;
		float result = rr.Right - rect.Left;
		out.x -= result;
		prec.Left -= result;
		prec.Right -= result;
	}
	if (rect.CollisionRect(lr))
	{
		re = true;
		float result = rect.Right - lr.Left;
		out.x += result;
		prec.Left += result;
		prec.Right += result;
	}
	return re;
}

void CPole::SetPoleScale(const float & scale)
{
	m_PoleScale = scale;
}

CRectangle CPole::GetRect(void)
{
	return CRectangle(m_Pos.x + m_SrcRectArray[0].Left, m_Pos.y + m_SrcRectArray[0].Top + m_SrcRectArray[0].GetHeight() * (1.0f - m_PoleScale), m_Pos.x + m_SrcRectArray[0].Right - m_SrcRectArray[0].GetWidth() * (1.0f - m_PoleScale), m_Pos.y + m_SrcRectArray[0].Bottom);
}
