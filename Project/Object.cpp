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
	//常にアニメーションを動かす
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	//現在のアニメーションがおわったら切り替える
	if (m_Motion.GetMotionNo() == MOTION_CHANGE1 && m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(MOTION_END);
	}
	if (m_Motion.GetMotionNo() == MOTION_CHANGE2 && m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(MOTION_START);
	}
	//if (m_bMotionEnd)
	//{
	//}

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

void CObject::ChangeEnd()
{
	//もう一度通るためにフラグをoffにする
	bFlag = false;
}
void CObject::Change()
{
	//一回しか通らないようにするため
	if (bFlag)
	{
		return;
	}
	bFlag = true;
	//青色から赤色へ
	if (m_Motion.GetMotionNo() == MOTION_START)
	{
		m_Motion.ChangeMotion(MOTION_CHANGE1);
	}
	if (m_Motion.GetMotionNo() == MOTION_END)
	{
		m_Motion.ChangeMotion(MOTION_CHANGE2);
	}
	
//	else if (m_Motion.GetMotionNo() != MOTION_END)
//	{
		//m_Motion.AddTimer(STOPBITS_20);
//		m_Motion.AddTimer(CUtilities::GetFrameSecond());
//	}


	//赤色から青色へ
	/*if (m_Motion.GetMotionNo() == MOTION_END)
	{
		m_Motion.ChangeMotion(MOTION_CHANGE2);
	}

	else if (m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(MOTION_START);
	}

	else if (m_Motion.GetMotionNo() != MOTION_START)
	{
		m_Motion.AddTimer(CUtilities::GetFrameSecond());
	}*/

	MOF_PRINTLOG("%s\n", m_Motion.IsEndMotion() ? "ture" : "false");
	


	
}