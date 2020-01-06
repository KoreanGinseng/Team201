#include "AnimationData.h"


CAnimationData::CAnimationData(void) :
m_TextureName(""),
m_pAnim(nullptr)
{
}

CAnimationData::~CAnimationData(void)
{
}

bool CAnimationData::Load(const std::string& str)
{
	//ファイルが開けなかった場合error
	FILE* fp = fopen(str.c_str(), "rb");
	if (fp == nullptr)
	{
		return FALSE;
	}

	//画像ファイルの文字列取得
	int fnc;
	fread(&fnc, sizeof(int), 1, fp);
	char* fns = new char[fnc + 1];
	fread(fns, sizeof(char), fnc, fp);
	fns[fnc] = '\0';

	//テクスチャの読み込み
	m_TextureName = fns;

	delete[] fns;
	fns = nullptr;

	//アニメーション数取得
	fread(&m_AnimCount, sizeof(int), 1, fp);
	m_pAnim = new SpriteAnimationCreate[m_AnimCount];

	//アニメーションの数だけ繰り返す
	for (int i = 0; i < m_AnimCount; ++i)
	{
		//データ読み取り用
		int read;

		//アニメーション名取得
		fread(&read, sizeof(int), 1, fp);
		char* animName = new char[read + 1];
		fread(animName, sizeof(char), read, fp);
		animName[read] = '\0';
		m_pAnim[i].Name = animName;

		delete[] animName;
		animName = nullptr;

		//OffsetX
		fread(&read, sizeof(int), 1, fp);
		m_pAnim[i].OffsetX = (float)read;
		//OffsetY
		fread(&read, sizeof(int), 1, fp);
		m_pAnim[i].OffsetY = (float)read;
		//Width
		fread(&read, sizeof(int), 1, fp);
		m_pAnim[i].Width = (float)read;
		//Height
		fread(&read, sizeof(int), 1, fp);
		m_pAnim[i].Height = (float)read;

		//1byte(ループフラグ)読み取り用
		char tok;
		fread(&tok, sizeof(char), 1, fp);
		m_pAnim[i].bLoop = (bool)tok;
		//アニメーションフレーム数取得
		int animCount;
		fread(&animCount, sizeof(int), 1, fp);
		for (int j = 0; j < animCount; ++j)
		{
			fread(&read, sizeof(int), 1, fp);
			m_pAnim[i].Pattern[j].Wait = (float)read;
			fread(&m_pAnim[i].Pattern[j].No, sizeof(int), 1, fp);
			fread(&m_pAnim[i].Pattern[j].Step, sizeof(int), 1, fp);
		}
	}
	fclose(fp);

	return TRUE;
}

SpriteAnimationCreate * CAnimationData::GetAnim(void)
{
	return m_pAnim;
}

int CAnimationData::GetAnimCount(void) const
{
	return m_AnimCount;
}

std::string CAnimationData::GetTextureName(void) const
{
	return m_TextureName;
}

void CAnimationData::Release(void) 
{
	delete[] m_pAnim;
	m_pAnim = nullptr;
}