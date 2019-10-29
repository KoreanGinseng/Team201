#include	"Ranking.h"
#include	"VirtualKeyBoard.h"

unsigned char KeyBoard[4][10] = {
	VK_1,VK_2,VK_3,VK_4,VK_5,VK_6,VK_7,VK_8,VK_9,VK_0,
	VK_Q,VK_W,VK_E,VK_R,VK_T,VK_Y,VK_U,VK_I,VK_O,VK_P,
	VK_A,VK_S,VK_D,VK_F,VK_G,VK_H,VK_J,VK_K,VK_L,VK_OEM_PLUS,
	VK_Z,VK_X,VK_C,VK_V,VK_B,VK_N,VK_M,VK_OEM_COMMA,VK_OEM_PERIOD,VK_OEM_2
};

CRanking::CRanking() :
m_bInit(false){
}

bool CRanking::Load() {

	
	return TRUE;
}

void CRanking::Initialize() {
	
	m_bShift = false;
	m_KeySelectX = 0;
	m_KeySelectY = 0;
	m_KeyOffSet .x = (g_pGraphics->GetTargetWidth() - 32*10) * 0.5f;
	m_KeyOffSet.y = (g_pGraphics->GetTargetHeight() - 32*4) * 0.5f;
}

void CRanking::Update() {
	
	
	if (g_pInput->GetGamePadCount()) {

		PadOperation();
	}
	//���݂̃}�E�X���W���擾
	g_pInput->GetMousePos(m_MousePos);

	if (!m_bInit)
	{
		ImeInit();
		m_bInit = true;
	}

	//Ime�֘A�X�V
	ImeUpdate();
}

void CRanking::Render() {
	//Ime�֘A�`��
	ImeRender();
	
	for (int i = 0; i < m_RankingEntryArray.GetArrayCount(); i++) {
		//CGraphicsUtilities::RenderString(10, 100 + i * 50, "%s", m_RankingEntryArray[i]->Name.GetString());
	}

	KeyRender();

}

void CRanking::RenderDebug() {
	//CGraphicsUtilities::RenderString(10, 200, "%c", 0x7e);
	CGraphicsUtilities::RenderRect(m_KeyOffSet.x + ((m_KeySelectX+1) * 32), m_KeyOffSet.y + ((m_KeySelectY) * 32), m_KeyOffSet.x + ((m_KeySelectX + 1) * 32) + 32, m_KeyOffSet.y + ((m_KeySelectY ) * 32) + 32, MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderString(0, 100, "%d", m_bShift);
}

void CRanking::Release() {

}

void CRanking::ImeInit()
{
	//���͂��󂯕t���Ȃ�
	//g_pImeInput->SetEnable(FALSE);
	CImeProc::GetImeInput()->SetEnable(FALSE);
	m_bInputEnable = false;
	//���͒��������������
	g_pImeInput->SetInputString("");
	//���͊m�蕶������i�[
	m_String = "";
	m_VisibleCount = 0;
	m_InputCount = 0;
	//�t�H���g�̐���
	m_NameFont.Create(IME_FONT_SIZE, "�l�r�@����");
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
		g_pImeInput->SetInputString(m_String); //����
		m_String = "";

	}
	

	//�G���^�[�L�[�����������ɓ��͒������������
	if (g_pImeInput->GetEnterString()->GetLength() > 0) //����
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
		delete re;
		re = nullptr;
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
	CRectangle ir(GetTextBoxRect().Left, GetTextBoxRect().Top, GetTextBoxRect().Left + 2, GetTextBoxRect().Top + IME_FONT_SIZE - 2);
	if (it.GetLength() > 0) {
		m_NameFont.CalculateStringRect(GetTextBoxRect().Left, GetTextBoxRect().Top, it.GetString(), ir);
	}

	//�J�[�\���`��
	if (((int)m_VisibleCount) >= CUtilities::GetFPS() / 2.0f && m_bInputEnable) {
		CGraphicsUtilities::RenderLine(ir.Right + 2, ir.Top + 2, ir.Right + 2, ir.Bottom, MOF_COLOR_BLACK);
	}
}

