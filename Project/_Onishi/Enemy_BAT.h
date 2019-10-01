#pragma once
#include	"EnemyMove.h"

class CENEMY_BAT :public CEnemyMove {
private:
	CSpriteMotionController m_Motion;
	CRectangle				m_SrcRect;
	CTexture	m_Texture;
public:
	CENEMY_BAT();
	~CENEMY_BAT();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};
