#include	"Ranking.h"

char KeyBoard[4][10] = {
	{'1','2','3','4','5','6','7','8','9','0' },
    {'q','w','e','r','t','y','u','i','o','p' },
	{'a','s','d','f','g','h','j','k','l',';' },
	{'z','x','c','v','b','n','m',',','.','/' }
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

		SendKeyBoard(0, 8);

	//�G���^�[�L�[�����������ɓ��͒������������
	if (g_pImeInput->GetEnterString()->GetLength() > 0)
	{
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

void CRanking::SendKeyBoard(int x, int y) {
	keybd_event(KeyBoard[x][y], (BYTE)MapVirtualKey(KeyBoard[x][y], 0), 0, 0);
	keybd_event(KeyBoard[x][y], (BYTE)MapVirtualKey(KeyBoard[x][y], 0), KEYEVENTF_KEYUP, 0);
}