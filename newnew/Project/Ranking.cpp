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

	m_bInput = false;

}

bool CRanking::Load() {

	m_pEffect = NEW CEffectFade();
	m_pEffect->In(10);

	FILE* fpNE = fopen("RankingNE.dat", "rb");

	if (!fpNE) {

		return TRUE;
	}

	int ne;

	fread(&ne, sizeof(int), 1, fpNE);

	fclose(fpNE);

	m_RankingEntryArray.Release();
	
	FILE* fp = fopen("Ranking.dat", "rb");

	//std::vector<RankingEntry>* r_array = new std::vector<RankingEntry>();

	if (fp) {
		for (int i = 0; i < ne; i++) {

			RankingEntry r;
			fread(&r.IconRect, sizeof(CRectangle), 1, fp);
			int s;
			fread(&s, sizeof(int), 1, fp);
			char* str = NEW char[s + 1];
			str[s] = '\0';
			fread(str, sizeof(char), s, fp);
			r.Name.SetString(str);
			fread(&r.Time, sizeof(int), 1, fp);
			fread(&r.Score, sizeof(int), 1, fp);

			m_RankingEntryArray.Add(r);

			delete[] str;

			str = nullptr;
		}

		fclose(fp);

		

	}

	m_RankingEntryArray.Sort(Sort);

	//RankingSort(r_array);


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
	
	UpdateDebug();
	
	if (g_pInput->GetGamePadCount()) {

		PadOperation();
	}
	//現在のマウス座標を取得
	g_pInput->GetMousePos(m_MousePos);

	if (!m_bInit)
	{
		ImeInit();
		m_bInit = true;
	}

	//Ime関連更新
	ImeUpdate();
}

void CRanking::Render() {

	if (m_bInput) {

		CGraphicsUtilities::RenderString(0, 100, "スコア");
		CGraphicsUtilities::RenderString(100, 100, "タイム");
		CGraphicsUtilities::RenderString(200, 100, "名前");

		for (int i = 0; i < m_RankingEntryArray.GetArrayCount(); i++) {

			CGraphicsUtilities::RenderString(0, 100 +(( i + 1) * 50), "%d", m_RankingEntryArray[i].Score);
			CGraphicsUtilities::RenderString(100, 100 + ((i + 1) * 50), "%d", m_RankingEntryArray[i].Time);
			CGraphicsUtilities::RenderString(200, 100 +((i + 1) * 50), "%s", m_RankingEntryArray[i].Name.GetString());

		}

		return;

	}

	//Ime関連描画
	ImeRender();
	
	/*for (int i = 0; i < m_RankingEntryArray.GetArrayCount(); i++) {
		CGraphicsUtilities::RenderString(10, 100 + i * 50, "名前:%s タイム:%d", m_RankingEntryArray[i].Name.GetString(),m_RankingEntryArray[i].Score);
	}
	CGraphicsUtilities::RenderString(0, 200, "%d", (int)g_pTimeManager->GetNowTime());*/

	KeyRender();

	
}

void CRanking::RenderUI()
{
}

void CRanking::UpdateDebug() {

	if (g_pInput->IsKeyPush(MOFKEY_Q)) {
		m_NextSceneNo = SCENENO_GAME;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && g_pInput->IsKeyHold(MOFKEY_LCONTROL) && !m_pEffect->IsStart()) {
		m_pEffect->Out(10);

	}
	else if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {

	}
	if (m_pEffect->IsEnd() && m_pEffect->IsStart()) {
		m_NextSceneNo = SCENENO_TITLE;
	}
}

void CRanking::RenderDebug() {
	//CGraphicsUtilities::RenderString(10, 200, "%c", 0x7e);
	CGraphicsUtilities::RenderRect(m_KeyOffSet.x + ((m_KeySelectX+1) * 32), m_KeyOffSet.y + ((m_KeySelectY) * 32), m_KeyOffSet.x + ((m_KeySelectX + 1) * 32) + 32, m_KeyOffSet.y + ((m_KeySelectY ) * 32) + 32, MOF_XRGB(0, 255, 0));
	/*CGraphicsUtilities::RenderString(0, 100, "KeyMaxSize %d KeySelectX %d KeySelectY %d", m_KeyMaxSize,m_KeySelectX,m_KeySelectY);*/
}

void CRanking::Release() {

	if (m_pEffect) {

		delete m_pEffect;
		m_pEffect = nullptr;

	}

	g_pScore->Release();

//	g_pGameKey->Release();

}

