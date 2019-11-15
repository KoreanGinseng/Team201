#pragma once
#include	"Mof.h"
#include	"TimeManager.h"
#include	"SceneBase.h"
#include	"GameDefine.h"
#include	"GameKey.h"
#include	"Coordinate.h"
#include	"Score.h"
#include	"_Fujiwara/Fujiwara.h"


#define		IME_FONT_SIZE	64
#define		FONT_LENGTH		10
#define		TEXTBOX_TOP		50
#define		TEXTBOX_WIDHT	IME_FONT_SIZE * (FONT_LENGTH / 2)
#define		TEXTBOX_MARGIN	20
#define		KEYSIZE_X		14
#define		KEYSIZE_Y		5


typedef struct tag_RankingEntry {
	
	CRectangle	IconRect;
	CString		Name;
	int			Time;
	int			Score;

} RankingEntry;

enum tag_Ranking {

	KEY,GAMEPAD,

};

class CRanking : public CSceneBase {
private:
	//! Ime関連
	CTexturePtr					 m_pTexture;			//ランキング背景のテクスチャ
	CString						 m_String;
	int							 m_VisibleCount;		//点滅用カウント
	Vector2						 m_MousePos;
	Vector2						 m_PadPos;
	Vector2						 m_KeyOffSet;			//キー配列の位置
	CFont					     m_NameFont;			//ランキング登録用フォント
	bool						 m_bInputEnable;		//入力中かの判定
	bool						 m_bShift;				//シフトフラグ
	bool						 m_bInput;				//入力確定フラグ
	

	int							 m_CursolPointX;
	int							 m_KeyMaxSize;			//行配列の最大値
	int							 m_KeySelectX;			//現在の文字X
	int							 m_KeySelectY;			//現在の文字Y
	bool					     m_bInit;

	int							 m_InputCount;



	CDynamicArray<RankingEntry>  m_RankingEntryArray;	//ランキング登録を記録する配列

public:
	CRanking();
	~CRanking() {}
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void InfoRender(void);		//ランキング情報の描画
	void UpdateDebug();
	void RenderDebug();
	void Release();
	int GetSceneName(void) { return SCENENO_RANKING; }

	//------------------------------------------------------------------------------------------
	void ImeInit();
	void ImeUpdate();
	void ImeRender();

	void SendKeyBoard(unsigned char VK);
	void PadOperation(void);				//ゲームパッドでの操作
	void RankingSave(const int type);		//ランキングの保存
	static int Sort(const void* a, const void* b);	//ランキングのソート
	void VKOperation(void);							//キーボード操作
	void KeyRender(void);							//キー配列の描画
	void MaxKeyLook(void);							//行の最大要素数の検索
	
	CRectangle GetTextBoxRect() { return CRectangle(g_pGraphics->GetTargetWidth() / 2 - TEXTBOX_WIDHT, TEXTBOX_TOP,
													g_pGraphics->GetTargetWidth() / 2 + TEXTBOX_WIDHT + TEXTBOX_MARGIN, TEXTBOX_TOP + m_NameFont.GetSize()); }	//テキストボックスの矩形



};

#define	g_pImeInput CImeProc::GetImeInput()