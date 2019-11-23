#include "MapObj.h"



CMapObj::CMapObj()
{
}


CMapObj::~CMapObj()
{
	Release();
}

void CMapObj::Initialize(void)
{
	m_bShow = true;
}

void CMapObj::Update(void)
{
}

void CMapObj::Render(const Vector2 & screenPos)
{
	m_pTexture->Render(screenPos.x, screenPos.y);
}

void CMapObj::Release(void)
{
}