void CRanking::ImeInit()
{
	//入力を受け付けない
	//g_pImeInput->SetEnable(FALSE);
	CImeProc::GetImeInput()->SetEnable(FALSE);
	m_bInputEnable = false;
	//入力中文字列を初期化
	g_pImeInput->SetInputString("");
	//入力確定文字列を格納
	m_String = "";
	m_VisibleCount = 0;
	m_InputCount = 0;
	//フォントの生成
	m_NameFont.Create(IME_FONT_SIZE, "ＭＳ　明朝");
}

void CRanking::ImeUpdate() {
	//点滅用カウントを加算
	m_VisibleCount++;
	if (m_VisibleCount > CUtilities::GetFPS()) {
		m_VisibleCount = 0;
	}
	
	CString it;
	g_pImeInput->GetInputImeString(it);
	//MOF_PRINTLOG("%s\n", it.GetString());

	//テキストボックスをクリックして入力を開始
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (GetTextBoxRect().CollisionPoint(m_MousePos))
		{
			g_pImeInput->SetEnable(TRUE);
			m_bInputEnable = true;
		}

		//入力確定文字列を入力中に変換
		g_pImeInput->SetInputString(m_String); //ここ
		m_String = "";

	}
	
	if (g_pImeInput->GetEnterString()->GetLength() > 0) {

		RankingSave(KEY);

	}

	//エンターキーを押した時に入力中文字があれば
	//if (g_pImeInput->GetEnterString()->GetLength() > 0) //ここ
	//{
	//	//登録する名前はこれでよろしか
	//	//

	//	//入力確定文字列として追加
	//	m_String += g_pImeInput->GetEnterString()->GetString();

	//	//入力された値を保存
	//	RankingEntry* re = new RankingEntry;
	//	re->Name = m_String;
	//	re->IconRect = CRectangle(0, 0, 0, 0);
	//	re->Score = 0;
	//	m_RankingEntryArray.Add(&re);
	//	delete re;
	//	re = nullptr;
	//	//追加したら入力中文字列リセット
	//	g_pImeInput->ResetEnterString();
	//	//入力を無効にする
	//	g_pImeInput->SetEnable(FALSE);
	//	m_bInputEnable = false;
	//}
}

void CRanking::ImeRender() {
	//テキストボックスの描画
	CGraphicsUtilities::RenderFillRect(GetTextBoxRect(), MOF_COLOR_WHITE);
	//入力確定文字列を表示
	m_NameFont.RenderString(GetTextBoxRect().Left, GetTextBoxRect().Top, MOF_COLOR_RED, m_String.GetString());

	//入力確定文字の矩形を取得
	CRectangle or;
	m_NameFont.CalculateStringRect(GetTextBoxRect().Left, GetTextBoxRect().Top, m_String.GetString(), or);

	//入力中文字列を表示(入力確定文字の右に並べて描画)
	CString it;
	g_pImeInput->GetInputImeString(it);
	m_NameFont.RenderString(or.Right, or.Top, MOF_COLOR_BLACK, it.GetString());

	//入力中文字の矩形を取得
	CRectangle ir(GetTextBoxRect().Left, GetTextBoxRect().Top, GetTextBoxRect().Left + 2, GetTextBoxRect().Top + IME_FONT_SIZE - 2);
	if (it.GetLength() > 0) {
		m_NameFont.CalculateStringRect(GetTextBoxRect().Left, GetTextBoxRect().Top, it.GetString(), ir);
	}

	//カーソル描画
	if (((int)m_VisibleCount) >= CUtilities::GetFPS() / 2.0f && m_bInputEnable) {
		CGraphicsUtilities::RenderLine(ir.Right + 2, ir.Top + 2, ir.Right + 2, ir.Bottom, MOF_COLOR_BLACK);
	}
}

//void CRanking::RankingSort(std::vector<RankingEntry>* r_array) {
//
//	/*std::sort(r_array->begin(),
//		r_array->end(),
//		[](const RankingEntry& a, const RankingEntry& b)
//	{return (a.Score == b.Score) ? (a.Name.GetLength() < b.Name.GetLength()) : (a.Score < b.Score); });*/
//
//	
//
//	/*for (int i = 0; i < r_array->size(); i++) {
//
//		m_RankingEntryArray.Add(&(r_array[i]));
//	}
//	
//*/
//	
//}


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

	//テスト.RBで入力開始
	if (g_pGamePad->IsKeyPush(XINPUT_R_BTN)) {
		//編集可能
		g_pImeInput->SetEnable(TRUE);
		m_bInputEnable = true;
	
		
	}
	//入力開始していない間は処理をしない
	if (!m_bInputEnable) {

		return;

	}
	
	//VKの操作
	VKOperation();

	if (g_pGamePad->IsKeyPush(XINPUT_L_TRIGGER)) {
		//保存
		SendKeyBoard(VK_RETURN);
	
		RankingSave(GAMEPAD);

	}

}

