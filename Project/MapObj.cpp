#include "MapObj.h"



CMapObj::CMapObj()
{
}


CMapObj::~CMapObj()
{
}

bool CMapObj::Load()
{
	return true;
}
void CMapObj::Initialize(Vector2 pos,int type)
{
	m_Type = type;
	SetPos(pos);
	m_bShow = true;
}
void CMapObj::Update()
{

}
void CMapObj::Render(Vector2 pos)
{
	m_pTexture->Render(pos.x,pos.y);
}
void CMapObj::RenderDebug()
{

}
void CMapObj::Release()
{

}

void CMapObj::SetPos(Vector2 pos)
{
	m_Pos = pos;
}
bool CMapObj::GetShow()
{
	return false;
}
