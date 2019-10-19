#pragma once
#include	"Mof.h"
#include	"Substance.h"
#include	"GameDefine.h"

class CObject : public CSubstance
{
private:
	CTexturePtr							m_pTexture;
	CSpriteMotionController				m_Motion;
	bool								m_bMotionEnd;
	bool								m_bShow;
	CRectangle							m_SrcRect;

	enum tag_MOTION {
		MOTION_START,
		MOTION_END,

		MOTION_COUNT
	};
public:
	CObject();
	~CObject();
	void Initialize(float px, float py, const int& cn);
	void Update(void);
	void Render(Vector2 sp);
	void RenderDebug(Vector2 sp);
	void Release(void);

	//Collision
	void CollisionStage(const Vector2& o);

	//Set
	void SetTexture(CTexturePtr pt)	  { m_pTexture = pt; }
	void SetMotionEnd(const bool be)  { m_bMotionEnd = be; }
	void SetShow(const bool bs)	      { m_bShow = bs; }

	//Get
	bool		GetShow(void)	 const { return m_bShow; }
};

