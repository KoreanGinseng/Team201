#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

class CResourceManager
{
private:
	static std::map<TEXTUREDATA, CTexture> m_TextureResource;
	static std::map<ANIMATIONDATA, SpriteAnimationCreate*> m_AnimationResource;
	CResourceManager();
	static CResourceManager* m_Instance;

	const char* m_TextureName[] = {
	"TEXTURE_PLAYER",
	"TEXTURE_ENEMY_1",
	"TEXTURE_ENEMY_2",
	"TEXTURE_ENEMY_3",
	"TEXTURE_OBJ_1",
	"TEXTURE_OBJ_2",
	"TEXTURE_OBJ_3",
	"TEXTURE_OBJ_4",
	"TEXTURE_ENEMY_ATTACK",
	"TEXTURE_MAP_BACK",
	"TEXTURE_MAP_BACKCHIP_1",
	"TEXTURE_MAP_BACKCHIP_2",
	"TEXTURE_MAP_CHIP",
	};



public:
	~CResourceManager();
	static CResourceManager* GetInstance() {
		if (m_Instance == nullptr)
		{
			m_Instance = new CResourceManager();
		}
		return m_Instance;
	}
	
	CTexture* GetTexture(const TEXTUREDATA rt) {
		return &m_TextureResource[rt];
	}

	SpriteAnimationCreate* GetAnimation(const ANIMATIONDATA ra) {
		return m_AnimationResource[ra];
	}
	bool Load();
};

#define		g_pResouseManager		CResourceManager::GetInstance()