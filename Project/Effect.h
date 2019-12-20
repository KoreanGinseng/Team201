#pragma once

#include		"Mof.h"
#include		"GameDefine.h"

class CEffect {

private:
	CTexturePtr					m_pTexture;
	CSpriteMotionController		m_Motion;
	CRectangle					m_SrcRect;
	Vector2						m_Pos;
	bool						m_bShow;

public:

			CEffect();
			~CEffect();
	void	Initialize(int type);
	void	Update(void);
	void	Render(Vector2 screenPos);
	void	Release(void);
	void	Start(float px, float py);

	bool	GetShow(void) { return m_bShow; }
	void	SetTexture(CTexturePtr pt) { m_pTexture = pt; }

};