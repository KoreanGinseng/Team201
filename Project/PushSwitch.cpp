#include "PushSwitch.h"



CPushSwitch::CPushSwitch(void) :
CTargetObj()
{
	m_Type = OBJECT_PUSHSWITCH;
	m_SubType = SUB_ENE;
}


CPushSwitch::~CPushSwitch(void)
{
}

void CPushSwitch::Initialize(void)
{
	CTargetObj::Initialize();
	m_Way = m_SubStatus;
	m_pSuittiTexture = g_pTextureManager->GetTexture("suitti_j.png");
	float cx = (m_pTexture->GetWidth() - m_pSuittiTexture->GetWidth()) * 0.5f;
	m_SuittiPos = m_Pos;
	m_bOnPlayer = false;
	switch (m_Way)
	{
	case 0:
	{
		m_SrcRectArray.ReSize(0);
		float x = m_pTexture->GetHeight();
		m_SrcRectArray.Add(CRectangle(-1 * x,0,0,m_pTexture->GetWidth()));
		m_SuittiPos.y += cx;
		m_SuittiPos.x += m_pSuittiTexture->GetHeight() * 2.0f;
		m_Pos.x += m_pSuittiTexture->GetHeight();
		m_bSelectTarget = false;
		break;
	}
	case 1:
	{
		m_SrcRectArray.ReSize(0);
		m_SrcRectArray.Add(CRectangle(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight()));
		m_SuittiPos.x += cx;
		m_SuittiPos.y += m_pSuittiTexture->GetHeight();
		m_Pos.y += 64 - m_pTexture->GetHeight();
		break;
	}
	}
	m_OffsetPos = m_SuittiPos;
	m_OffsetWait = 180;
	m_WaitCount = m_OffsetWait;
	m_OnMoveY = 0;
}

void CPushSwitch::Update(void)
{
	if (m_Way == 0 && m_bOnPlayer)
	{
		m_SuittiPos.x = m_Pos.x;
	}

	if (m_bAnimStop)
	{
		if (m_WaitCount-- < 0)
		{
			m_WaitCount = m_OffsetWait;
			m_bAnimStop = false;
			m_SubStatus = SUBSTATUS_NOMAL;
		}
		if (m_bOnPlayer)
		{
			m_bOnPlayer = true;
		}
		return;
	}
	if (!m_bOnPlayer && m_Way == 1)
	{
		if (m_SuittiPos.y > m_OffsetPos.y)
		{
			m_SuittiPos.y -= 0.1f;
		}
	}
}

void CPushSwitch::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	switch (m_Way)
	{
	case 0:
	{
		m_pSuittiTexture->RenderRotate(m_SuittiPos.x - scroll.x, m_SuittiPos.y - scroll.y, MOF_ToRadian(90));
		m_pTexture->RenderRotate(m_Pos.x - scroll.x, m_Pos.y - scroll.y, MOF_ToRadian(90));

		break;
	}
	case 1:
	{
		m_pSuittiTexture->Render(m_SuittiPos.x - scroll.x, m_SuittiPos.y - scroll.y);
		m_pTexture->Render(m_Pos.x - scroll.x, m_Pos.y - scroll.y);

		break;
	}
	}
	if (m_bTarget)
	{
		CGraphicsUtilities::RenderRect(GetRect() - scroll, MOF_COLOR_GREEN);
	}
#ifdef _DEBUG
	if (gbDebug)
	{
		for (int i = 0; i < m_SrcRectArray.GetArrayCount(); i++)
		{
			CGraphicsUtilities::RenderRect(m_SrcRectArray[i] + m_Pos - scroll, MOF_COLOR_BLUE);
		}
		CGraphicsUtilities::RenderRect(GetRect() - scroll, MOF_COLOR_BLUE);
	}
#endif // _DEBUG

}

CRectangle CPushSwitch::GetRect(void)
{
	CRectangle rect;
	switch (m_Way)
	{
	case 0:
	{
		rect = CRectangle(m_SuittiPos.x, m_SuittiPos.y, m_SuittiPos.x + m_pSuittiTexture->GetWidth(), m_SuittiPos.y + m_pSuittiTexture->GetHeight());
		rect.Left -= m_pSuittiTexture->GetHeight();
		rect.Right = rect.Left + m_pSuittiTexture->GetHeight();
		rect.Bottom = rect.Top + m_pSuittiTexture->GetWidth();
		break;
	}
	case 1:
	{
		rect = CRectangle(m_SuittiPos.x, m_SuittiPos.y, m_SuittiPos.x + m_pSuittiTexture->GetWidth(), m_SuittiPos.y + m_pSuittiTexture->GetHeight());
		break;
	}
	}
	return rect;
}

bool CPushSwitch::OverValue(CRectangle rec, Vector2 & out)
{
	bool re = false;
	m_bOnPlayer = false;
	CRectangle rect = GetRectArray(0);
	CRectangle SuittiRect = GetRect();
	CRectangle prec = rec;
	if (!rect.CollisionRect(prec))
	{
		return re;
	}
	CRectangle br = prec;
	br.Expansion(-6, 0);
	br.Top = br.Bottom - 1;
	if (SuittiRect.CollisionRect(br))
	{
		re = true;
		float result = br.Bottom - SuittiRect.Top;
		out.y -= result;
		prec.Top -= result;
		prec.Bottom -= result;
		if (m_Way == 1)
		{
			m_SuittiPos.y += result;
			m_bOnPlayer = true;
		}
	}
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
	CRectangle tr = prec;
	tr.Expansion(-6, 0);
	tr.Bottom = tr.Top + 1;
	if (rect.CollisionRect(tr))
	{
		re = true;
		float result = tr.Top - rect.Bottom;
		out.y -= result;
		prec.Top -= result;
		prec.Bottom -= result;
	}
	return re;
	return false;
}

int CPushSwitch::GetWay(void) const
{
	return m_Way;
}

void CPushSwitch::SetOnPlayer(const bool & b)
{
	m_bOnPlayer = b;
	m_SuittiPos.x = m_Pos.x;
}
