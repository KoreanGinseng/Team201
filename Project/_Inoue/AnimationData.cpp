#include "AnimationData.h"



CAnimationData::CAnimationData() :
m_pTexture(nullptr),
m_pMotion(nullptr)
{
}


CAnimationData::~CAnimationData()
{
}

bool CAnimationData::Load(const char* pName) 
{
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

	//テクスチャの読み込み
	m_pTexture = g_pTextureManager->GetResource(fns);
	if (m_pTexture == nullptr)
	{
		return FALSE;
	}

	delete fns;
	fns = nullptr;

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
		delete[] animName;
		animName = nullptr;
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

	//アニメーションデータ作成
	if (m_pMotion == nullptr)
	{
		m_pMotion = std::make_shared<CSpriteMotionController>();
	}
	if (!m_pMotion->Create(anim, c))
	{
		delete[] anim;
		anim = nullptr;
		return FALSE;
	}

	delete[] anim;
	anim = nullptr;
	return TRUE;
}

void CAnimationData::Release(void) 
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
	if (m_pMotion != nullptr)
	{
		m_pMotion->Release();
		m_pMotion = nullptr;
	}
}