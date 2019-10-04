/*****************************************************************
 *	@file			Player.cpp
 *	@brief			プレイヤークラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/

//INCLUDE
#include "Player.h"

//コンストラクタ
CPlayer::CPlayer(void) :
m_pTexture(nullptr),
m_Pos(Vector2(0,0)),
m_Move(Vector2(0,0)),
m_Spd(Vector2(0,0)),
m_bJump(false),
m_HP(10),
m_Stock(3)
{
}

//デストラクタ
CPlayer::~CPlayer(void)
{
}

//初期化
void CPlayer::Initialize(void)
{
	//画像データのセット
	m_pTexture = g_pAnimManager->GetResource(FileName[0])->GetTexture();
	//アニメーションデータのセット
	m_pMotion = g_pAnimManager->GetResource("playerAnim.bin")->GetMotion();
	//座標の初期化
	m_Pos = Vector2(g_pGraphics->GetTargetWidth() / 2, 0);
	//移動量の初期化
	m_Move = Vector2(0, 0);
	//移動速度の初期化
	m_Spd = Vector2(PLAYER_SPEED, PLAYER_JUMPPOW);
	//HPの初期化
	m_HP = PLAYER_MAXHP;
	//残機の初期化
	m_Stock = PLAYER_MAXSTOCK;
	//ジャンプフラグの初期化
	m_bJump = false;
	//パワーアップフラグの初期化
	m_bPowUp = false;
}

//更新
void CPlayer::Update(void)
{
	//コントローラーが接続されているか
	if (g_pInput->GetGamePadCount())
	{
		//コントローラー入力での移動量更新
		PadOparation();
	}

	//キーボード入力での移動量更新
	KeyOparation();

	//移動
	Move();

	//アニメーション更新
	Animation();
}

//描画
void CPlayer::Render(Vector2 screenPos)
{
	CRectangle dr = m_SrcRect;
	//反転フラグが立っているとき描画矩形を反転
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	m_pTexture->Render(screenPos.x, screenPos.y, dr);
}

//デバッグ描画
void CPlayer::RenderDebug(Vector2 screenPos)
{
	CGraphicsUtilities::RenderRect(screenPos.x + PLAYER_RECTDIS, screenPos.y + PLAYER_RECTDIS,
		screenPos.x + m_SrcRect.GetWidth() - PLAYER_RECTDIS, screenPos.y + m_SrcRect.GetHeight(), MOF_COLOR_RED);
}

//解放
void CPlayer::Release(void)
{

}

//パッドオペレーション
void CPlayer::PadOparation(void)
{
	//スティックを右か左に倒した場合、倒した方向に移動
	if (g_pGamePad->GetStickHorizontal() > 0.8f)
	{
		MoveAdd(WAY_RIGHT);
	}
	else if (g_pGamePad->GetStickHorizontal() < -0.8f)
	{
		MoveAdd(WAY_LEFT);
	}
	//スティックを離した場合（移動の操作をしていない場合）
	else
	{
		//移動量が0なら処理に入らない
		//移動量が存在する場合、徐々に移動量を0にする
		if (m_Move.x > 0)
		{
			MoveSub(WAY_RIGHT);
		}
		else if (m_Move.x < 0)
		{
			MoveSub(WAY_LEFT);
		}
		else
		{
			m_bMove = false;
		}
	}

	//Aボタンを押下かつジャンプフラグがたっていない場合ジャンプする
	if (g_pGamePad->IsKeyPush(GAMEKEY_A) && !m_bJump)
	{
		Jump();
	}
}

//キーオペレーション
void CPlayer::KeyOparation(void)
{
	//スティックを右か左に倒した場合、倒した方向に移動
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		MoveAdd(WAY_RIGHT);
	}
	else if (g_pInput->IsKeyHold(MOFKEY_LEFT)) 
	{
		MoveAdd(WAY_LEFT);
	}
	//スティックを離した場合（移動の操作をしていない場合）
	else
	{
		//移動量が0なら処理に入らない
		//移動量が存在する場合、徐々に移動量を0にする
		if (m_Move.x > 0)
		{
			MoveSub(WAY_RIGHT);
		}
		else if (m_Move.x < 0) 
		{
			MoveSub(WAY_LEFT);
		}
		else
		{
			m_bMove = false;
		}
	}

	//Aボタンを押下かつジャンプフラグがたっていない場合ジャンプする
	if (g_pInput->IsKeyHold(MOFKEY_UP) && !m_bJump)
	{
		Jump();
	}
}

//移動
void CPlayer::Move(void)
{
	//移動量に重力をかける
	m_Move.y += GRAVITY;
	m_Pos += m_Move;
}

//加速処理
void CPlayer::MoveAdd(WAY w)
{
	switch(w)
	{
	case WAY_RIGHT:
		m_bReverse = false;
		m_Move.x += m_Spd.x;
		//最大速度を超えないようにする
		if (m_Move.x > PLAYER_MAXSPEED)
		{
			m_Move.x = PLAYER_MAXSPEED;
		}
		break;

	case WAY_LEFT:
		m_bReverse = true;
		m_Move.x -= m_Spd.x;
		//最大速度を超えないようにする
		if (m_Move.x < -PLAYER_MAXSPEED)
		{
			m_Move.x = -PLAYER_MAXSPEED;
		}
		break;
	}
	m_bMove = true;
}

//減速処理
void CPlayer::MoveSub(WAY w)
{
	switch (w)
	{
	case WAY_RIGHT:
		m_Move.x -= m_Spd.x - 0.1f;
		//ゼロ以下にならないようにする
		if (m_Move.x < 0)
		{
			m_Move.x = 0;
		}
		break;
	case WAY_LEFT:
		m_Move.x += m_Spd.x - 0.1f;
		//ゼロ以上にならないようにする
		if (m_Move.x > 0)
		{
			m_Move.x = 0;
		}
		break;
	}
}

//アニメーション処理
void CPlayer::Animation(void)
{
	//移動中なら移動モーションにする
	if(m_bMove && m_pMotion->GetMotionNo() == ANIM_WAIT)
	{
		m_pMotion->ChangeMotion(ANIM_MOVE);
	}
	if(!m_bMove && m_pMotion->GetMotionNo() == ANIM_MOVE)
	{
		m_pMotion->ChangeMotion(ANIM_WAIT);
	}

	//アニメーション加算
	m_pMotion->AddTimer(CUtilities::GetFrameSecond());

	//アニメーション矩形更新
	m_SrcRect = m_pMotion->GetSrcRect();
}

//ジャンプ処理
void CPlayer::Jump(void)
{
	//ジャンプ効果音のテスト処理
	g_pSoundManager->GetResource(FileName[10])->Play();

	//ジャンプフラグを立てる
	m_bJump = true;

	//パワーアップフラグが立っている場合、ジャンプ力上昇
	if (m_bPowUp)
	{
		m_Move.y = PLAYER_HIGHJUMPPOW;
	}
	else
	{
		m_Move.y = PLAYER_JUMPPOW;
	}
}

//当たり判定
void CPlayer::CollisionStage(Vector2 o) {
	m_Pos += o;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化
	if (o.y < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
		if (m_bJump)
		{
			m_bJump = false;
		}
	}
	else if (o.y > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する
	if ((o.x < 0 && m_Move.x > 0) || (o.x > 0 && m_Move.x < 0))
	{
		m_Move.x = 0;
	}
}