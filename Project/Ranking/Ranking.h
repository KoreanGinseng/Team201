#pragma once
#include	"Mof.h"
#include	"../SceneBase.h"

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
	//! Ime�֘A
	CString						 m_String;
	int							 m_VisibleCount;		//�_�ŗp�J�E���g
	Vector2						 m_MousePos;
	CFont					     m_NameFont;			//�����L���O�o�^�p�t�H���g
	bool						 m_bInputEnable;		//���͒����̔���
	int							 m_CursolPointX;

	int							 m_InputCount;

	CDynamicArray<RankingEntry*> m_RankingEntryArray;	//�����L���O�o�^���L�^����z��

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

	void SendKeyBoard(int y, int x);
	
	CRectangle GetTextBoxRect() { return CRectangle(g_pGraphics->GetTargetWidth() / 2 - TEXTBOX_WIDHT, TEXTBOX_TOP,
													g_pGraphics->GetTargetWidth() / 2 + TEXTBOX_WIDHT + TEXTBOX_MARGIN, TEXTBOX_TOP + m_NameFont.GetSize()); }	//�e�L�X�g�{�b�N�X�̋�`



};

#define	g_pImeInput CImeProc::GetImeInput()