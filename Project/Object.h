#pragma once
#include	"Mof.h"
#include	"Substance.h"
#include	"GameDefine.h"
#include	"Empty.h"
#include	"Rope.h"

class CObject : public CSubstance
{
protected:
	CTexturePtr							m_pTexture;
	CSpriteMotionController				m_Motion;
	bool								m_bMotionEnd;
	bool								m_bShow;
	CRectangle							m_SrcRect;
	CEmpty*								m_pObjEmp;

	enum tag_MOTION {
		MOTION_START,
		MOTION_END,

		MOTION_COUNT
	};
public:
	CObject();
	~CObject() { Release(); }
	void Initialize(float px, float py, const int& cn);
	void Update(void);
	void Render(Vector2 sp);
	void RenderDebug(Vector2 sp);
	void Release(void);

	//Collision
	void CollisionStage(const Vector2& o);

	//Set
	void SetTexture(CTexturePtr pt)    { m_pTexture = pt; }
	void SetMotionEnd(const bool& be)  { m_bMotionEnd = be; }
	void SetShow(const bool& bs)       { m_bShow = bs; }

	//Get
	bool		GetShow(void)	 const { return m_bShow; }
	//virtual CRectangle GetRect() const { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight()); }
	CRectangle GetRect() const { return m_pObjEmp->GetRect(m_Pos, m_SrcRect); }
	void SetObject(const int& Type);
};

