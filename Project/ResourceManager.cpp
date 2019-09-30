#include "ResourceManager.h"

CResourceManager* CResourceManager::m_pInstance = nullptr;

bool CResourceManager::Load(const char* pName, const TEXTUREDATA rt, const ANIMATIONDATA ra)
{
	//既に登録されていれば解放
	if (m_TextureResource.find(rt) != m_TextureResource.end())
	{
		m_TextureResource[rt].Release();
	}
	if (m_AnimationResource.find(ra) != m_AnimationResource.end())
	{
		m_AnimationResource[ra].Release();
	}

	//ファイルが開けなかった場合error
	FILE* fp = fopen(pName, "rb");
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
	m_TextureResource[rt].Load(fns);

	//アニメーション数取得
	int c;
	fread(&c, sizeof(int), 1, fp);
	SpriteAnimationCreate* anim = new SpriteAnimationCreate[c];
	
	//アニメーションの数だけ繰り返す
	for (int i = 0; i < c; ++i)
	{
		//データ読み取り用
		int read;

		//アニメーション名取得
		fread(&read, sizeof(int), 1, fp);
		char* animName = new char[read + 1];
		fread(animName, sizeof(char), read, fp);
		animName[read] = '\0';
		anim[i].Name = animName;
		//OffsetX
		fread(&read, sizeof(int), 1, fp);
		anim[i].OffsetX = (float)read;
		//OffsetY
		fread(&read, sizeof(int), 1, fp);
		anim[i].OffsetY = (float)read;
		//Width
		fread(&read, sizeof(int), 1, fp);
		anim[i].Width = (float)read;
		//Height
		fread(&read, sizeof(int), 1, fp);
		anim[i].Height = (float)read;

		//1byte(ループフラグ)読み取り用
		char tok;
		fread(&tok, sizeof(char), 1, fp);
		anim[i].bLoop = (bool)tok;
		//アニメーションフレーム数取得
		int animCount;
		fread(&animCount, sizeof(int), 1, fp);
		for (int j = 0; j < animCount; ++j)
		{
			fread(&read, sizeof(int), 1, fp);
			anim[i].Pattern[j].Wait = (float)read;
			fread(&anim[i].Pattern[j].No, sizeof(int), 1, fp);
			fread(&anim[i].Pattern[j].Step, sizeof(int), 1, fp);
		}
	}
	fclose(fp);

	m_AnimationResource[ra].Create(anim, c);

	return TRUE;
}

bool CResourceManager::AddTexture(const char* pName, const TEXTUREDATA rt)
{
	m_TextureResource[rt].Release();
	return m_TextureResource[rt].Load(pName);
}

void CResourceManager::Release()
{
	for (auto itr = m_TextureResource.begin(); itr != m_TextureResource.end(); ++itr)
	{
		itr->second.Release();
	}
	for (auto itr = m_AnimationResource.begin(); itr != m_AnimationResource.end(); ++itr)
	{
		itr->second.Release();
	}
	delete CResourceManager::m_pInstance;
	CResourceManager::m_pInstance = nullptr;
}