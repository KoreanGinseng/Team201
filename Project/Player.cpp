#include		"Player.h"
#include		"GameDefine.h"

//ゲームパッドからキーボードへの切り替えフラグ
bool	g_OperationDebug = true;
//キーボード、ゲームパッドのテスト操作方法の説明の表示フラグ
bool	g_PadRenderDebug = false;
bool	g_KeyRenderDebug = false;

CPlayer::CPlayer() {
	//オブジェクト生成時の初期化
	m_Skillrang = 0.0f;

	m_PosX = 0;
	m_PosY = 0;

	m_MoveX = 0;
	m_MoveY = 0;

	m_MoveX2 = 0;
	m_MoveY2 = 0;

	m_Hp = PLAYER_MAXHP;
	m_Life = PLAYER_MAXLIFE;

	m_bJump = false;
	m_bPowerUp = false;
	m_bTrigger = false;


}

CPlayer::~CPlayer() {

	Release();

}

bool CPlayer::Load() {
	//HPテクスチャーの読み込み
	if (!m_HpTexture.Load("Hp.png")) {

		return false;

	}

	return true;

}

void CPlayer::Initialize() {
	//スキルの範囲を初期化
	m_Skillrang = 0.0f;
	//座標の初期化
	m_PosX = g_pGraphics->GetTargetWidth() / 2;
	m_PosY = 0;
	//移動量の初期化
	m_MoveX = 0;
	m_MoveY = 0;
	//HPの初期化
	m_Hp = PLAYER_MAXHP;
	//残機の初期化
	m_Life = PLAYER_MAXLIFE;
	//ジャンプフラグの初期化
	m_bJump = false;
	//パワーアップフラグの初期化
	m_bPowerUp = false;
	//スキルの発動フラグを初期化
	m_bTrigger = false;


}

void CPlayer::Update() {

	
	//操作の更新
	Operation();
	//残機処理の更新
	LifeDecrease();

	
}

void CPlayer::Operation() {

	//エンターキーを押した場合、ゲームパッドからキーボードに操作を切り替える
	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {

		g_OperationDebug = !g_OperationDebug;
	}

	//コントローラーがPCに接続されている場合操作できる
	if (g_pInput->GetGamePadCount() && g_OperationDebug) {

		g_KeyRenderDebug = false;

		//スタートボタンを押した場合、テスト操作方法の説明を表示
		if (g_pGamePad->IsKeyPush(GAMEKEY_START)) {

			g_PadRenderDebug = !g_PadRenderDebug;
		}

		PadOperation();


	}
	//キーボード操作
	else {

		g_PadRenderDebug = false;

		//0キーを押した場合、テスト操作方法の説明を表示
		if (g_pInput->IsKeyPush(MOFKEY_0)) {

			g_KeyRenderDebug = !g_KeyRenderDebug;
		}

		KeyOperation();
	}

}

void CPlayer::TestPadOperation() {

	//ダメージのテスト処理
	if (g_pGamePad->IsKeyPush(GAMEKEY_X)) {

		m_Hp -= 5;

	}//パワーアップのテスト処理
	else if (g_pGamePad->IsKeyPush(GAMEKEY_Y)) {

		m_bPowerUp = !m_bPowerUp;

	}//エフェクトのテスト処理
	else if (g_pGamePad->IsKeyPush(GAMEKEY_RB)) {

		g_pEffectManager->Start(m_PosX + PLAYER_WIDTH * 0.5f, m_PosY + PLAYER_HEIGHT * 0.5f, EFC_TEST);

	}//サウンドの再生テスト
	else if (g_pGamePad->IsKeyPush(GAMEKEY_LB)) {

		g_pSoundManager->Start(SUD_SOUNDBGM, SOUND_BGM);

	}//サウンドのストップテスト1
	else if (g_pGamePad->IsKeyPush(GAMEKEY_START)) {

		g_pSoundManager->Stop(SUD_SOUNDBGM, STOP_SUDDEN);

	}//サウンドのストップテスト2
	else if (g_pGamePad->IsKeyPush(GAMEKEY_BACK)) {

		g_pSoundManager->Stop(SUD_SOUNDBGM,STOP_GRADUALLY);

	}

}

