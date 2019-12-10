#pragma once
#include	"GameDefine.h"
#include	"Mof.h"

class CEmpty
{
protected:
	
	int			m_RectCount;
	int			m_Aliment;
	float		m_Rote;
	float*		m_pRectCenter;
	CTexture*	m_pTexture;
	Vector2*	m_pCenter;
	Vector2*	m_pDownCenter;
	Vector2*	m_pPos;
	Vector2*	m_pMove;
	CRectangle	m_Rect;
	CRectangle* m_pRect;
	void RectLoad(const char* pName);
public:
	CEmpty();
	~CEmpty();
	virtual void Initialize(void) = 0;
	virtual bool Load(void) = 0;
	virtual void Update(const bool& me) = 0;
	virtual CRectangle GetRect(const Vector2& pos, const CRectangle& src) const = 0;
	virtual int GetType(void) const = 0;

	int		GetRenderType(void) { return m_Aliment; }
	float	GetRote(void) { return m_Rote; }
	void SetRect(const CRectangle& r) { m_Rect = r; }
	void SetCenter(Vector2* pCenter) { m_pCenter = pCenter; }
	void SetDownCenter(Vector2* pDownCenter) { m_pDownCenter = pDownCenter;}
	void SetPos(Vector2* pos) { m_pPos = pos; }
	void SetMove(Vector2* move) { m_pMove = move; }
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	void SetRectCenter(float* pRc) { m_pRectCenter = pRc; }
	
};

