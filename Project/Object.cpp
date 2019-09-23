#include "Object.h"



CObject::CObject()
{
}


CObject::~CObject()
{
}

void CObject::Initialize(float px, float py) {
	m_PosX = px;
	m_PosY = py;
	m_bShow = true;
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
		{
			"オブジェクトチェンジ１",
			0,0,
			64,64,
			FALSE,{{5,3,0},{5,2,0},{5,1,0},{5,0,0}},
		},
		{
			"オブジェクトチェンジ２",
			0,64,
			64,64,
			FALSE,{{5,3,0},{5,2,0},{5,1,0},{5,0,0}}
		},

	};
	m_Motion.Create(anim, MOTION_COUNT);
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

	if (m_bMotionEnd)
	{
		//m_Motion.AddTimer(CUtilities::GetFrameSecond());
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

void CObject::Change()
{
	bool end = false;
	if (m_Motion.GetMotionNo()==MOTION_START)
	{
		m_Motion.ChangeMotion(MOTION_CHANGE1);
	}
	
	if (end&&m_Motion.GetMotionNo() == MOTION_CHANGE1)
	{			
		m_Motion.ChangeMotion(MOTION_CHANGE2);
		
	}

	/*else if (m_Motion.GetMotionNo() == MOTION_CHANGE1)
	{
		if(m_Motion.IsEndMotion())
		m_Motion.ChangeMotion(MOTION_CHANGE2);
	}*/

	/*if (m_Motion.GetMotionNo() == MOTION_CHANGE1)
	{
		m_Motion.ChangeMotion(MOTION_END);
	}

	if (m_Motion.GetMotionNo() == MOTION_CHANGE2)
	{
		m_Motion.ChangeMotion(MOTION_START);
	}*/


	
}