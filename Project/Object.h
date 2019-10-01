#pragma once

#include	"Mof.h"
#include	"Substance.h"

class CObject : public CSubstance
{
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	bool					m_bMotionEnd;
	

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

	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	void SetShow(bool bs) { m_bShow = bs; }
	void SetMotionEnd(bool bme) { m_bMotionEnd = bme; }

	bool GetShow(void) { return m_bShow; }
	Vector2 GetPos() { return Vector2(m_PosX, m_PosY); }
	/*CRectangle GetRect() { return CRectangle(m_PosX, m_PosY, m_PosX + m_SrcRect.GetWidth(), m_PosY + m_SrcRect.GetHeight()); }*/
};

