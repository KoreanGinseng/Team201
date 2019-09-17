#include	"Ranking.h"
#include	"VirtualKeyBoard.h"

unsigned short int KeyBoard[4][10] = {
	VK_1,VK_2,VK_3,VK_4,VK_5,VK_6,VK_7,VK_8,VK_9,VK_0,
	VK_Q,VK_W,VK_E,VK_R,VK_T,VK_Y,VK_U,VK_I,VK_O,VK_P,
	VK_A,VK_S,VK_D,VK_F,VK_G,VK_H,VK_J,VK_K,VK_L,VK_OEM_PLUS,
	VK_Z,VK_X,VK_C,VK_V,VK_B,VK_N,VK_M,VK_OEM_COMMA,VK_OEM_PERIOD,VK_OEM_2
};

CRanking::CRanking() {
}

void CRanking::Load() {
	
}

void CRanking::Initialize() {
	//���͂��󂯕t���Ȃ�
	g_pImeInput->SetEnable(FALSE);
	m_bInputEnable = false;
	//���͒��������������
	g_pImeInput->SetInputString("");
	//���͊m�蕶������i�[
	m_String = "";
	m_VisibleCount = 0;
	m_InputCount = 0;
	//�t�H���g�̐���
	m_NameFont.Create(FONT_SIZE, "�l�r�@����");
}

void CRanking::Update() {
	//���݂̃}�E�X���W���擾
	g_pInput->GetMousePos(m_MousePos);

	//Ime�֘A�X�V
	ImeUpdate();
}

void CRanking::Render() {
	//Ime�֘A�`��
	ImeRender();
	
	for (int i = 0; i < m_RankingEntryArray.GetArrayCount(); i++) {
		CGraphicsUtilities::RenderString(10, 100 + i * 50, "%s", m_RankingEntryArray[i]->Name.GetString());
	}
}

void CRanking::RenderDebug() {
	//CGraphicsUtilities::RenderString(10, 200, "%c", 0x7e);
}

void CRanking::Release() {

}

void CRanking::ImeUpdate() {
	//�_�ŗp�J�E���g�����Z
	m_VisibleCount++;
	if (m_VisibleCount > CUtilities::GetFPS()) {
		m_VisibleCount = 0;
	}

	//�e�L�X�g�{�b�N�X���N���b�N���ē��͂��J�n
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (GetTextBoxRect().CollisionPoint(m_MousePos))
		{
			g_pImeInput->SetEnable(TRUE);
			m_bInputEnable = true;
		}

		//���͊m�蕶�������͒��ɕϊ�
		g_pImeInput->SetInputString(m_String);
		m_String = "";

	}
	

	//�G���^�[�L�[�����������ɓ��͒������������
	if (g_pImeInput->GetEnterString()->GetLength() > 0)
	{
		//�o�^���閼�O�͂���ł�낵��
		//

		//���͊m�蕶����Ƃ��Ēǉ�
		m_String += g_pImeInput->GetEnterString()->GetString();

		//���͂��ꂽ�l��ۑ�
		RankingEntry* re = new RankingEntry;
		re->Name = m_String;
		re->IconRect = CRectangle(0, 0, 0, 0);
		re->Score = 0;
		m_RankingEntryArray.Add(&re);

		//�ǉ���������͒������񃊃Z�b�g
		g_pImeInput->ResetEnterString();
		//���͂𖳌��ɂ���
		g_pImeInput->SetEnable(FALSE);
		m_bInputEnable = false;
	}
}

void CRanking::ImeRender() {
	//�e�L�X�g�{�b�N�X�̕`��
	CGraphicsUtilities::RenderFillRect(GetTextBoxRect(), MOF_COLOR_WHITE);
	//���͊m�蕶�����\��
	m_NameFont.RenderString(GetTextBoxRect().Left, GetTextBoxRect().Top, MOF_COLOR_RED, m_String.GetString());

	//���͊m�蕶���̋�`���擾
	CRectangle or;
	m_NameFont.CalculateStringRect(GetTextBoxRect().Left, GetTextBoxRect().Top, m_String.GetString(), or);

	//���͒��������\��(���͊m�蕶���̉E�ɕ��ׂĕ`��)
	CString it;
	g_pImeInput->GetInputImeString(it);
	m_NameFont.RenderString(or.Right, or.Top, MOF_COLOR_BLACK, it.GetString());

	//���͒������̋�`���擾
	CRectangle ir(GetTextBoxRect().Left, GetTextBoxRect().Top, GetTextBoxRect().Left + 2, GetTextBoxRect().Top + FONT_SIZE - 2);
	if (it.GetLength() > 0) {
		m_NameFont.CalculateStringRect(GetTextBoxRect().Left, GetTextBoxRect().Top, it.GetString(), ir);
	}

	//�J�[�\���`��
	if (((int)m_VisibleCount) >= CUtilities::GetFPS() / 2.0f && m_bInputEnable) {
		CGraphicsUtilities::RenderLine(ir.Right + 2, ir.Top + 2, ir.Right + 2, ir.Bottom, MOF_COLOR_BLACK);
	}
}

void CRanking::SendKeyBoard(int y, int x) {
	keybd_event(KeyBoard[y][x], (BYTE)MapVirtualKey(KeyBoard[y][x], 0), 0, 0);
	keybd_event(KeyBoard[y][x], (BYTE)MapVirtualKey(KeyBoard[y][x], 0), KEYEVENTF_KEYUP, 0);
}