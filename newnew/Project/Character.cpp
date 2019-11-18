#include "Character.h"



CCharacter::CCharacter()
{
}


CCharacter::~CCharacter()
{
}

void CCharacter::Initialize(void)
{
	m_MvCntrl.Initialize();
	m_Anim.Initialize();
}

void CCharacter::Update(void)
{
	m_MvCntrl.Update();
	m_Anim.Update();
}

void CCharacter::Render(const Vector2& screenPos)
{
	m_pTexture->Render(screenPos.x, screenPos.y, GetSrcRect());
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
		CRectangle rec(m_Pos.x, m_Pos.y, m_Pos.x + m_SrcRectArray[i].GetWidth(), m_Pos.y + m_SrcRectArray[i].GetHeight());
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
