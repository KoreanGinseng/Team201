/*****************************************************************
 *	@file			Title.h
 *	@brief			タイトルシーンクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

 // INCLUDE
#include "SceneBase.h"
#include	"GameDefine.h"

class CTitle :
	public CSceneBase
{
private:
	CTexturePtr	m_pTexture;
	CMovie		m_Movie;
	bool		m_bMovie;
	int			m_SelectNo;
	MofU32		m_RectColor;
	CRectangle	m_Rect;
	bool		m_bAlphaUp;
	int			m_Alpha;
public:
	CTitle(void);
	~CTitle(void) override;
	bool Load(void) override;
	void Initialize(void) override;
	void Update(void) override;
	void Render(void) override;
	void RenderUI(void) override;
	void RenderDebug(void) override;
	void Release(void) override;

	void UpdateDebug(void);

	int GetSceneName(void) { return SCENENO_TITLE; }
};

