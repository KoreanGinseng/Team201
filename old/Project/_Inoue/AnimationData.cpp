#include "AnimationData.h"



CAnimationData::CAnimationData() :
m_pTexture(nullptr),
m_pAnim(nullptr)
{
}


CAnimationData::~CAnimationData()
{
}

bool CAnimationData::Load(const char* pName) 
{
	//�t�@�C�����J���Ȃ������ꍇerror
	FILE* fp = fopen(pName, "rb");
	if (fp == nullptr)
	{
		return FALSE;
	}

	//�摜�t�@�C���̕�����擾
	int fnc;
	fread(&fnc, sizeof(int), 1, fp);
	char* fns = new char[fnc + 1];
	fread(fns, sizeof(char), fnc, fp);
	fns[fnc] = '\0';

	//�e�N�X�`���̓ǂݍ���
	m_pTexture = g_pTextureManager->GetResource(fns);
	if (m_pTexture == nullptr)
	{
		return FALSE;
	}

	delete fns;
	fns = nullptr;

	//�A�j���[�V�������擾
	fread(&m_AnimCount, sizeof(int), 1, fp);
	m_pAnim = new SpriteAnimationCreate[m_AnimCount];

	//�A�j���[�V�����̐������J��Ԃ�
	for (int i = 0; i < m_AnimCount; ++i)
	{
		//�f�[�^�ǂݎ��p
		int read;

		//�A�j���[�V�������擾
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

		//1byte(���[�v�t���O)�ǂݎ��p
		char tok;
		fread(&tok, sizeof(char), 1, fp);
		m_pAnim[i].bLoop = (bool)tok;
		//�A�j���[�V�����t���[�����擾
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

void CAnimationData::Release(void) 
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
	delete[] m_pAnim;
	m_pAnim = nullptr;
}