#include	"Ranking.h"
#include	"VirtualKeyBoard.h"

//unsigned char KeyBoard[4][10] = {
//	VK_1,VK_2,VK_3,VK_4,VK_5,VK_6,VK_7,VK_8,VK_9,VK_0,
//	VK_Q,VK_W,VK_E,VK_R,VK_T,VK_Y,VK_U,VK_I,VK_O,VK_P,
//	VK_A,VK_S,VK_D,VK_F,VK_G,VK_H,VK_J,VK_K,VK_L,VK_OEM_PLUS,
//	VK_Z,VK_X,VK_C,VK_V,VK_B,VK_N,VK_M,VK_OEM_COMMA,VK_OEM_PERIOD,VK_OEM_2
//};

unsigned char KeyBoard[KEYSIZE_Y][KEYSIZE_X] = {
	VK_1,VK_2,VK_3,VK_4,VK_5,VK_6,VK_7,VK_8,VK_9,VK_0,VK_OEM_MINUS,VK_OEM_7,VK_BACK,0,//13-1
	VK_TAB,VK_Q,VK_W,VK_E,VK_R,VK_T,VK_Y,VK_U,VK_I,VK_O,VK_P,VK_OEM_3,VK_OEM_4,0,//13-1
	VK_A,VK_S,VK_D,VK_F,VK_G,VK_H,VK_J,VK_K,VK_L,VK_OEM_PLUS,VK_OEM_1,VK_OEM_6,0,0,//12-1
	VK_Z,VK_X,VK_C,VK_V,VK_B,VK_N,VK_M,VK_OEM_COMMA,VK_OEM_PERIOD,VK_OEM_2,VK_OEM_102,0,0,0,//12-1
	VK_SPACE,VK_SHIFT,0,0,0,0,0,0,0,0,0,0,0,0,//1-1
};


CRanking::CRanking() :
m_bInit(false){

}

bool CRanking::Load() {

	
	return TRUE;
}

void CRanking::Initialize() {
	m_KeyMaxSize = 0;
	m_bShift = false;
	m_KeySelectX = 0;
	m_KeySelectY = 0;
	m_KeyOffSet .x = (g_pGraphics->GetTargetWidth() - 32*KEYSIZE_X) * 0.5f;
	m_KeyOffSet.y = (g_pGraphics->GetTargetHeight() - 32*KEYSIZE_Y) * 0.5f;
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
		CGraphicsUtilities::RenderString(10, 100 + i * 50, "%s", m_RankingEntryArray[i].Name.GetString());
	}

	KeyRender();

}

void CRanking::RenderDebug() {
	//CGraphicsUtilities::RenderString(10, 200, "%c", 0x7e);
	CGraphicsUtilities::RenderRect(m_KeyOffSet.x + ((m_KeySelectX+1) * 32), m_KeyOffSet.y + ((m_KeySelectY) * 32), m_KeyOffSet.x + ((m_KeySelectX + 1) * 32) + 32, m_KeyOffSet.y + ((m_KeySelectY ) * 32) + 32, MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderString(0, 100, "KeyMaxSize %d KeySelectX %d KeySelectY %d", m_KeyMaxSize,m_KeySelectX,m_KeySelectY);
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
	
	CString it;
	g_pImeInput->GetInputImeString(it);
	//MOF_PRINTLOG("%s\n", it.GetString());

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
	//if (g_pImeInput->GetEnterString()->GetLength() > 0) //����
	//{
	//	//�o�^���閼�O�͂���ł�낵��
	//	//

	//	//���͊m�蕶����Ƃ��Ēǉ�
	//	m_String += g_pImeInput->GetEnterString()->GetString();

	//	//���͂��ꂽ�l��ۑ�
	//	RankingEntry* re = new RankingEntry;
	//	re->Name = m_String;
	//	re->IconRect = CRectangle(0, 0, 0, 0);
	//	re->Score = 0;
	//	m_RankingEntryArray.Add(&re);
	//	delete re;
	//	re = nullptr;
	//	//�ǉ���������͒������񃊃Z�b�g
	//	g_pImeInput->ResetEnterString();
	//	//���͂𖳌��ɂ���
	//	g_pImeInput->SetEnable(FALSE);
	//	m_bInputEnable = false;
	//}
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

		for (int y = 0; y < KEYSIZE_Y; y++) {

			switch (y)
			{
			case 0:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "!\"#$%&\'()=~B");
				break;
			case 1:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "TQWERTYUIOP`{");
				break;
			case 2:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "ASDFGHJKL+*}");
				break;
			case 3:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "ZXCVBNM<>?_");
				break;
			case 4:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "Ss");
				break;

			}

		}

	}
	else {

		for (int y = 0; y < KEYSIZE_Y; y++) {

			switch (y)
			{
			case 0:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "1234567890-^B");
				break;
			case 1:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "Tqwertyuiop@[");
				break;
			case 2:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "asdfghjkl;:]");
				break;
			case 3:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "zxcvbnm,./\\");
				break;
			case 4:
				String(m_KeyOffSet.x, m_KeyOffSet.y + y * 32, FONT_SIZE, "Ss");
				break;


			}

		}
	}
	
	

	RenderDebug();

	
}

