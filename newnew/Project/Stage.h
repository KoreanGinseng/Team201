/*****************************************************************
 *	@file			Stage.h
 *	@brief			ステージクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

//INCLUDE
#include	"Mof.h"
#include	<vector>
#include	<string>
#include	"GameDefine.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"TargetObj.h"
#include	"MapObj.h"
#include	"BackChip.h"

#define		RIGHTSLOPE		10
#define		RIGHTSLOPE2		23

class CBackChip;

class CStage
{
private:
	CTexturePtr	m_pBackTexture;
	CTexturePtr	m_pChipTexture;
	std::vector<CTexturePtr>	m_pMapObjTexture;
	std::vector<CTexturePtr>	m_pBackChipTexture;
	std::vector<CTexturePtr>	m_pEnemyTexture;
	std::vector<CTexturePtr>	m_pItemTexture;
	std::vector<CTexturePtr>	m_pObjectTexture;

	float		m_ChipSize;
	int			m_XCount;
	int			m_YCount;
	static float m_sChipSize;
	static int	m_sXCount;
	static int	m_sYCount;

	char*		m_pChipData;
	char*		m_pMapObjData;
	char*		m_pBackChipData;
	char*		m_pEnemyData;
	char*		m_pItemData;
	char*		m_pObjectData;
	char*		m_pObjEndData;

	int			m_MapObjTextureCount;
	int			m_BackChipTextureCount;
	int			m_EnemyTextureCount;
	int			m_ItemTextureCount;
	int			m_ObjectTextureCount;

	int			m_MapObjCount;
	int			m_BackChipCount;
	int			m_EnemyCount;
	int			m_ItemCount;
	int			m_ObjectCount;

	std::string IsExt(const char* pName);
	CTexturePtr TextureLoad(char* pName);
	int			ChipDataLoad(char* str, char* pData);
public:
	CStage(void);
	~CStage(void) {}
	bool Load(const char* pName);
	void Initialize(CDynamicArray<CEnemy*>* pEnemyArray, CDynamicArray<CItem*>*	pItemArray, CDynamicArray<CTargetObj*>*	pTargetObjArray, CDynamicArray<CMapObj*>* pMapObjArray, CDynamicArray<CBackChip*>* pBackChipArray);
	void Update(void);
	void RenderBack(Vector2 scroll);
	void RenderChip(Vector2 scroll);
	void Render(Vector2 scroll);
	void RenderDebug(Vector2 scroll);
	void Release(void);

	//Collision
	bool OverValue(CRectangle r, Vector2& o);

	//Get
	int			GetBackChipCount() const { return m_BackChipCount; }
	int			GetMapObjCount() const { return m_MapObjCount; }
	int			GetEnemyCount()  const { return m_EnemyCount; }
	int			GetItemCount()   const { return m_ItemCount; }
	int			GetObjectCount() const { return m_ObjectCount; }
	//Vector2		GetStageSize()	 const { return Vector2(m_XCount, m_YCount); }
	static Vector2 GetStageSize() { return Vector2(m_sXCount, m_sYCount); }
	static CRectangle  GetStageRect() { return CRectangle(0, 0, m_sXCount * m_sChipSize, m_sYCount * m_sChipSize); }
};

