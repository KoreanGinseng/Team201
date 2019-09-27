#include		"Player.h"
#include		"GameDefine.h"


bool	bDebug = true;

CPlayer::CPlayer() {
	//オブジェクト生成時の初期化
	m_PosX = 0;
	m_PosY = 0;

	m_MoveX = 0;
	m_MoveY = 0;

	m_MoveX2 = 0;
	m_MoveY2 = 0;

	m_Hp = PLAYER_MAXHP;
	m_Life = PLAYER_MAXLIFE;

	m_bJump = false;


}

CPlayer::~CPlayer() {


}

bool CPlayer::Load() {
	//HPテクスチャーの読み込み
	if (!m_HpTexture.Load("Hp.png")) {

		return false;

	}

	return true;

}
void CPlayer::Initialize() {
	//座標の初期化
	//m_PosX = 0;
	m_PosX = 256.0f;
	//m_PosY = 0;
	m_PosY = 1344.0f;
	//移動量の初期化
	m_MoveX = 0;
	m_MoveY = 0;
	//HPの初期化
	m_Hp = PLAYER_MAXHP;
	//残機の初期化
	m_Life = PLAYER_MAXLIFE;
	//ジャンプフラグの初期化
	m_bJump = false;

}

void CPlayer::Update() {

	if (g_pInput->IsKeyPush(MOFKEY_F4))
	{
		bDebug = !bDebug;
	}

	if (bDebug)
	{
		Debug();
	}

	//コントローラーがPCに接続されている場合操作できる
	else if (g_pInput->GetGamePadCount()) {

		PadOperation();
		//ダメージのテスト処理
		if (g_pGamePad->IsKeyPush(GAMEKEY_X)) {

			m_Hp -= 5;

		}

	}
	//キーボード操作
	else {
		KeyOperation();
	}
	//残機処理の更新
	LifeDecrease();

	
}

void CPlayer::PadOperation() {

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

		m_bJump = true;

		m_MoveY = -10.0f;
	}

	m_MoveY += PLAYER_GRAVITY;

	m_PosY += m_MoveY;

	////とりあえず縦座標が300の位置をステージに
	//if (m_PosY > 300) {
	//	m_PosY = 300;
	//	m_MoveY = 0;
	//	if (m_bJump) {
	//		m_bJump = false;
	//	}
	//}

}

void CPlayer::KeyOperation() {

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

		m_bJump = true;

		m_MoveY = -10.0f;
	}

	m_MoveY += PLAYER_GRAVITY;

	m_PosY += m_MoveY;

	////とりあえず縦座標が300の位置をステージに
	//if (m_PosY > 100) {
	//	m_PosY = 100;
	//	m_MoveY = 0;
	//	if (m_bJump) {
	//		m_bJump = false;
	//	}
	//}
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
	//CGraphicsUtilities::RenderRect(m_PosX, m_PosY, m_PosX + PLAYER_WIDTH, m_PosY + PLAYER_HEIGHT, MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderRect(scroll.x, scroll.y, scroll.x + PLAYER_WIDTH, scroll.y + PLAYER_HEIGHT, MOF_XRGB(255, 0, 0));
	//プレイヤーのHPの描画
	RenderState();

	RenderDebug();

	CGraphicsUtilities::RenderCircle(scroll.x + PLAYER_WIDTH / 2, scroll.y + PLAYER_HEIGHT / 2, 512, MOF_COLOR_RED);

}

void CPlayer::RenderState() {
	//HPの値によってケージの長さを変化
	CRectangle rec(0, 0, 532 * (m_Hp*0.01f), 64);

	m_HpTexture.Render(248, 150, rec);


	
}

void CPlayer::RenderDebug() {

	CGraphicsUtilities::RenderString(0, 50, MOF_XRGB(255, 0, 0), "m_MoveX %.f m_MoveY %.f m_bJump %d m_Hp %d m_Life %d", m_MoveX,m_MoveY,m_bJump,m_Hp,m_Life);
	CGraphicsUtilities::RenderString(0, 100, MOF_XRGB(255, 0, 0), "スティックで移動: Aボタンでジャンプ: Xボタンで疑似ダメージ");
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

#ifdef _DEBUG
void CPlayer::Debug()
{
	int s = 5;
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_PosX -= s;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_PosX += s;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		m_PosY -= s;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		m_PosY += s;
	}
}
#endif	//_DEBUG