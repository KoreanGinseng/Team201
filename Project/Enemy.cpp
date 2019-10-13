#include	"Enemy.h"

/**
 * コンストラクタ
 *
 */
CEnemy::CEnemy() :
m_pTexture(nullptr) ,
m_bShow(false) ,
m_HP(0) ,
m_DamageWait(0) {
}

/**
 * デストラクタ
 *
 */
CEnemy::~CEnemy(){
	//delete[] で解放されるようにReleaseをデストラクタで実行する
	Release();
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 *
 * 引数
 * [in]			px					X座標
 * [in]			py					Y座標
 * [in]			type				敵タイプ
 */
void CEnemy::Initialize(float px,float py) {
	m_pMove->Initialize();
	m_pMove->SetPos(Vector2(px, py));
	m_pMove->SetReverse(true);
	m_bShow = true;
	m_HP = 10;
	m_DamageWait = 0;
}

/**
 * 更新
 *
 */
void CEnemy::Update(const Vector2& playerPos) {
	//非表示
	if(!m_bShow)
	{
		return;
	}
	
	m_pMove->Update(playerPos.x, playerPos.y);

	if (m_pMove->GetAttack())
	{
		m_pAttack->KUpdate(m_pMove->GetPos().x, m_pMove->GetPos().y, m_pMove->GetReverce());
	}

	//実際に座標を移動させる
	m_Pos = m_pMove->GetPos();
	m_Pos += m_pMove->GetSpd();
	m_pMove->SetPos(m_Pos);
	m_SrcRect = m_pMove->GetSrcRect();

	//ダメージのインターバルを減らす
	if(m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}


/**
 * 描画
 */
void CEnemy::Render(const Vector2& sp){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//インターバル2フレームごとに描画をしない
	if(m_DamageWait % 4 >= 2)
	{
		return;
	}
	//描画矩形
	CRectangle dr = m_SrcRect;
	//反転フラグがONの場合描画矩形を反転させる
	if(m_pMove->GetReverce())
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//テクスチャの描画
	m_pTexture->Render(sp.x, sp.y, dr);
}

/**
 * デバッグ描画
 */
void CEnemy::RenderDebug(const Vector2& sp){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr(sp.x, sp.y, sp.x + m_SrcRect.GetWidth(), sp.y + m_SrcRect.GetHeight());
	CGraphicsUtilities::RenderRect(hr, MOF_XRGB(255,0,0));
}

/**
 * 解放
 *
 */
void CEnemy::Release(void) {
 	delete	m_pMove;
 	m_pMove = nullptr;
 	delete	m_pAttack;
 	m_pAttack = nullptr;
}

/**
 * ダメージ処理
 * 引数分のＨＰを減らしＨＰが０以下になれば敵を消去する
 *
 * 引数
 * [in]			dmg				ダメージ
 * [in]			bRev			反転フラグ
 */
void CEnemy::Damage(int dmg,bool bRev){

}

/**
 * ステージとの当たり
 */
void CEnemy::CollisionStage(Vector2 o) {
	m_Pos += o;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if(o.y < 0 && m_pMove->GetSpd().y > 0)
	{
		m_pMove->ResetSpd(WAY_Y);
	}
	else if(o.y > 0 && m_pMove->GetSpd().y < 0)
	{
		m_pMove->ResetSpd(WAY_Y);
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if(o.x < 0 && m_pMove->GetSpd().x > 0)
	{
		m_pMove->Reverse();
	}
	else if(o.x > 0 && m_pMove->GetSpd().x < 0)
	{
		m_pMove->Reverse();
	}
	m_pMove->SetPos(m_Pos);
}


void CEnemy::SetMoveAttack(const int& no)
{
	switch (no)
	{
	case ENEMY_KURIBO:
		m_pMove = new CEnemy_KURIBO();
		m_pAttack = new CEnemyAtack();
		break;
	case ENEMY_NOKONOKO:
		m_pMove = new CENEMY_NOKONOKO();
		break;
	case ENEMY_TERESA:
		m_pMove = new CENEMY_TERESA();
		break;
	case ENEMY_BAT:
		m_pMove = new CENEMY_BAT();
		break;
	case ENEMY_KOTEIHOUDAI:
		m_pMove = new CENEMY_KOTEIHOUDAI();
		break;
	default:
		break;
	}
}