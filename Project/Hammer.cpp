#include "Hammer.h"



CHammer::CHammer(void) :
	CTargetObj()
{
	m_SubType = SUB_ENE;
	m_Type = OBJECT_HAMMER;
}


CHammer::~CHammer(void)
{
}

void CHammer::Initialize(void)
{
	m_pHummerTexture = g_pTextureManager->GetTexture("Hummer-2.png");
	m_OffsetWait = 300;
	m_WaitCount = m_OffsetWait;
	deg = 90;
	m_Rote = MOF_ToRadian(deg);
	m_CosSpd = 0.05f;
	m_CosTime = 0;
}

void CHammer::Update(void)
{
	if (m_bAnimStop)
	{
		if (m_WaitCount-- < 0)
		{
			m_WaitCount = m_OffsetWait;
			m_bAnimStop = false;
			m_SubStatus = SUBSTATUS_NOMAL;
		}
		return;
	}
	m_CosTime += m_CosSpd;
	float c = cos(m_CosTime);
	m_Rote = MOF_ToRadian(80) * c;
	m_HummerPos = GetRectCenter();
}

void CHammer::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	m_pTexture->RenderRotate(m_Pos.x - scroll.x, m_Pos.y - scroll.y, m_Rote, TEXALIGN_TOPCENTER);
	m_pHummerTexture->Render(m_HummerPos.x - scroll.x, m_HummerPos.y - scroll.y, TEXALIGN_CENTERCENTER);
#ifdef _DEBUG
	if (gbDebug)
	{
		for (int i = 0; i < m_SrcRectArray.GetArrayCount(); i++)
		{
			CRectangle rect = m_SrcRectArray[i];
			CGraphicsUtilities::RenderRect(rect + m_HummerPos - scroll, MOF_COLOR_BLUE);
		}
		CGraphicsUtilities::RenderRect(GetRect() - scroll, MOF_COLOR_BLUE);
	}
#endif // _DEBUG

}

Vector2 CHammer::GetRectCenter(void)
{
	float y = m_pTexture->GetHeight();
	float ang = m_Rote;
	float ca = cos(ang);
	float sa = sin(ang);
	float ax = -sa * y;
	float ay = ca * y;

	return Vector2(ax + m_Pos.x, ay + m_Pos.y);
}

CRectangle CHammer::GetRect(void)
{
	Vector2 Center(m_pHummerTexture->GetWidth() * 0.5f, m_pHummerTexture->GetHeight() * 0.5f);
	CRectangle rect(m_HummerPos.x, m_HummerPos.y, m_HummerPos.x + m_pHummerTexture->GetWidth(), m_HummerPos.y + m_pHummerTexture->GetHeight());
	rect -= Center;
	return rect;
}

bool CHammer::OverValue(CRectangle rect, Vector2 & out)
{
	bool re = false;
	CRectangle prec = rect;
	CRectangle rec = GetRect();
	if (!prec.CollisionRect(rec))
	{
		return false;
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
