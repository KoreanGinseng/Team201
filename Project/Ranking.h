#pragma once
#include	"Mof.h"
#include	"SceneBase.h"

#define		FONT_SIZE		64
#define		FONT_LENGTH		10
#define		TEXTBOX_TOP		50
#define		TEXTBOX_WIDHT	FONT_SIZE * (FONT_LENGTH / 2)
#define		TEXTBOX_MARGIN	20

class CRanking : public CSceneBase {
private:
	CString m_String;
	int		m_VisibleCount;	//点滅用カウント
	Vector2 m_MousePos;
	CFont	m_NameFont;		//ランキング登録用フォント
	bool	m_bInputEnable;	//入力中かの判定
public:
	CRanking();
	~CRanking() {}
	void Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();

	//------------------------------------------------------------------------------------------
	void ImeUpdate();
	void ImeRender();

	CRectangle GetTextBoxRect() { return CRectangle(g_pGraphics->GetTargetWidth() / 2 - TEXTBOX_WIDHT, TEXTBOX_TOP,
													g_pGraphics->GetTargetWidth() / 2 + TEXTBOX_WIDHT + TEXTBOX_MARGIN, TEXTBOX_TOP + m_NameFont.GetSize()); }	//テキストボックスの矩形
};

#define	g_pImeInput CImeProc::GetImeInput()