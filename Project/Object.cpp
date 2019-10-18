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
bool CObject::Collision(CRectangle r, float& ox, float& oy)
{
	int h = r.GetHeight();
	int w = r.GetWidth();
	
	//壊れている
	if (m_Motion.GetMotionNo() == MOTION_START)
	{
		ObjNo = 0;
	}
	//壊れていない
	else 
	{
		ObjNo = 1;
	}
	bool re = false;
	
	float x = m_SrcRect.GetWidth();
	float y = m_SrcRect.GetHeight();
	//当たり判定
			CRectangle cr(m_PosX, m_PosY, m_PosX+x ,m_PosY +y);
			//当たり判定用の矩形
			//左右判定
			//左、右それぞれで範囲を限定した専用の矩形を作成する。
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;
			lrec.Expansion(0, -3);
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;
			rrec.Expansion(0, -3);
			//オブジェクトが壊れていなければ
			if (ObjNo == 0)
			{
			    //左と当たり判定
				if (cr.CollisionRect(lrec))
				{
					re = true;
					//左の埋まりなのでチップ右端から矩形の左端の値を引いた値が埋まりの値
					ox += cr.Right - lrec.Left;
					r.Left += cr.Right - lrec.Left;
					r.Right += cr.Right - lrec.Left;
				}
				//右と当たり判定
				if (cr.CollisionRect(rrec))
				{
					re = true;
					//右の埋まりなのでチップの左端から
					ox += cr.Left - rrec.Right;
					r.Left += cr.Left - rrec.Right;
					r.Right += cr.Left - rrec.Right;
				}
				CRectangle brec = r;
				brec.Top = brec.Bottom - 1;//
				brec.Expansion(-2, 0);//
				//下と当たり判定
				if (cr.CollisionRect(brec))
				{
					re = true;
					//下の埋まりなのでチップの上端から矩形の下端の値を引いた値が埋まり値
					oy += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}

				//上で範囲を限定した専用の矩形を作成する。
				CRectangle trec = r;
				trec.Bottom = trec.Top - 1;//
				trec.Expansion(-2, 0);//
				//上と当たり判定
				if (cr.CollisionRect(trec))
				{
					re = true;
					//上の埋まりなのでチップした端から矩形の上端を
					oy += cr.Bottom - trec.Top;
					r.Top += cr.Bottom - trec.Top;
					r.Bottom += cr.Bottom - trec.Top;
				}
			}
	return re;
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
	MOF_PRINTLOG("%s\n", m_Motion.IsEndMotion() ? "ture" : "false");	
}