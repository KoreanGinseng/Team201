#include "Character.h"



CCharacter::CCharacter()
	: CObject()
{
	m_bDead = false;
	m_bCollision = true;
}


CCharacter::~CCharacter()
{
}

void CCharacter::Initialize(void)
{
	m_MvCntrl.Initialize();
	m_Anim.Initialize();
	m_bShow = true;
	m_bDead = false;
}

void CCharacter::Update(void)
{
	m_MvCntrl.Update();
	m_Anim.Update();
	m_Pos += m_MvCntrl.GetMove();
}

void CCharacter::Render(const Vector2& screenPos)
{
	m_pTexture->Render(screenPos.x, screenPos.y, GetSrcRect());

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
	m_MvCntrl.Remove();
	m_Anim.Release();
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

bool CCharacter::OverValue(CRectangle rec, Vector2 & out)
{
	return false;
}

void CCharacter::CollisionStage(const Vector2 & over)
{
	m_Pos += over;
}
