#pragma once
#include	"Mof.h"



class CStage {
private:
	CTexture	m_BackTexture;
	CTexture	m_ChipTexture;
	CTexture*	m_pEnemyTexture;
	CTexture*	m_pItemTexture;
	CTexture*	m_pObjectTexture;

	float		m_ChipSize;
	int			m_XCount;
	int			m_YCount;

	char*		m_pChipData;
	char*		m_pEnemyData;
	char*		m_pItemData;
	char*		m_pObjectData;

	int			m_EnemyTextureCount;
	int			m_ItemTextureCount;
	int			m_ObjectTextureCount;

	int			m_EnemyCount;
	int			m_ItemCount;
	int			m_ObjectCount;

public:
	CStage();
	~CStage() {}
	bool Load(char* pName);
	void Initialize();
	void Update();
	void Render(Vector2 scroll);
	void RenderDebug(Vector2 scroll);
	void Release();

	bool Collision(CRectangle r, Vector2& o);

};