void CPlayer::TestKeyOperation() {

	//ダメージのテスト処理
	if (g_pInput->IsKeyPush(MOFKEY_1)) {

		m_Hp -= 5;

	}//パワーアップのテスト処理
	else if (g_pInput->IsKeyPush(MOFKEY_2)) {

		m_bPowerUp = !m_bPowerUp;

	}//エフェクトのテスト処理
	else if (g_pInput->IsKeyPush(MOFKEY_3)) {

		g_pEffectManager->Start(m_PosX + PLAYER_WIDTH * 0.5f, m_PosY + PLAYER_HEIGHT * 0.5f, EFC_TEST);

	}//サウンドの再生テスト
	else if (g_pInput->IsKeyPush(MOFKEY_4)) {

		g_pSoundManager->Start(SUD_SOUNDBGM, SOUND_BGM);

	}//サウンドのストップテスト1
	else if (g_pInput->IsKeyPush(MOFKEY_5)) {

		g_pSoundManager->Stop(SUD_SOUNDBGM, STOP_SUDDEN);

	}//サウンドのストップテスト2
	else if (g_pInput->IsKeyPush(MOFKEY_6)) {

		g_pSoundManager->Stop(SUD_SOUNDBGM, STOP_GRADUALLY);

	}

}

void CPlayer::PadOperation() {

	//スキルの更新
	Skill();
	//テスト操作用
	TestPadOperation();

	//スティックを右か左に倒した場合、倒した方向に移動
	if (g_pGamePad->GetStickHorizontal() > 0.8f) {

		m_MoveX += 0.3f;
		m_MoveX2 += 2.5f;
		if (m_MoveX > PLAYER_MAXSPEED) {

			m_MoveX = PLAYER_MAXSPEED;

		}
		if (m_MoveX2 > PLAYER_MAXSPEED * 2) {

			m_MoveX2 = PLAYER_MAXSPEED * 2;

		}
	}
	else if (g_pGamePad->GetStickHorizontal() < -0.8f) {

		m_MoveX -= 0.3f;
		m_MoveX2 -= 2.5f;
		if (m_MoveX < -PLAYER_MAXSPEED) {

			m_MoveX = -PLAYER_MAXSPEED;

		}
		if (m_MoveX2 < -PLAYER_MAXSPEED * 2) {

			m_MoveX2 = -PLAYER_MAXSPEED * 2;

		}
	}//スティックを離した場合（移動の操作をしていない場合）
	else {

		//移動量が0なら処理に入らない
		//移動量が存在する場合、徐々に移動量を0にする
		if (m_MoveX > 0) {

			m_MoveX -= 0.2f;

			if (m_MoveX < 0) {

				m_MoveX = 0;
			}

		}
		else if(m_MoveX<0){

			m_MoveX += 0.2f;

			if (m_MoveX > 0) {

				m_MoveX = 0;
			}

		}
		//移動量が0なら処理に入らない
		//移動量が存在する場合、徐々に移動量を0にする
		if (m_MoveX2 > 0) {

			m_MoveX2 -= 2.5f;

			if (m_MoveX2 < 0) {

				m_MoveX2 = 0;
			}

		}
		else if (m_MoveX2 < 0) {

			m_MoveX2 += 2.5f;

			if (m_MoveX2 > 0) {

				m_MoveX2 = 0;
			}

		}
	}

	//移動量を座標に加算
	m_PosX += m_MoveX;

	//Aボタンを押下かつジャンプフラグがたっていない場合ジャンプする
	if (g_pGamePad->IsKeyPush(GAMEKEY_A)&&!m_bJump) {

		//ジャンプ効果音のテスト処理
		g_pSoundManager->Start(SUD_SOUNDEFFECT, SOUND_EFFECT);

		m_bJump = true;

		//パワーアップフラグが立っている場合、ジャンプ力上昇
		if (m_bPowerUp) {

			m_MoveY = PLAYER_HIGHJUMP;

		}
		else {

			m_MoveY = PLAYER_JUMP;

		}
		
	}

	m_MoveY += PLAYER_GRAVITY;

	m_PosY += m_MoveY;

	

}

