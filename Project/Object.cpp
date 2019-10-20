#include "Object.h"
#include	"Rope.h"


CObject::CObject() :
CSubstance()
{
}

void CObject::Initialize(float px, float py, const int& cn) {
	m_Pos.x = px;
	m_Pos.y = py - 32;
	m_bShow = true;
	//アニメーションを作成
	int c = g_pAnimManager->GetResource(FileName[ANIMATION_OBJ_1 + cn])->GetAnimCount();
	m_Motion.Create(g_pAnimManager->GetResource(FileName[ANIMATION_OBJ_1 + cn])->GetAnim(), c);
	if (m_bMotionEnd)
	{
		m_Motion.ChangeMotion(MOTION_END);
	}
}

void CObject::Update(void) {
	//非表示
	if (!m_bShow)
	{
		return;
	}

	m_pObjEmp->Update(m_bMotionEnd);

	if (m_bSkill)
	{
		m_Motion.AddTimer(CUtilities::GetFrameSecond());
		if (m_Motion.IsEndMotion())
		{
			m_bSkill = false;
			if (m_Motion.GetMotionNo() == MOTION_START)
			{
				m_bMotionEnd = true;
				m_Motion.ChangeMotion(MOTION_END);
			}
			else if (m_Motion.GetMotionNo() == MOTION_END)
			{
				m_bMotionEnd = false;
				m_Motion.ChangeMotion(MOTION_START);
			}
		}
	}

	m_SrcRect = m_Motion.GetSrcRect();
}

void CObject::Render(Vector2 sp) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(sp.x, sp.y, m_SrcRect);
}

void CObject::RenderDebug(Vector2 sp) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr(sp.x - m_Pos.x + GetRect().Left, sp.y - m_Pos.y + GetRect().Top, sp.x + GetRect().GetWidth(), sp.y + GetRect().GetHeight());
	CGraphicsUtilities::RenderRect(hr, MOF_XRGB(255, 0, 0));
}

void CObject::Release(void) {
	delete m_pObjEmp;
	m_Motion.Release();
}

void CObject::CollisionStage(const Vector2& o)
{
	//m_Pos += o;
}

void CObject::SetObject(const int& Type)
{
	switch (Type)
	{
	case 0:
		m_pObjEmp = new CRope();
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}