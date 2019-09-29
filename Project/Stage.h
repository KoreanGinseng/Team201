/*****************************************************************
 *	@file			Stage.h
 *	@brief			ステージクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

//INCLUDE
#include	"Mof.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"Object.h"

class CStage
{
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
	CStage(void);
	~CStage(void) {}
	bool Load(const char* pName);
	void Initialize(CEnemy* pEne, CItem* pItem, CObject* pObj);
	void Update(void);
	void Render(Vector2 scroll);
	void RenderDebug(Vector2 scroll);
	void Release(void);

	//Collision
	bool Collision(CRectangle r, Vector2& o);

	//Get
	int	 GetEnemyCount()  const { return m_EnemyCount; }
	int	 GetItemCount()   const { return m_ItemCount; }
	int	 GetObjectCount() const { return m_ObjectCount; }

};

