#pragma once

#include	"Mof.h"
#include	"GameDefine.h"

//アイテム種類列挙
enum tag_ITEMTYPE {
	ITEM_RECOVER,					//回復
	ITEM_GOAL,						//ゴール

	ITEM_TYPECOUNT,
};

class CItem {
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	Vector2					m_Pos;
	Vector2					m_Move;
	bool					m_bShow;
	CRectangle				m_SrcRect;
public:
	CItem();
	~CItem();
	void Initialize(float px,float py,int type);
	void Update(void);
	void Render(Vector2 sp);
	void RenderDebug(Vector2 sp);
	void Release(void);
	
	//Set
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	void SetShow(const bool bs) { m_bShow = bs; }
	
	//Collision
	void CollisionStage(Vector2 o);
	
	//Get
	bool		GetShow(void)	const { return m_bShow; }
	Vector2		GetPos(void)	const { return m_Pos; }
	int			GetType(void)	const { return m_Type; }
	CRectangle	GetRect(void)	const { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight()); }
};