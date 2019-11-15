#pragma once
#include "Mof.h"
#include "Empty.h"

class CMapObj
{
private:
	CTexturePtr m_pTexture;
	Vector2 m_Pos;
	bool m_bShow;
	int m_Type;

	void SetPos(Vector2 pos);

public:
	CMapObj();
	~CMapObj();

	bool Load();
	void Initialize(Vector2 pos,int type);
	void Update();
	void Render(Vector2 pos);
	void RenderDebug();
	void Release();

	bool GetShow();
	Vector2 GetPos(void) const { return m_Pos; }
    void SetTexture(CTexturePtr pt){ m_pTexture = pt; }
};

