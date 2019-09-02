#pragma once
#include	"Mof.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"Object.h"


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
	char*		m_pObjEndData;

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
	void Initialize(CEnemy* pEne, CItem* pItem, CObject* pObj);
	void Update();
	void Render(Vector2 scroll);
	void RenderDebug(Vector2 scroll);
	void Release();

	bool Collision(CRectangle r, Vector2& o);

	int	 GetEnemyCount()  const { return m_EnemyCount; }
	int	 GetItemCount()   const { return m_ItemCount; }
	int	 GetObjectCount() const { return m_ObjectCount; }

};