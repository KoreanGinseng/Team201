#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

class CResourceManager
{
private:
	std::map<TEXTUREDATA, CTexture> m_TextureResource;
	std::map<ANIMATIONDATA, CSpriteMotionController> m_AnimationResource;
	CResourceManager(void) = default;
	~CResourceManager(void) = default;
	static CResourceManager* m_pInstance;

public:
	bool Load(const char* pName, const TEXTUREDATA rt, const ANIMATIONDATA ra);
	void AddTexture(const char* pName, const TEXTUREDATA rt);
	void Release(void);

	//Get
	CTexture* GetTexture(const TEXTUREDATA rt) { return &m_TextureResource[rt];	}
	CSpriteMotionController* GetAnimation(const ANIMATIONDATA ra) {	return &m_AnimationResource[ra]; }
	static CResourceManager* GetInstance(void) {
		if (m_pInstance == nullptr)	m_pInstance = new CResourceManager();
		return m_pInstance;
	}
};

#define		g_pResouseManager		CResourceManager::GetInstance()