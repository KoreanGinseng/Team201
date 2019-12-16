#include "Character.h"



CCharacter::CCharacter() :
CObject(),
m_HP(1),
m_Move(),
m_Motion(),
m_SrcRectArray(),
m_bMove(false),
m_bDead(false),
m_bReverse(false),
m_DamageWait(0),
m_bCollision(false)
{
}


CCharacter::~CCharacter()
{
	Release();
}

void CCharacter::Render(const Vector2& screenPos)
{
	CRectangle r = GetSrcRect();
	if (!m_bReverse)
	{
		r.Left = GetSrcRect().Right;
		r.Right = GetSrcRect().Left;
	}
	m_pTexture->Render(screenPos.x, screenPos.y, r);

#ifdef _DEBUG
	CGraphicsUtilities::RenderRect(screenPos.x,screenPos.y,screenPos.x + GetSrcRect().GetWidth(), screenPos.y + GetSrcRect().GetHeight(), MOF_COLOR_RED);
	for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
	{
		CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
			screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
	}
#endif // _DEBUG
}

void CCharacter::Release(void)
{
	m_Motion.Release();
}

void CCharacter::LoadRect(const char * pName)
{
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルサイズをすべてバッファに読み込む
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;


	pstr = strtok(pBuffer, ",");
	int rectCount = atoi(pstr);
	CRectangle rec;
	for (int i = 0; i < rectCount; i++)
	{
		pstr = strtok(NULL, ",");
		rec.Left = atoi(pstr);
		pstr = strtok(NULL, ",");
		rec.Top = atoi(pstr);
		pstr = strtok(NULL, ",");
		rec.Right = atoi(pstr);
		pstr = strtok(NULL, ",");
		rec.Bottom = atoi(pstr);
		m_SrcRectArray.Add(rec);
	}
	free(pBuffer);
	fclose(fp);
}

CRectangle CCharacter::GetSrcRect(void) const
{
	return CRectangle();
}

CRectangle CCharacter::GetRect(void) const
{
	return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + GetSrcRect().GetWidth(), m_Pos.y + GetSrcRect().GetHeight());
}

RectArray CCharacter::GetSrcRectArray(void) const
{
	return m_SrcRectArray;
}

RectArray * CCharacter::GetSrcRectArrayPointer(void)
{
	return &m_SrcRectArray;
}

RectArray CCharacter::GetRectArray(void) const
{
	RectArray result;
	for (int i = 0; i < m_SrcRectArray.GetArrayCount(); i++)
	{
		CRectangle rec(m_Pos.x + m_SrcRectArray[i].Left, m_Pos.y + m_SrcRectArray[i].Top, GetRect().Left + m_SrcRectArray[i].GetWidth(), GetRect().Top + m_SrcRectArray[i].GetHeight());
		result.Add(rec);
	}
	return result;
}

CRectangle CCharacter::GetRectArray(const int & n) const
{
	return CRectangle(
		m_Pos.x + m_SrcRectArray[n].Left, m_Pos.y + m_SrcRectArray[n].Top,
		m_Pos.x + m_SrcRectArray[n].Right, m_Pos.y + m_SrcRectArray[n].Bottom
	);
}

int CCharacter::GetDamageWait(void) const
{
	return m_DamageWait;
}

bool CCharacter::OverValue(CRectangle rec, Vector2 & out)
{
	return false;
}

void CCharacter::CollisionStage(const Vector2 & over)
{
	m_Pos += over;
}

void CCharacter::SetCollisionFlag(const bool & b)
{
	m_bCollision = b;
}

bool CCharacter::IsCollisionFlag(void) const
{
	return m_bCollision;
}

bool CCharacter::IsStageOver(void) const
{
	return (
		GetRect().Right < CCordinate::GetStageRect().Left ||m_Pos.x > CCordinate::GetStageRect().Right ||
		GetRect().Bottom < CCordinate::GetStageRect().Top || m_Pos.y > CCordinate::GetStageRect().Bottom
		);
}
