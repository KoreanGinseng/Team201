#include "Object.h"



CObject::CObject()
{
}


CObject::~CObject()
{
}

void CObject::Initialize(float px, float py) {
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
	m_bAnim = false;
	//アニメーションを作成
	int c = g_pAnimManager->GetResource(FileName[ANIMATION_OBJ_1])->GetAnimCount();
	m_Motion.Create(g_pAnimManager->GetResource(FileName[ANIMATION_OBJ_1])->GetAnim(), c);
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

	if (m_bAnim)
	{
		m_Motion.AddTimer(CUtilities::GetFrameSecond());
		if (m_Motion.IsEndMotion())
		{
			m_bAnim = false;
			if (m_Motion.GetMotionNo() == MOTION_START)
			{
				m_Motion.ChangeMotion(MOTION_END);
			}
			else if (m_Motion.GetMotionNo() == MOTION_END)
			{
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
	CRectangle hr(sp.x, sp.y, sp.x + m_SrcRect.GetWidth(), sp.y + m_SrcRect.GetHeight());
	CGraphicsUtilities::RenderRect(hr, MOF_XRGB(255, 0, 0));
}

void CObject::Release(void) {
	m_Motion.Release();
}

void CObject::CollisionStage(const Vector2& o)
{
	m_Pos += o;
}

void CObject::Animation(void)
{
	m_bAnim = true;
}