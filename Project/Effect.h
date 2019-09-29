#pragma once

#include		"Mof.h"

/*�G�t�F�N�g�̎��*/
enum tag_EFFECTTYPE {

	EFC_TEST,EFC_TYPECOUNT

};

class CEffect {

private:
	CTexture*					m_pTexture;
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
	void	SetTexture(CTexture* pt) { m_pTexture = pt; }

};