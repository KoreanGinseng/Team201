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
	CRectangle hr(sp.x + GetRect().Left - m_Pos.x, sp.y + GetRect().Top - m_Pos.y,
		sp.x + GetRect().Right - m_Pos.x, sp.y + GetRect().Bottom - m_Pos.y);
	CGraphicsUtilities::RenderRect(hr, MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderString(0, 100, "%.1f, %.1f", GetRect().Left, GetRect().Top);
}

void CObject::Release(void) {
	delete m_pObjEmp;
	m_Motion.Release();
}

void CObject::CollisionStage(const Vector2& o)
{
	m_Pos += o;
}

bool CObject::Collision(CRectangle rect, Vector2 & o)
{
	bool re = false;
	//当たり判定
	CRectangle cr = GetRect();
	//当たり判定用の矩形
	//左右判定
	//左、右それぞれで範囲を限定した専用の矩形を作成する。
	CRectangle lrec = rect;
	lrec.Right = lrec.Left + 1;
	lrec.Expansion(0, -6);
	CRectangle rrec = rect;
	rrec.Left = rrec.Right - 1;
	rrec.Expansion(0, -6);
	//オブジェクトが壊れていなければ
	if (!m_bMotionEnd)
	{
		//左と当たり判定
		if (cr.CollisionRect(lrec))
		{
			re = true;
			//左の埋まりなのでチップ右端から矩形の左端の値を引いた値が埋まりの値
			o.x += cr.Right - lrec.Left;
			rect.Left += cr.Right - lrec.Left;
			rect.Right += cr.Right - lrec.Left;
		}
		//右と当たり判定
		if (cr.CollisionRect(rrec))
		{
			re = true;
			//右の埋まりなのでチップの左端から
			o.x += cr.Left - rrec.Right;
			rect.Left += cr.Left - rrec.Right;
			rect.Right += cr.Left - rrec.Right;
		}
		CRectangle brec = rect;
		brec.Top = brec.Bottom - 1;//
		brec.Expansion(-6, 0);//
		//下と当たり判定
		if (cr.CollisionRect(brec))
		{
			re = true;
			//下の埋まりなのでチップの上端から矩形の下端の値を引いた値が埋まり値
			o.y += cr.Top - brec.Bottom;
			rect.Top += cr.Top - brec.Bottom;
			rect.Bottom += cr.Top - brec.Bottom;
		}

		//上で範囲を限定した専用の矩形を作成する。
		CRectangle trec = rect;
		trec.Bottom = trec.Top - 1;//
		trec.Expansion(-6, 0);//
		//上と当たり判定
		if (cr.CollisionRect(trec))
		{
			re = true;
			//上の埋まりなのでチップした端から矩形の上端を
			o.y += cr.Bottom - trec.Top;
			rect.Top += cr.Bottom - trec.Top;
			rect.Bottom += cr.Bottom - trec.Top;
		}
	}
	return re;
}

void CObject::SetObject(const int& Type)
{
	switch (Type)
	{
	case 0:
		m_pObjEmp = new CRope();
		break;
	case 1:
		m_pObjEmp = new CObjTree();
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}