void CPlayer::KeyOperation() {

	//テスト操作用
	TestKeyOperation();

	//スティックを右か左に倒した場合、倒した方向に移動
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT)) {

		m_MoveX += 0.2f;
		m_MoveX2 += 2.5f;
		if (m_MoveX > PLAYER_MAXSPEED) {

			m_MoveX = PLAYER_MAXSPEED;

		}
		if (m_MoveX2 > PLAYER_MAXSPEED * 2) {

			m_MoveX2 = PLAYER_MAXSPEED * 2;

		}

	}
	else if (g_pInput->IsKeyHold(MOFKEY_LEFT)) {

		m_MoveX -= 0.2f;
		m_MoveX2 -= 2.5f;

		if (m_MoveX < -PLAYER_MAXSPEED) {

			m_MoveX = -PLAYER_MAXSPEED;

		}
		if (m_MoveX2 < -PLAYER_MAXSPEED * 2) {

			m_MoveX2 = -PLAYER_MAXSPEED * 2;

		}

	}//スティックを離した場合（移動の操作をしていない場合）
	else {

		//移動量が0なら処理に入らない
		//移動量が存在する場合、徐々に移動量を0にする
		if (m_MoveX > 0) {

			m_MoveX -= 0.3f;

			if (m_MoveX < 0) {

				m_MoveX = 0;
			}

		}
		else if (m_MoveX < 0) {

			m_MoveX += 0.3f;

			if (m_MoveX > 0) {

				m_MoveX = 0;
			}

		}

		//移動量が0なら処理に入らない
		//移動量が存在する場合、徐々に移動量を0にする
		if (m_MoveX2 > 0) {

			m_MoveX2 -= 2.5f;

			if (m_MoveX2 < 0) {

				m_MoveX2 = 0;
			}

		}
		else if (m_MoveX2 < 0) {

			m_MoveX2 += 2.5f;

			if (m_MoveX2 > 0) {

				m_MoveX2 = 0;
			}

		}
	}

	//移動量を座標に加算
	m_PosX += m_MoveX;

	//Aボタンを押下かつジャンプフラグがたっていない場合ジャンプする
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump) {

		//ジャンプ効果音のテスト処理
		g_pSoundManager->Start(SUD_SOUNDEFFECT, SOUND_EFFECT);

		m_bJump = true;

		//パワーアップフラグが立っている場合、ジャンプ力上昇
		if (m_bPowerUp) {

			m_MoveY = PLAYER_HIGHJUMP;

		}
		else {

			m_MoveY = PLAYER_JUMP;

		}

	}

	m_MoveY += PLAYER_GRAVITY;

	m_PosY += m_MoveY;

}

void CPlayer::Skill() {

	//スキルの円に座標や半径を代入
	m_SkillCircle.x = m_PosX + PLAYER_WIDTH / 2;
	m_SkillCircle.y = m_PosY + PLAYER_HEIGHT / 2;
	m_SkillCircle.r = m_Skillrang;

	//LTボタンを押した場合、スキルが発動
	if (g_pGamePad->GetPadState()->lZ > 500) {

		m_bTrigger = true;

	}
	else if (g_pGamePad->GetPadState()->lZ < 1) {

		m_bTrigger = false;

	}

	//スキルが発動している場合ターゲットの範囲を広げる
	if (m_bTrigger) {

		m_Skillrang += 10;

		if (m_Skillrang >= PLAYER_MAXSKILLRANGE) {

			m_Skillrang = PLAYER_MAXSKILLRANGE;

		}
	}
	else {

		if (m_Skillrang > 0.0f) {

			m_Skillrang = 0.0f;

		}

	}

}

