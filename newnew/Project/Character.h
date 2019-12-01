#pragma once
#include "Object.h"
#include "MoveController.h"
#include "Anim.h"

class CCharacter :
	public CObject
{
protected:
	CMoveController		m_MvCntrl;
	CAnim				m_Anim;
	RectArray			m_SrcRectArray;
	bool				m_bDead;
	bool				m_bReverse;
	int					m_DamageWait;
public:
	CCharacter(void);
	~CCharacter(void) override;
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void Release(void) override;

	void CreateMove(const int& no) { m_MvCntrl.Create(no); m_MvCntrl.SetPos(&m_Pos); }
	void CreateAnim(const char* pName) { m_Anim.Create(pName); }

	void LoadRect(const char* pName);

	bool IsDead(void) const { return m_bDead; }

	Vector2 GetSpd(void) const { return m_MvCntrl.GetSpd(); }
	CRectangle GetSrcRect(void) const { return m_Anim.GetRect(); }
	virtual CRectangle GetRect(void) const { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + GetSrcRect().GetWidth(), m_Pos.y + GetSrcRect().GetHeight()); }
	RectArray GetSrcRectArray(void) const { return m_SrcRectArray; }
	RectArray* GetSrcRectArrayPointer(void) { return &m_SrcRectArray; }
	RectArray GetRectArray(void) const;
	CRectangle GetRectArray(const int& n) const {
		return CRectangle(
			m_Pos.x + m_SrcRectArray[n].Left, m_Pos.y + m_SrcRectArray[n].Top,
			m_Pos.x + m_SrcRectArray[n].Right, m_Pos.y + m_SrcRectArray[n].Bottom);
	}
	int GetDamageWait(void) const { return m_DamageWait; }
	virtual bool OverValue(CRectangle rec, Vector2& out);
	virtual void CollisionStage(const Vector2& over);
};

