#include	"Item.h"

/**
 * コンストラクタ
 *
 */
CItem::CItem() :
m_pTexture(NULL) ,
m_pMotion() ,
m_Pos(Vector2(0,0)) ,
m_Move(Vector2(0,0)) ,
m_bShow(false) ,
m_SrcRect() {
}

/**
 * デストラクタ
 *
 */
CItem::~CItem(){
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
void CItem::Initialize(float px,float py,int type){
	m_Type = type;
	m_Pos.x = px;
	m_Pos.y = py;
	m_Move.x = 0.0f;
	m_Move.y = 0.0f;
	m_bShow = true;
	//アニメーションを作成
	m_pMotion = g_pAnimManager->GetResource(FileName[ANIMATION_ITEM_1])->GetMotion();
}

/**
 * 更新
 *
 */
void CItem::Update(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//重力により下に少しずつ下がる
	m_Move.y += GRAVITY;
	if(m_Move.y >= 20.0f)
	{
		m_Move.y = 20.0f;
	}
	//実際に座標を移動させる
	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	//アニメーションの更新
	m_pMotion->AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_pMotion->GetSrcRect();
}


/**
 * 描画
 */
void CItem::Render(Vector2 sp){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(sp.x, sp.y, m_SrcRect);
}

/**
 * デバッグ描画
 */
void CItem::RenderDebug(Vector2 sp){
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
void CItem::Release(void){
	m_pMotion->Release();
}

/**
 * ステージとの当たり
 *
 * 引数
 * [in]			ox					X埋まり量
 * [in]			oy					Y埋まり量
 */
void CItem::CollisionStage(Vector2 o){
	m_Pos.x += o.x;
	m_Pos.y += o.y;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if(o.y < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if(o.y > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if(o.x < 0 && m_Move.x > 0)
	{
		m_Move.x = 0;
	}
	else if(o.x > 0 && m_Move.x < 0)
	{
		m_Move.x = 0;
	}
}
