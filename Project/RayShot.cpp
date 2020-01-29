#include "RayShot.h"



CRayShot::CRayShot(void) :
	CShot()
{
	m_ShotType = SHOT_RAY;
}


CRayShot::~CRayShot(void)
{
	m_pTexture = nullptr;
}

void CRayShot::Fire(const Vector2 & startPos)
{
	m_bShot = true;
	m_bShot2 = false;
	m_bShot3 = false;
	m_Pos = startPos;
	m_RefrectPos[0] = m_Pos;
	m_RefrectPos[1] = Vector2(0, 0);
	for (int i = 0; i < 2; i++) {
		m_Scale[i] = 0;
	}
	m_ScaleY = 1.0f;
	Vector2 d = Vector2(
		CCordinate::GetPlayerPos().x + 192 * 0.5f,
		CCordinate::GetPlayerPos().y + 192 * 0.5f)
		- m_Pos;
	float fd = sqrtf(d.x * d.x + d.y * d.y);
	Vector2 dd = d / fd;
	m_Spd = Vector2(12, 12);
	m_Move = dd * m_Spd;
	m_RefrectRad[0] = atan2f(d.y, d.x);
	m_Timer = 180;
	m_bReverse = false;
	m_ColCirArray.Release();
	m_ColCirArray.ReSize(0);
	m_TempCount = 0;
}

void CRayShot::Initialize(void)
{
	m_bShot = false;
	m_pTexture = g_pTextureManager->GetTexture("RayShot.png");
	for (auto& itr : m_RefrectPos)
	{
		itr = Vector2(0, 0);
	}
}

void CRayShot::Update(void)
{

	int crr = m_pTexture->GetHeight();
	float texW = m_pTexture->GetWidth();
	if (m_bShot2 && !m_bShot3)
	{
		m_Scale[1] += 0.01f;
		int cc = m_ColCirArray.GetArrayCount() - m_TempCount;
		float length = static_cast<float>(texW * m_Scale[1]);
		if (length - cc * crr > crr)
		{
			float x = m_RefrectPos[1].x + (length - crr * 0.5f);
			float y = m_RefrectPos[1].y;
			m_ColCirArray.Add(CCircle(x, y, crr * 0.5f));
		}
	}
	else if (!m_bShot3)
	{
		float length = static_cast<float>(texW * m_Scale[0]);
		m_Scale[0] += 0.01f;
		int cc = m_ColCirArray.GetArrayCount();
		//if ((cc == 0 || cc == 1) && length > crr)
		//{
		//	float x = m_RefrectPos[0].x + (length - crr * 0.5f) * cosf(m_RefrectRad[0]);
		//	float y = m_RefrectPos[0].y + (length - crr * 0.5f) * sinf(m_RefrectRad[0]);
		//	m_ColCirArray.Add(CCircle(x, y, crr * 0.5f));
		//}
		//else 
		if (/*cc != 0 &&*/ length - cc * crr > crr)
		{
			float x = m_RefrectPos[0].x + (length - crr * 0.5f) * cosf(m_RefrectRad[0]);
			float y = m_RefrectPos[0].y + (length - crr * 0.5f) * sinf(m_RefrectRad[0]);
			m_ColCirArray.Add(CCircle(x, y, crr * 0.5f));
		}
	}
	for (int i = 0; i < 2; i++) {
		if (/*m_RefrectPos[i].x < CCamera2D::GetSScroll().x ||*/ m_Timer-- < 0)
		{
			m_ScaleY -= 0.01f;
			if (m_ScaleY < 0) {
				m_bShot = false;
			}
		}
	}
}

void CRayShot::Render(const Vector2 & screenPos)
{
	if (!m_bShot)
	{
		return;
	}
	Vector2 scroll = CCamera2D::GetSScroll();
	//CRectangle rect(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight());
	//if (m_bReverse)
	//{
	//	float tmp = rect.Left;
	//	rect.Left = rect.Right;
	//	rect.Right = tmp;
	//}
	if (m_bShot2) {
		g_pTextureManager->GetTexture("RayShot.png")->RenderScaleRotate(m_RefrectPos[1].x - scroll.x, m_RefrectPos[1].y - scroll.y, m_Scale[1], m_ScaleY, 0.0f, TEXALIGN_CENTERLEFT);
	}
	m_pTexture->RenderScaleRotate(m_RefrectPos[0].x - scroll.x, m_RefrectPos[0].y - scroll.y, m_Scale[0], m_ScaleY, m_RefrectRad[0], TEXALIGN_CENTERLEFT);
	MOF_PRINTLOG("POSX:%.1f POSY:%.1f SCALE:%.3f RAD:%.1f\n", m_RefrectPos[0].x - scroll.x, m_RefrectPos[0].y - scroll.y, m_Scale[0], MOF_ToDegree(m_RefrectRad[0]));
#ifdef _DEBUG
	if (gbDebug)
	{
		for (int i = 0; i < m_ColCirArray.GetArrayCount(); i++)
		{
			CCircle cir = m_ColCirArray[i];
			CGraphicsUtilities::RenderFillCircle(cir.x - scroll.x, cir.y - scroll.y, cir.r, MOF_COLOR_BLUE);

			CGraphicsUtilities::RenderString(0, 0 + 24 * i, "%.1f,%.1f,%.1f", cir.x - scroll.x, cir.y - scroll.y, cir.r);
		}
	}
#endif
}

CDynamicArray<CCircle>* CRayShot::GetShotCircle(void)
{
	return &m_ColCirArray;
}

bool CRayShot::OverValue(CRectangle rect, Vector2 & out)
{
	for (int i = 0; i < m_ColCirArray.GetArrayCount(); i++)
	{
		CCircle c = m_ColCirArray[i];
		if (CollisionRectCircle(rect, c))
		{
			return true;
		}
	}
	return false;
}

void CRayShot::Refrect(const Vector2& pos)
{
	if (m_bShot2)
	{
		m_bShot3 = true;
		return;
	}
	m_RefrectPos[1] = pos;
	m_RefrectPos[1].x += m_pTexture->GetHeight() * 0.3f;
	m_TempCount = m_ColCirArray.GetArrayCount();
	m_bShot2 = true;
	//m_Move.x *= -1;
	//m_RefrectRad[1] = MOF_ToRadian(180) - m_RefrectRad[0];
}

void CRayShot::FireStop(void)
{
	m_bShot = false;
	m_bReverse = true;
}

int CRayShot::GetTempCount(void) const
{
	return m_TempCount;
}

bool CRayShot::IsRef(void) const
{
	return m_bShot2;
}
