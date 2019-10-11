#pragma once
#include	"Mof.h"
#include	"SceneBase.h"
#include	"GameDefine.h"
#include	"GamePad.h"
#include	"Coordinate.h"
#include	"_Fujiwara/Fujiwara.h"


#define		IME_FONT_SIZE	64
#define		FONT_LENGTH		10
#define		TEXTBOX_TOP		50
#define		TEXTBOX_WIDHT	IME_FONT_SIZE * (FONT_LENGTH / 2)
#define		TEXTBOX_MARGIN	20


typedef struct tag_RankingEntry {
	CRectangle	IconRect;
	CString		Name;
	int			Score;
} RankingEntry;

class CRanking : public CSceneBase {
private:
	//! Ime関連
	CTexturePtr					 m_pTexture;
	CString						 m_String;
	int							 m_VisibleCount;		//点滅用カウント
	Vector2						 m_MousePos;
	Vector2						 m_PadPos;
	Vector2						 m_KeyOffSet;
	CCircle						 m_PosCircle;
	CFont					     m_NameFont;			//ランキング登録用フォント
	bool						 m_bInputEnable;		//入力中かの判定
	bool						 m_bPadInputMode;
	int							 m_CursolPointX;

	bool					     m_bInit;

	int							 m_InputCount;

	

	CDynamicArray<RankingEntry*> m_RankingEntryArray;	//ランキング登録を記録する配列

public:
	CRanking();
	~CRanking() {}
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();

	//------------------------------------------------------------------------------------------
	void ImeInit();
	void ImeUpdate();
	void ImeRender();

	void SendKeyBoard(int y, int x);
	void PadOperation(void);

	void KeyRender(void);
	
	CRectangle GetTextBoxRect() { return CRectangle(g_pGraphics->GetTargetWidth() / 2 - TEXTBOX_WIDHT, TEXTBOX_TOP,
													g_pGraphics->GetTargetWidth() / 2 + TEXTBOX_WIDHT + TEXTBOX_MARGIN, TEXTBOX_TOP + m_NameFont.GetSize()); }	//テキストボックスの矩形



};

#define	g_pImeInput CImeProc::GetImeInput()