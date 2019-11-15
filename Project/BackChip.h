#pragma once
#include "Mof.h"
#include "Empty.h"

class BackChip
{
private:
	CTexturePtr m_pTexture;
	Vector2 m_Pos;
	bool m_bShow;
	int m_Type;



public:
	BackChip();
	~BackChip();

	bool Load();
	void Initialize(Vector2 pos, int type);
	void Update();
	void Render(Vector2 pos);
	void RenderDebug();
	void Release();

	bool GetShow();
	Vector2 GetPos(void) const { return m_Pos; }
	void SetPos(Vector2 p);
	void SetTexture(CTexturePtr pt) { m_pTexture = pt; }
	float GetWidth() { return m_pTexture->GetWidth(); }
};

