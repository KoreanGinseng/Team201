#pragma once
#include	"Mof.h"
#include	"SceneBase.h"
#include	"GameDefine.h"
#include	"GameKey.h"
#include	"Coordinate.h"
#include	"Score.h"


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
	//! Ime�֘A

	CString						 m_String;
	int							 m_VisibleCount;		//�_�ŗp�J�E���g
	Vector2						 m_MousePos;
	Vector2						 m_PadPos;
	Vector2						 m_KeyOffSet;
	CFont					     m_NameFont;			//�����L���O�o�^�p�t�H���g
	bool						 m_bInputEnable;		//���͒����̔���
	bool						 m_bShift;
	bool						 m_bInput;
	

	int							 m_CursolPointX;
	int							 m_KeyMaxSize;
	int							 m_KeySelectX;
	int							 m_KeySelectY;
	bool					     m_bInit;

	int							 m_InputCount;



	CDynamicArray<RankingEntry>  m_RankingEntryArray;	//�����L���O�o�^���L�^����z��

public:
	CRanking();
	~CRanking() override {}
	bool Load() override;
	void Initialize() override;
	void Update() override;
	void Render() override;
	void RenderUI() override;
	void UpdateDebug();
	void RenderDebug() override;
	void Release() override;
	int GetSceneName(void) { return SCENENO_RANKING; }

	//------------------------------------------------------------------------------------------
	void ImeInit();
	void ImeUpdate();
	void ImeRender();

	void SendKeyBoard(unsigned char VK);
	void PadOperation(void);
	void RankingSave(const int type);
	static int Sort(const void* a, const void* b);
	void VKOperation(void);
	void KeyRender(void);
	//void RankingSort(std::vector<RankingEntry>* r_array);
	void MaxKeyLook(void);
	
	CRectangle GetTextBoxRect() { return CRectangle(g_pGraphics->GetTargetWidth() / 2 - TEXTBOX_WIDHT, TEXTBOX_TOP,
													g_pGraphics->GetTargetWidth() / 2 + TEXTBOX_WIDHT + TEXTBOX_MARGIN, TEXTBOX_TOP + m_NameFont.GetSize()); }	//�e�L�X�g�{�b�N�X�̋�`



};

#define	g_pImeInput CImeProc::GetImeInput()