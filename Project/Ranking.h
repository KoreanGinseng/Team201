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
	//! Ime�֘A
	CTexturePtr					 m_pTexture;			//�����L���O�w�i�̃e�N�X�`��
	CString						 m_String;
	int							 m_VisibleCount;		//�_�ŗp�J�E���g
	Vector2						 m_MousePos;
	Vector2						 m_PadPos;
	Vector2						 m_KeyOffSet;			//�L�[�z��̈ʒu
	CFont					     m_NameFont;			//�����L���O�o�^�p�t�H���g
	bool						 m_bInputEnable;		//���͒����̔���
	bool						 m_bShift;				//�V�t�g�t���O
	bool						 m_bInput;				//���͊m��t���O
	

	int							 m_CursolPointX;
	int							 m_KeyMaxSize;			//�s�z��̍ő�l
	int							 m_KeySelectX;			//���݂̕���X
	int							 m_KeySelectY;			//���݂̕���Y
	bool					     m_bInit;

	int							 m_InputCount;



	CDynamicArray<RankingEntry>  m_RankingEntryArray;	//�����L���O�o�^���L�^����z��

public:
	CRanking();
	~CRanking() {}
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void InfoRender(void);		//�����L���O���̕`��
	void UpdateDebug();
	void RenderDebug();
	void Release();
	int GetSceneName(void) { return SCENENO_RANKING; }

	//------------------------------------------------------------------------------------------
	void ImeInit();
	void ImeUpdate();
	void ImeRender();

	void SendKeyBoard(unsigned char VK);
	void PadOperation(void);				//�Q�[���p�b�h�ł̑���
	void RankingSave(const int type);		//�����L���O�̕ۑ�
	static int Sort(const void* a, const void* b);	//�����L���O�̃\�[�g
	void VKOperation(void);							//�L�[�{�[�h����
	void KeyRender(void);							//�L�[�z��̕`��
	void MaxKeyLook(void);							//�s�̍ő�v�f���̌���
	
	CRectangle GetTextBoxRect() { return CRectangle(g_pGraphics->GetTargetWidth() / 2 - TEXTBOX_WIDHT, TEXTBOX_TOP,
													g_pGraphics->GetTargetWidth() / 2 + TEXTBOX_WIDHT + TEXTBOX_MARGIN, TEXTBOX_TOP + m_NameFont.GetSize()); }	//�e�L�X�g�{�b�N�X�̋�`



};

#define	g_pImeInput CImeProc::GetImeInput()