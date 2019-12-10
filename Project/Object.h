#pragma once
#include	"Mof.h"
#include	"Substance.h"
#include	"GameDefine.h"
#include	"Empty.h"
#include	"Rope.h"
#include	"ObjTree.h"
#include	"Bridge.h"
#include	"MoveObject.h"
#include	"SaveObject.h"
#include	"PendulumLine.h"
#include	"PendulumBlock.h"

class CObject : public CSubstance
{
protected:
	CTexturePtr							m_pTexture;
	CSpriteMotionController				m_Motion;
	bool								m_bMotionEnd;
	bool								m_bShow;
	bool								m_bAppearance;
	CRectangle							m_SrcRect;
	CEmpty*								m_pObjEmp;

	int									m_ObjType;
	int									m_AnimCount;
	bool		m_bSave;
	CObject*							m_pPosObj;
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
	bool Collision(CRectangle rect, Vector2& o);

	//Set
	void SetObject(const int& Type);
	void SetTexture(CTexturePtr pt)    { m_pTexture = pt; }
	void SetMotionEnd(const bool& be)  { m_bMotionEnd = be; }
	void SetShow(const bool& bs)       { m_bShow = bs; }
	void SetAppearance(const bool& ba) { m_bAppearance = ba; }
	void SetSave(const bool& save)			   { m_bSave = save; }
	void SetPosObj(CObject* po) { m_pPosObj = po; }
	//Get
	bool		GetShow(void)	 const { return m_bShow; }
	bool		IsAppearance(void)	const { return m_bAppearance; }
	bool		IsSave(void) { return m_bSave; }
	
	CRectangle GetRect() const { return m_pObjEmp->GetRect(m_Pos, m_SrcRect); }
	int	 GetType(void) { return m_pObjEmp->GetType(); }

	Vector2 GetLineBottomPos() {
		if (m_ObjType != OBJECT_PENDULUMLINE)
		{
			return Vector2();
		}
		return dynamic_cast<CPendulumLine*>(m_pObjEmp)->GetRectCenter();
	}
};