void CRanking::SendKeyBoard(unsigned char VK) {
	keybd_event(VK, (BYTE)MapVirtualKey(VK, 0), 0, 0);
	keybd_event(VK, (BYTE)MapVirtualKey(VK, 0), KEYEVENTF_KEYUP, 0);
}

void CRanking::PadOperation() {

	//�e�X�g.RB�œ��͊J�n
	if (g_pGamePad->IsKeyPush(GAMEKEY_RB)) {
		//�ҏW�\
		g_pImeInput->SetEnable(TRUE);
		m_bInputEnable = true;
	
		
	}
	//���͊J�n���Ă��Ȃ��Ԃ͏��������Ȃ�
	if (!m_bInputEnable) {

		return;

	}
	
	//VK�̑���
	VKOperation();

	//�ۑ�
	RankingSave();

}

void CRanking::VKOperation() {

	MaxKeyLook();

	/*�e�X�g*/
	//X�L�[�őI�������ɂ���
	if (g_pGameKey->KeyLeft()) {
		
		m_KeySelectX--;
		if (m_KeySelectY >= 1 && m_KeySelectX < 0) {

			m_KeySelectY--;

			MaxKeyLook();

			m_KeySelectX = m_KeyMaxSize;
		

		}
		else if (m_KeySelectY == 0 && m_KeySelectX < 0) {

			m_KeySelectX = 0;
		}
		


	}
	else if (g_pGameKey->KeyRigth()) {
	
		m_KeySelectX++;

		if (m_KeySelectY < KEYSIZE_Y-1 && m_KeySelectX>m_KeyMaxSize) {

			m_KeySelectX = 0;
			m_KeySelectY++;

		}
		else if (m_KeySelectY == KEYSIZE_Y-1 && m_KeySelectX > m_KeyMaxSize) {

			m_KeySelectX = m_KeyMaxSize;
		}

		

	}
	else if (g_pGameKey->KeyUp()) {

		m_KeySelectY--;
		if (m_KeySelectY < 0) {

			m_KeySelectY = 0;
		}

	}
	else if (g_pGameKey->KeyDown()) {

		m_KeySelectY++;
		if (m_KeySelectY >= KEYSIZE_Y-1) {

			m_KeySelectY = KEYSIZE_Y-1;

		}

		if (KeyBoard[m_KeySelectY][m_KeySelectX] == 0) {

			MaxKeyLook();

			m_KeySelectX = m_KeyMaxSize;
		}

	}

	
	if (KeyBoard[m_KeySelectY][m_KeySelectX] == VK_SHIFT) {

		if (g_pGamePad->IsKeyPush(GAMEKEY_START)) {

			m_bShift = !m_bShift;

			return;

		}
	}



	if (m_bShift) {
		//�v�b�V��
		keybd_event(VK_LSHIFT, (BYTE)MapVirtualKey(VK_LSHIFT, 0), 0, 0);

	}
	else {
		//����
		keybd_event(VK_LSHIFT, (BYTE)MapVirtualKey(VK_LSHIFT, 0), KEYEVENTF_KEYUP, 0);

	}


	if (g_pGamePad->IsKeyPush(GAMEKEY_B)) {

		SendKeyBoard(KeyBoard[m_KeySelectY][m_KeySelectX]);


	}

	if (g_pInput->IsKeyPush(MOFKEY_RIGHT)) {

		SendKeyBoard(VK_RIGHT);

	}
	else if (g_pInput->IsKeyPush(MOFKEY_LEFT)) {

		SendKeyBoard(VK_LEFT);

	}
	

}
void CRanking::RankingSave() {

	//���͊m��
	if (g_pGamePad->GetPadState()->lZ < -500.0f) {

		m_bInputEnable = false;

		//���͊m�蕶����Ƃ��Ēǉ�
		//m_String += g_pImeInput->GetEnterString()->GetString();
		CString it;
		g_pImeInput->GetInputImeString(it);

		//���͂��ꂽ�l��ۑ�
		RankingEntry* re = new RankingEntry;
		re->Name = it;
		re->IconRect = CRectangle(0, 0, 0, 0);
		re->Score = 0;
		m_RankingEntryArray.Add(re);
		delete re;
		re = nullptr;
		//�ǉ���������͒������񃊃Z�b�g
		g_pImeInput->ResetEnterString();
		//���͂𖳌��ɂ���
		g_pImeInput->SetEnable(FALSE);

		m_KeySelectX = 0;
		m_KeySelectY = 0;

		for (int i = 0; i < m_RankingEntryArray.GetArrayCount(); i++)
			MOF_PRINTLOG("%s\n", m_RankingEntryArray[i].Name.GetString());
	}

}

void CRanking::MaxKeyLook() {

	//keyselectY�̍ő�����Ă���v�f�[����
	for (m_KeyMaxSize = 0; KeyBoard[m_KeySelectY][m_KeyMaxSize + 1] != 0; m_KeyMaxSize++) {

		
	}


}