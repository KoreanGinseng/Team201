#pragma once
#include	"Mof.h"

class CObject
{
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	bool					m_bMotionEnd;
	Vector2					m_Pos;
	bool					m_bShow;
	CRectangle				m_SrcRect;

	enum tag_MOTION {
		MOTION_START,
		MOTION_END,

		MOTION_COUNT
	};
public:
	CObject();
	~CObject();
	void Initialize(float px, float py);
	void Update(void);
	void Render(Vector2 sp);
	void RenderDebug(Vector2 sp);
	void Release(void);

	//Set
	void SetTexture(CTexture* pt)	  { m_pTexture = pt; }
	void SetMotionEnd(const bool be)  { m_bMotionEnd = be; }
	void SetShow(const bool bs)	      { m_bShow = bs; }

	//Get
	bool		GetShow(void)	 const { return m_bShow; }
	Vector2		GetPos(void)	 const { return m_Pos; }
	CRectangle	GetRect(void)	 const { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight()); }
};

