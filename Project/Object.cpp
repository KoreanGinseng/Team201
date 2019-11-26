#include "Object.h"
#include	"Rope.h"


CObject::CObject() :
CSubstance()
{
	m_Type = TYPE_OBJECT;
	m_bAppearance = false;
}

void CObject::Initialize(float px, float py, const int& cn) {
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
	//アニメーションを作成
	m_AnimCount = MOF_MAX(g_pAnimManager->GetResource(FileName[ANIMATION_OBJ_1 + cn])->GetAnimCount(), 0);
	m_Motion.Create(g_pAnimManager->GetResource(FileName[ANIMATION_OBJ_1 + cn])->GetAnim(), m_AnimCount);
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

	if (m_bSkill && m_AnimCount > 0)
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
	if (m_AnimCount > 0)
	{
		m_SrcRect = m_Motion.GetSrcRect();
	}
	else
	{
		m_SrcRect = CRectangle(0, 0, 64, 64);
	}

	m_pObjEmp->SetRect(GetRect());

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
	CGraphicsUtilities::RenderRect(hr, m_bTarget ? MOF_COLOR_GREEN : MOF_COLOR_RED);
	//CGraphicsUtilities::RenderString(0, 100, "%.1f, %.1f", GetRect().Left, GetRect().Top);
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
	//オブジェクトが壊れていなければ
	if (!m_bMotionEnd)
	{
		CRectangle brec = rect;
		brec.Top = brec.Bottom - 1;//
		brec.Expansion(-6, 0);//
		//下と当たり判定
		if (cr.CollisionRect(brec))
		{
			re = true;
			if (m_pObjEmp->GetType() == OBJECT_BRIDGE)
			{
				float serch = (cr.GetWidth() * 1 / 3);
				float sp = 0.0f;
				if (rect.Left <= cr.Left + serch)
				{
					sp = ((cr.Left + serch) - brec.Left) / serch;
				}
				else if (rect.Right >= cr.Right - serch)
				{
					sp = (brec.Right - (cr.Right - serch)) / serch;
				}
				if (sp < 0.1f)
				{
					sp = 0.1f;
				}
				else if (sp > 1.0f)
				{
					sp = 1.0f;
				}
				//橋の上の位置を求める
				float cTop = cr.Bottom - cr.GetHeight() * sp;
				if (brec.Bottom >= cTop)
				{
					o.y += cTop - brec.Bottom;
					rect.Top += cTop - brec.Bottom;
					rect.Bottom += cTop - brec.Bottom;
				}
			}
			else
			{
				//下の埋まりなのでチップの上端から矩形の下端の値を引いた値が埋まり値
				o.y += cr.Top - brec.Bottom;
				rect.Top += cr.Top - brec.Bottom;
				rect.Bottom += cr.Top - brec.Bottom;
			}
		}
		if (m_pObjEmp->GetType() != OBJECT_BRIDGE)
		{
			//当たり判定用の矩形
			//左右判定
			//左、右それぞれで範囲を限定した専用の矩形を作成する。
			CRectangle lrec = rect;
			lrec.Right = lrec.Left + 1;
			lrec.Expansion(0, -6);
			CRectangle rrec = rect;
			rrec.Left = rrec.Right - 1;
			rrec.Expansion(0, -6);
			//引数のレクトの左と当たり判定
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
	}
	return re;
}

void CObject::SetObject(const int& Type)
{

	

	switch (Type)
	{
	case 0:
		m_pObjEmp = new CRope();
		m_Pos.y += 32;
		break;
	case 1:
		m_pObjEmp = new CObjTree();
		break;
	case 2:
		m_pObjEmp = new CBridge();
		break;
	case OBJECT_MOVE:

		m_pObjEmp = new CMoveObject();
		
		break;
	case OBJECT_SAVE:

		m_pObjEmp = new CSaveObject();
	
		break;

	default:
		break;
	}

	if (m_pObjEmp->GetType() == OBJECT_SAVE) {

		m_bSave = false;

	}
	else {

		m_bSave = true;

	}
}