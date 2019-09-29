#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

class CResourceManager
{
private:
	std::map<TEXTUREDATA, CTexture> m_TextureResource;
	std::map<ANIMATIONDATA, SpriteAnimationCreate*> m_AnimationResource;
	CResourceManager(void) = default;
	~CResourceManager(void) = default;
	static CResourceManager* m_pInstance;

public:
	static CResourceManager* GetInstance(void) {
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CResourceManager();
		}
		return m_pInstance;
	}
	
	CTexture* GetTexture(const TEXTUREDATA rt) {
		return &m_TextureResource[rt];
	}

	SpriteAnimationCreate* GetAnimation(const ANIMATIONDATA ra) {
		return m_AnimationResource[ra];
	}
	bool Load(void);
	void Release(void);
	void AddTexture(const TEXTUREDATA rt, const char* pName);
};

#define		g_pResouseManager		CResourceManager::GetInstance()