#include		"Player.h"
#include		"GameDefine.h"

CPlayer::CPlayer() {
	//オブジェクト生成時の初期化
	m_PosX = 0;
	m_PosY = 0;

	m_MoveX = 0;
	m_MoveY = 0;

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
	m_PosX = 0;
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

}

void CPlayer::Update() {

	//コントローラーがPCに接続されている場合操作できる
	if (g_pInput->GetGamePadCount()) {

		PadOperation();
		//ダメージのテスト処理
		if (g_pGamePad->IsKeyPush(GAMEKEY_X)) {

			m_Hp -= 5;

		}

	}
	//残機処理の更新
	LifeDecrease();

	
}

void CPlayer::PadOperation() {

	//スティックを右か左に倒した場合、倒した方向に移動
	if (g_pGamePad->GetStickHorizontal() > 0.8f) {

		m_MoveX += 0.3f;

		if (m_MoveX > PLAYER_MAXSPEED) {

			m_MoveX = PLAYER_MAXSPEED;

		}

	}
	else if (g_pGamePad->GetStickHorizontal() < -0.8f) {

		m_MoveX -= 0.3f;

		if (m_MoveX < -PLAYER_MAXSPEED) {

			m_MoveX = -PLAYER_MAXSPEED;

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
		else if(m_MoveX<0){

			m_MoveX += 0.3f;

			if (m_MoveX > 0) {

				m_MoveX = 0;
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

	//とりあえず縦座標が600の位置をステージに
	if (m_PosY > 600) {

		m_PosY = 600;

		m_MoveY = 0;

		if (m_bJump) {

			m_bJump = false;

		}

	}


	

}

void CPlayer::LifeDecrease() {
	//HPが0以下になった場合残機を減らしHPを初期値に戻す
	if (m_Hp <= 0) {

		m_Life--;

		m_Hp = PLAYER_MAXHP;
	}
}

void CPlayer::Render() {

	//プレイヤー(仮)の描画
	CGraphicsUtilities::RenderRect(m_PosX, m_PosY, m_PosX + PLAYER_WIDTH, m_PosY + PLAYER_HEIGHT, MOF_XRGB(255, 0, 0));
	//プレイヤーのHPの描画
	RenderState();

	RenderDebug();

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