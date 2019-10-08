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
	SpriteAnimationCreate anim[] = {
		{
			"オブジェクト",
			0,0,
			64,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"オブジェクトエンド",
			0,64,
			64,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
	};
	m_pMotion->Create(anim, MOTION_COUNT);
	if (m_bMotionEnd)
	{
		m_pMotion->ChangeMotion(MOTION_END);
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
		m_pMotion->AddTimer(CUtilities::GetFrameSecond());
		if (m_pMotion->IsEndMotion())
		{
			m_bAnim = false;
			if (m_pMotion->GetMotionNo() == MOTION_START)
			{
				m_pMotion->ChangeMotion(MOTION_END);
			}
			else if (m_pMotion->GetMotionNo() == MOTION_END)
			{
				m_pMotion->ChangeMotion(MOTION_START);
			}
		}
	}

	m_SrcRect = m_pMotion->GetSrcRect();
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
	m_pMotion->Release();
}

void CObject::CollisionStage(const Vector2& o)
{
	m_Pos += o;
}

void CObject::Animation(void)
{
	m_bAnim = true;
}