void CPlayer::SkillColision(CEnemy* pene, int eneCount, CObject* pobj, int objCount) {
//表示されている要素数を探す、その数を数える
	//要素の数をを継続条件に、格納した要素数を引いていく

	//表示されている敵の要素数を順に格納
	list<int> element; 
	list<int>::iterator itr;
	
	int min = 0;
	int idx = 0;

	for (int i = 0; i < eneCount; i++) {

		if (!pene[i].GetShow()) {

			continue;

		}

		//表示されていてスキルの円に敵が当たっている場合、その敵の要素を入れる
		if (CollisionRectCircle(pene[i].GetRect(), m_SkillCircle)) {

			element.push_back(i);
			pene[i].TestSetColor();
		}

	}


	//Listのポインタ
	itr = element.begin();

	float stx = m_PosX + PLAYER_WIDTH * 0.5f;
	float sty = m_PosY + PLAYER_HEIGHT;
	/*float stx = m_PosX + m_Motion.GetStrRect().GetWidth()*0.5f;
		float sty = m_m_PosX + m_Motion.GetStrRect().GetHeight();*/
	
	for (auto itr = element.cbegin(); itr != element.cend();++itr) {

		CRectangle erec = pene[*itr].GetRect();

		Vector2 cv = erec.GetCenter();

		float dx = cv.x - stx;
		float dy = cv.y - sty;

		float d = (dx*dx + dy * dy);	

	}

}

void CPlayer::LifeDecrease() {
	//HPが0以下になった場合残機を減らしHPを初期値に戻す
	if (m_Hp <= 0) {

		m_Life--;

		m_Hp = PLAYER_MAXHP;
	}
}

void CPlayer::Render(Vector2 scroll) {

	//プレイヤー(仮)の描画
	CGraphicsUtilities::RenderRect(scroll.x, scroll.y, scroll.x + PLAYER_WIDTH, scroll.y + PLAYER_HEIGHT, MOF_XRGB(255, 0, 0));
	//プレイヤーのHPの描画
	RenderState();
	//デバックの描画
	RenderDebug();

	CGraphicsUtilities::RenderCircle(scroll.x+PLAYER_WIDTH / 2, scroll.y + PLAYER_WIDTH / 2,m_Skillrang, MOF_COLOR_RED);

}

void CPlayer::RenderState() {
	//HPの値によってケージの長さを変化
	CRectangle rec(0, 0, 532 * (m_Hp*0.01f), 64);

	m_HpTexture.Render(248, 150, rec);


	
}

void CPlayer::RenderDebug() {

	CGraphicsUtilities::RenderString(0, 30, MOF_XRGB(0, 255, 0), "テスト操作方法説明の表示:キーボードの場合0キー : ゲームパッドの場合STRATボタン");
	CGraphicsUtilities::RenderString(0, 60, MOF_XRGB(0, 255, 0), "ゲームパッドに接続されている状態でもエンターキーで操作をキーボードと切り替え可能");
	CGraphicsUtilities::RenderString(0, 90, MOF_XRGB(0, 255, 0), "m_MoveX %.f m_MoveY %.f m_bPowerUp %d m_bJump %d m_Hp %d m_Life %d m_PosX %.f", m_MoveX, m_MoveY, m_bPowerUp, m_bJump, m_Hp, m_Life,m_PosX);
	

	if (g_KeyRenderDebug) {

		CGraphicsUtilities::RenderString(0, 120, MOF_XRGB(255, 0, 0), "1キーで疑似ダメージ: 2キーで強化: 3キーでエフェクト: 4キーでBGM再生: 5キーでBGM急停止: ");
		CGraphicsUtilities::RenderString(0, 150, MOF_XRGB(255, 0, 0), "6キーでBGM徐々に停止");
	}
	
	if (g_PadRenderDebug) {

		CGraphicsUtilities::RenderString(0, 120, MOF_XRGB(255, 0, 0), "スティックで移動: Aボタンでジャンプ: Xボタンで疑似ダメージ Yボタンで強化: RBボタンでエフェクト:");
		CGraphicsUtilities::RenderString(0, 150, MOF_XRGB(255, 0, 0), " LBボタンでBGM再生: STARTボタンでBGM急停止: BACKボタンでBGM徐々に停止");

	}
	
	
}

void CPlayer::Release() {
	//HPテクスチャー(仮)の解放
	m_HpTexture.Release();
}

void CPlayer::CollisionStage(Vector2 o) {
	m_PosX += o.x;
	m_PosY += o.y;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化
	if (o.y < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
		if (m_bJump)
		{
			m_bJump = false;
		}
	}
	else if (o.y > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する
	if ((o.x < 0 && m_MoveX>0) || (o.x > 0 && m_MoveX < 0))
	{
		m_MoveX = 0;
	}
}