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
	m_pMove->SetPos(Vector2(px, py));
	m_pMove->Initialize();
	m_pMove->SetReverse(false);
	m_bShow = true;
	m_HP = 10;
	m_DamageWait = 0;
}

/**
 * 更新
 *
 */
void CEnemy::Update(const Vector2& playerPos) {

	if (m_bSkill)
	{
		if (--m_StopWait < 0)
		{
			m_StopWait = m_StopWaitOffset;
			m_bSkill = false;
		}
	}

	//非表示
	if(!m_bShow || m_bSkill)
	{
		return;
	}

	m_pMove->Update(playerPos.x, playerPos.y);
	m_pMove->Animation();

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
	CRectangle hr(sp.x - m_Pos.x + GetRect().Left, sp.y - m_Pos.y + GetRect().Top, sp.x + GetRect().GetWidth(), sp.y + GetRect().GetHeight());
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

bool CEnemy::Collision(CRectangle rect, Vector2 & o)
{
	bool re = false;
	//当たり判定
	CRectangle cr = GetRect();
	//止まっていれば
	if (m_bSkill)
	{
		CRectangle brec = rect;
		brec.Top = brec.Bottom - 1;//
		brec.Expansion(-6, 0);//
		//下と当たり判定
		if (cr.CollisionRect(brec))
		{
			re = true;
			//下の埋まりなのでチップの上端から矩形の下端の値を引いた値が埋まり値
			o.y += cr.Top - brec.Bottom;
			rect.Top += cr.Top - brec.Bottom;
			rect.Bottom += cr.Top - brec.Bottom;
		}
		//左、右それぞれで範囲を限定した専用の矩形を作成する。
		CRectangle lrec = rect;
		lrec.Right = lrec.Left + 1;
		lrec.Expansion(0, -6);
		//引数のレクトの左と当たり判定
		if (cr.CollisionRect(lrec))
		{
			re = true;
			//左の埋まりなのでチップ右端から矩形の左端の値を引いた値が埋まりの値
			o.x += cr.Right - lrec.Left;
			rect.Left += cr.Right - lrec.Left;
			rect.Right += cr.Right - lrec.Left;
		}
		//右と当たり判定
		CRectangle rrec = rect;
		rrec.Left = rrec.Right - 1;
		rrec.Expansion(0, -6);
		if (cr.CollisionRect(rrec))
		{
			re = true;
			//右の埋まりなのでチップの左端から
			o.x += cr.Left - rrec.Right;
			rect.Left += cr.Left - rrec.Right;
			rect.Right += cr.Left - rrec.Right;
		}
		//上で範囲を限定した専用の矩形を作成する。
		CRectangle trec = rect;
		trec.Bottom = trec.Top - 1;//
		trec.Expansion(-6, 0);//
		//上と当たり判定
		if (cr.CollisionRect(trec))
		{
			re = true;
			//上の埋まりなのでチップした端から矩形の上端を
			o.y += cr.Bottom - trec.Top;
			rect.Top += cr.Bottom - trec.Top;
			rect.Bottom += cr.Bottom - trec.Top;
		}
	}
	return re;
}


void CEnemy::SetMoveAttack(const int& no)
{
	switch (no)
	{
	case ENEMY_KURIBO:
		m_pMove = new CEnemy_KURIBO();
		break;
	case ENEMY_NOKONOKO:
		m_pMove = new CENEMY_NOKONOKO();
		break;
	case ENEMY_BAT:
		m_pMove = new CENEMY_BAT();
		break;
	case ENEMY_TERESA:
		m_pMove = new CENEMY_TERESA();
		break;
	case ENEMY_KOTEIHOUDAI:
		m_pMove = new CENEMY_KOTEIHOUDAI();
		break;
	default:
		break;
	}
	m_pAttack = new CEnemyAtack();
	m_StopWaitOffset = 300;
	m_StopWait = m_StopWaitOffset;
	m_Type = no;
}