void CRanking::VKOperation() {

	MaxKeyLook();

	/*テスト*/
	//Xキーで選択を左にする
	if (g_pGamePad->IsKeyPush(XINPUT_DP_LEFT)) {
		
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
	else if (g_pGamePad->IsKeyPush(XINPUT_DP_RIGHT)) {
	
		m_KeySelectX++;

		if (m_KeySelectY < KEYSIZE_Y-1 && m_KeySelectX>m_KeyMaxSize) {

			m_KeySelectX = 0;
			m_KeySelectY++;

		}
		else if (m_KeySelectY == KEYSIZE_Y-1 && m_KeySelectX > m_KeyMaxSize) {

			m_KeySelectX = m_KeyMaxSize;
		}

		

	}
	else if (g_pGamePad->IsKeyPush(XINPUT_DP_UP)) {

		m_KeySelectY--;
		if (m_KeySelectY < 0) {

			m_KeySelectY = 0;
		}

	}
	else if (g_pGamePad->IsKeyPush(XINPUT_DP_DOWN)) {

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

		if (g_pGamePad->IsKeyPush(XINPUT_START)) {

			m_bShift = !m_bShift;

			return;

		}
	}



	if (m_bShift) {
		//プッシュ
		keybd_event(VK_LSHIFT, (BYTE)MapVirtualKey(VK_LSHIFT, 0), 0, 0);

	}
	else {
		//離す
		keybd_event(VK_LSHIFT, (BYTE)MapVirtualKey(VK_LSHIFT, 0), KEYEVENTF_KEYUP, 0);

	}


	if (g_pGamePad->IsKeyPush(XINPUT_B)) {

		SendKeyBoard(KeyBoard[m_KeySelectY][m_KeySelectX]);


	}

	if (g_pInput->IsKeyPush(MOFKEY_RIGHT)) {
		//?
		SendKeyBoard(VK_RIGHT);

	}
	else if (g_pInput->IsKeyPush(MOFKEY_LEFT)) {

		SendKeyBoard(VK_LEFT);

	}
	

}

int CRanking::Sort(const void* a, const void* b) {
	RankingEntry* r1 = (RankingEntry*)a;
	RankingEntry* r2 = (RankingEntry*)b;
	if (r1->Score > r2->Score) {

		return 0;
	}

	return 1;

}

void CRanking::RankingSave(const int type) {

	//入力確定
	
	m_bInputEnable = false;
	CString it;
	switch (type)
	{
	case KEY:
		it.SetString(g_pImeInput->GetEnterString()->GetString());
		break;
	case GAMEPAD:
		g_pImeInput->GetInputImeString(it);
		break;
	}
	//入力確定文字列として追加
	//m_String += g_pImeInput->GetEnterString()->GetString();
	
	
	

	//入力された値を保存
	RankingEntry* re = NEW RankingEntry;
	re->Name = it;
	re->IconRect = CRectangle(0, 0, 0, 0);
	re->Time = (int)g_pTimeManager->GetNowTime();
	re->Score = g_pScore->GetScore();
	m_RankingEntryArray.Add(re);
	delete re;
	re = nullptr;
	//追加したら入力中文字列リセット
	g_pImeInput->ResetEnterString();
	//入力を無効にする
	g_pImeInput->SetEnable(FALSE);

	m_KeySelectX = 0;
	m_KeySelectY = 0;

	FILE* fpNE = fopen("RankingNE.dat", "wb");

	int ne = m_RankingEntryArray.GetArrayCount();

	if (fpNE) {


		fwrite(&ne, sizeof(int), 1, fpNE);

	}

	fclose(fpNE);


	FILE* fp = fopen("Ranking.dat", "wb");


	for (int i = 0; i < ne; i++) {
		RankingEntry r = m_RankingEntryArray.GetData(i);
		fwrite(&r.IconRect, sizeof(CRectangle), 1, fp);
		int a = r.Name.GetLength();
		fwrite(&a, sizeof(int), 1, fp);
		fwrite(r.Name.GetString(), sizeof(char), a, fp);
		fwrite(&r.Time, sizeof(int), 1, fp);
		fwrite(&r.Score, sizeof(int), 1, fp);

	}

	fclose(fp);

	
	g_pImeInput->ResetEnterString();

	for (int i = 0; i < m_RankingEntryArray.GetArrayCount(); i++)
		MOF_PRINTLOG("%s\n", m_RankingEntryArray[i].Name.GetString());
	
	m_bInput = true;

}

void CRanking::MaxKeyLook() {

	//keyselectYの最大入っている要素端っこ
	for (m_KeyMaxSize = 0; KeyBoard[m_KeySelectY][m_KeyMaxSize + 1] != 0; m_KeyMaxSize++) {

		
	}


}