void CRanking::KeyRender() {

	if (!m_bInputEnable) {

		return;

	}

	if (m_bShift) {

		for (int y = 0; y < 4; y++) {

			switch (y)
			{
			case 0:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "!\"#$%&\'()=~|");
				break;
			case 1:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "QWERTYUIOP@{");
				break;
			case 2:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "ASDFGHJKL+*}");
				break;
			case 3:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "ZXCVBNM<>?_");
				break;

			}

		}

	}
	else {

		for (int y = 0; y < 4; y++) {

			switch (y)
			{
			case 0:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "1234567890-^\\");
				break;
			case 1:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "qwertyuiop@[");
				break;
			case 2:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "asdfghjkl;:]");
				break;
			case 3:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "zxcvbnm,./\\");
				break;

			}

		}
	}
	
	

	RenderDebug();

	
}

void CRanking::SendKeyBoard(unsigned char VK) {
	keybd_event(VK, (BYTE)MapVirtualKey(VK, 0), 0, 0);
	keybd_event(VK, (BYTE)MapVirtualKey(VK, 0), KEYEVENTF_KEYUP, 0);//���͂������͕̂ۑ�����Ă��邩
}

void CRanking::PadOperation() {

	//�V�t�g�{�^���������ƌŒ�ł�����x�����Ɖ���
	if (g_pGamePad->IsKeyPush(GAMEKEY_RB)) {
		//�ҏW�\
		g_pImeInput->SetEnable(TRUE);
		m_bInputEnable = true;
	
		
	}

	if (!m_bInputEnable) {

		return;

	}
	
	if (g_pGamePad->IsKeyPush(GAMEKEY_X)) {

		m_KeySelectX--;
		if (m_KeySelectY >= 1&&m_KeySelectX<0) {

			m_KeySelectX = 9;
			m_KeySelectY--;

		}
		else if (m_KeySelectY == 0 && m_KeySelectX < 0) {

			m_KeySelectX = 0;
		}
		

	}else if (g_pGamePad->IsKeyPush(GAMEKEY_B)) {

		m_KeySelectX++;

		if (m_KeySelectY < 3 && m_KeySelectX>9) {

			m_KeySelectX = 0;
			m_KeySelectY++;

		}
		else if (m_KeySelectY == 3 && m_KeySelectX > 9) {

			m_KeySelectX = 9;
		}

	}else if (g_pGamePad->IsKeyPush(GAMEKEY_Y)) {

		m_KeySelectY--;
		if (m_KeySelectY < 0) {

			m_KeySelectY = 0;
		}

	}else if (g_pGamePad->IsKeyPush(GAMEKEY_A)) {

		m_KeySelectY++;
		if (m_KeySelectY > 3) {

			m_KeySelectY = 4;

		}
	}

	if (m_KeySelectY == 4) {

		if (g_pGamePad->IsKeyPush(GAMEKEY_START)) {

			m_bShift = !m_bShift;

			return;

		}

	}

	if (m_bShift) {

		keybd_event(VK_LSHIFT, (BYTE)MapVirtualKey(VK_LSHIFT, 0), 0, 0);

	}
	

	//�͈͑I��SHIFT+CAPSLOCK�ŉ���
	if (g_pGamePad->IsKeyPush(GAMEKEY_START)) {

		SendKeyBoard(KeyBoard[m_KeySelectY][m_KeySelectX]);
		

	}

	//�ۑ��Ɠ��͕��@
	

	//���͊m��
	if (g_pGamePad->GetPadState()->lZ < -500.0f) {

		m_bInputEnable = false;

		//���͊m�蕶����Ƃ��Ēǉ�
		m_String += g_pImeInput->GetEnterString()->GetString();

		//���͂��ꂽ�l��ۑ�
		RankingEntry* re = new RankingEntry;
		re->Name = m_String;
		re->IconRect = CRectangle(0, 0, 0, 0);
		re->Score = 0;
		m_RankingEntryArray.Add(&re);
		delete re;
		re = nullptr;
		//�ǉ���������͒������񃊃Z�b�g
		g_pImeInput->ResetEnterString();
		//���͂𖳌��ɂ���
		g_pImeInput->SetEnable(FALSE);

		m_KeySelectX = 0;
		m_KeySelectY = 0;
		

	}

	



	

	
	
}