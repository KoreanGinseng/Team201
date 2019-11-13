#pragma once
#include	"GameDefine.h"

class CObject
{
protected:
	Vector2			m_Pos;
	CTexturePtr		m_pTexture;
	bool			m_bShow;
public:
	CObject();
	virtual ~CObject();
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(Vector2 screenPos) = 0;
	virtual void Release(void) = 0;
	void SetPos(const Vector2& pos) { m_Pos = pos; }
	void SetTexture(const CTexturePtr& pt) { m_pTexture = pt; }
	void SetShow(const bool& b) { m_bShow = b; }

	bool IsShow(void) const { return m_bShow; }
};

