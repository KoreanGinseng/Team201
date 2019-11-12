/*****************************************************************
 *	@file			Player.cpp
 *	@brief			プレイヤークラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/

//INCLUDE
#include "Player.h"

CXGamePad xgpad;
//コンストラクタ
CPlayer::CPlayer(void) :
m_pTexture(nullptr),
m_Pos(Vector2(0,0)),
m_Move(Vector2(0,0)),
m_Spd(Vector2(0,0)),
m_bJump(false),
m_bClime(false),
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
	XGAMEPADCREATEINFO xc;
	xgpad.Create(&xc);
	//画像データのセット
	m_pTexture = g_pAnimManager->GetResource(FileName[ANIMATION_PLAYER])->GetTexture();
	//アニメーションデータのセット
	int c = g_pAnimManager->GetResource(FileName[ANIMATION_PLAYER])->GetAnimCount();
	m_Motion.Create(g_pAnimManager->GetResource(FileName[ANIMATION_PLAYER])->GetAnim(), c);
	//座標の初期化
	//m_Pos = Vector2(g_pGraphics->GetTargetWidth() / 2, 0);
	m_Pos = Vector2(960, 768);
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
	//
	m_bClime = false;
	//スキルの範囲を初期化
	m_Skillrang = 0.0f;
	m_Target = 0;
	//
	m_CoolTime = 100.0f;
	//
	m_bTrigger = false;
	//
	m_DamageWait = 0;
}

//更新
void CPlayer::Update(void)
{
	xgpad.RefreshKey();
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

	//スキル
	Skill();

	//アニメーション更新
	Animation();

	//
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

	//
	if (ReNum::GetInstance().GetReNumber() < 0)
	{
		m_HP = 0;

	}
	if (m_HP <= 0)
	{
		ReNum::GetInstance().SubReNumber();
		if (ReNum::GetInstance().GetReNumber() < 0)
		{
			m_HP = 0;
		}
		else
		{
			m_HP = PLAYER_MAXHP;
		}
	}
}

//描画
void CPlayer::Render(Vector2 screenPos)
{
	//
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	CRectangle dr = m_SrcRect;
	//反転フラグが立っているとき描画矩形を反転
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	m_pTexture->Render(screenPos.x, screenPos.y, dr);

	RenderDebug(screenPos);
}

//デバッグ描画
void CPlayer::RenderDebug(Vector2 screenPos)
{
	/*CGraphicsUtilities::RenderString(10, 200, "%.1f", m_Skillrang);
	CGraphicsUtilities::RenderString(10, 240, "%.1f", m_CoolTime);*/
	CGraphicsUtilities::RenderCircle(screenPos.x + m_SrcRect.GetWidth() / 2, screenPos.y + m_SrcRect.GetHeight() / 2, m_Skillrang, MOF_COLOR_RED);
	CGraphicsUtilities::RenderRect(screenPos.x + PLAYER_RECTDIS, screenPos.y + PLAYER_RECTDIS,
		screenPos.x + m_SrcRect.GetWidth() - PLAYER_RECTDIS, screenPos.y + m_SrcRect.GetHeight(), MOF_COLOR_RED);
	//CGraphicsUtilities::RenderString(0, 130, "%.1f,%.1f", GetRect().Left, GetRect().Top);
}

//解放
void CPlayer::Release(void)
{
	m_Motion.Release();
	m_SkillTarget.clear();
	m_pTexture = nullptr;
}

//パッドオペレーション
void CPlayer::PadOparation(void)
{
	//スティックを右か左に倒した場合、倒した方向に移動
	if (xgpad.GetStickHorizontal() > 0.8f)
	{
		MoveAdd(WAY_RIGHT);
	}
	else if (xgpad.GetStickHorizontal() < -0.8f)
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

	//LTボタンを押した場合、スキルが発動
	if (xgpad.IsKeyHold(XINPUT_L_TRIGGER)/* && m_CoolTime > 0.0f*/)
	{
		m_bTrigger = true;
		if (!m_SkillTarget.empty())
		{
			//LBまたはRBでターゲットを変更
			if (g_pGamePad->IsKeyPush(GAMEKEY_LB))
			{
				if (--m_Target < 0)
				{
					m_Target = m_SkillTarget.size() - 1;
				}
			}
			else if (g_pGamePad->IsKeyPush(GAMEKEY_RB))
			{
				if (++m_Target >= m_SkillTarget.size())
				{
					m_Target = 0;
				}
			}

			//スキルの番号
			int skillNo = -1;

			//戻る
			if (xgpad.IsKeyPush(GAMEKEY_X)) {

				skillNo = GAMEKEY_X;

			}//止める
			else if (xgpad.IsKeyPush(GAMEKEY_Y)) {

				skillNo = GAMEKEY_Y;

			}//飛ばす
			else if (xgpad.IsKeyPush(GAMEKEY_B)) {

				skillNo = GAMEKEY_B;

			}



			//X||Y||Bのいずれかを押した場合
			if (skillNo!=-1)
			{
			
				if (!m_SkillTarget.empty())
				{
					m_bTrigger = false;
					m_SkillTarget[m_Target]->SetSkill();
					//スキル番号のスキルをセットする
					switch (skillNo)
					{
					case GAMEKEY_X:
						m_SkillTarget[m_Target]->SetBack();
						break;
					case GAMEKEY_Y:
						m_SkillTarget[m_Target]->SetStop();
						break;
					case GAMEKEY_B:
						m_SkillTarget[m_Target]->SetTrip();
						break;
					}
					for (int i = 0; i < m_SkillTarget.size(); i++)
					{
						m_SkillTarget[i]->SetTarget(false);
					}
				}
			}
		}
	}
	else if (g_pGamePad->GetPadState()->lZ < 1)
	{
		m_bTrigger = false;
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

	//スペースキーを押した場合、スキルが発動
	if (g_pInput->IsKeyHold(MOFKEY_SPACE) /*&& m_CoolTime > 0.0f*/)
	{
		m_bTrigger = true;
		//Listが空の場合、処理をしない
		if (!m_SkillTarget.empty())
		{
			//ZまたはXでターゲットを変更
			if (g_pInput->IsKeyPush(MOFKEY_Z))
			{
				if (--m_Target < 0)
				{
					m_Target = m_SkillTarget.size() - 1;
				}
			}
			else if (g_pInput->IsKeyPush(MOFKEY_X))
			{
				if (++m_Target >= m_SkillTarget.size())
				{
					m_Target = 0;
				}
			}
			//Cを押したとき選択中の敵にスキルを使用
			if (g_pInput->IsKeyPush(MOFKEY_C))
			{
				m_bTrigger = false;
				m_SkillTarget[m_Target]->SetSkill();
				for (int i = 0; i < m_SkillTarget.size(); i++)
				{
					m_SkillTarget[i]->SetTarget(false);
				}
			}//シフトキーと保存
		}
	}
	else if (g_pInput->IsKeyPull(MOFKEY_SPACE))
	{
		m_bTrigger = false;
	}
}

//移動
void CPlayer::Move(void)
{
	//移動量に重力をかける
	if (!m_bClime)
	{
		m_Move.y += GRAVITY;
	}
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
	if(m_bMove && m_Motion.GetMotionNo() == ANIM_WAIT)
	{
		m_Motion.ChangeMotion(ANIM_MOVE);
	}
	if(!m_bMove && m_Motion.GetMotionNo() == ANIM_MOVE)
	{
		m_Motion.ChangeMotion(ANIM_WAIT);
	}

	//アニメーション加算
	m_Motion.AddTimer(CUtilities::GetFrameSecond());

	//アニメーション矩形更新
	m_SrcRect = m_Motion.GetSrcRect();
}

//ジャンプ処理
void CPlayer::Jump(void)
{
	//ジャンプ効果音のテスト処理
	//g_pSoundManager->GetResource(FileName[SOUND_JUMP])->Play();

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
void CPlayer::CollisionStage(Vector2 o)
{
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

void CPlayer::Skill()
{
	//スキルの円に座標や半径を代入
	m_SkillCircle.x = m_Pos.x + m_SrcRect.GetWidth() / 2;
	m_SkillCircle.y = m_Pos.y + m_SrcRect.GetHeight() / 2;
	m_SkillCircle.r = m_Skillrang;

	//スキルが発動している場合ターゲットの範囲を広げる
	if (m_bTrigger)
	{
		m_Skillrang += 10;
		/*m_CoolTime -= 0.1f;*/
		if (m_Skillrang >= PLAYER_MAXSKILLRANGE)
		{
			m_Skillrang = PLAYER_MAXSKILLRANGE;
		}
	}
	else 
	{
		//離したまたは押してない状態で
		//ターゲット範囲が0より大きい場合
		if (m_Skillrang > 0.0f)
		{
			//スキル範囲を0にしてターゲットを先頭に戻す(初期化する)
			m_Skillrang = 0.0f;
			m_Target = 0;
			//ベクトルに要素が入っている場合
			if (!m_SkillTarget.empty()) 
			{
				//全てのターゲットフラグを下ろし、要素を全てクリアする
				for (int i = 0; i < m_SkillTarget.size(); i++)
				{
					m_SkillTarget[i]->SetTarget(false);
				}
				m_SkillTarget.clear();
			}
		}
	}
}


void CPlayer::SkillColision(CEnemy* pene, int eneCount, CObject* pobj, int objCount) {

	std::list<CSubstance*> element;
	//ベクトルに入っていたSubstanceのターゲットの初期化
	for (int i = 0; i < m_SkillTarget.size(); i++)
	{
		m_SkillTarget[i]->SetTarget(false);
	}
	//ベクトルの要素をクリア
	m_SkillTarget.clear();


	for (int i = 0; i < eneCount; i++) 
	{
		if (!pene[i].GetShow())
		{
			continue;
		}

		//表示されていてスキルの円に敵が当たっている場合、その敵の要素を入れる
		if (CollisionRectCircle(pene[i].GetRect(), m_SkillCircle))
		{
			element.push_back(&pene[i]);
		}
	}

	for (int i = 0; i < objCount; i++)
	{
		if (!pobj[i].GetShow())
		{
			continue;
		}

		//表示されていてスキルの円に敵が当たっている場合、その敵の要素を入れる
		if (CollisionRectCircle(pobj[i].GetRect(), m_SkillCircle))
		{
			element.push_back(&pobj[i]);
		}
	}

	//Listが空の場合、処理をしない
	if (element.empty())
	{
		return;
	}

	//プレイヤーの位置
	float stx = m_Pos.x + m_SrcRect.GetWidth()*0.5f;
	float sty = m_Pos.y + m_SrcRect.GetHeight();

	//一つずつv と　v++を比較してソートする
	element.sort(
		[&](CSubstance*& v1, CSubstance*& v2)
		{
			CRectangle rec1 = v1->GetRect();
			CRectangle rec2 = v2->GetRect();

			Vector2 cv1 = rec1.GetCenter();
			Vector2 cv2 = rec2.GetCenter();

			float dx1 = cv1.x - stx;
			float dy1 = cv1.y - sty;
			float d1 = (dx1*dx1 + dy1 * dy1);

			float dx2 = cv2.x - stx;
			float dy2 = cv2.y - sty;
			float d2 = (dx2*dx2 + dy2 * dy2);
			if (d1 > d2) {
				return false;
			}
			return true;
		}
	);

	//ソートされた敵かオブジェクトをベクトルに入れる
	for (auto itr = element.cbegin(); itr != element.cend(); ++itr) 
	{
		m_SkillTarget.push_back(*itr);
	}

	
	if (m_Target > m_SkillTarget.size()-1) {

		m_Target = m_SkillTarget.size() - 1;

	}
	
	
	

	//ターゲット中か敵に伝える
	for (int i = 0; i < m_SkillTarget.size(); i++)
	{
		if (i == m_Target)
		{
			m_SkillTarget[i]->SetTarget(true);
		}
		else
		{
			m_SkillTarget[i]->SetTarget(false);
		}
	}
}

bool CPlayer::Dmg(CEnemy& ene)
{
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();

	if (m_DamageWait > 0 || ene.GetDamageWait() > 0)
	{
		return false;
	}
	m_DamageWait = 60;
	if (m_HP > 0)
	{
		m_HP--;

		if (prec.Left < erec.Left)
		{
			m_Move.x = -5.0f;
			m_bReverse = false;
		}
		else
		{
			m_Move.x = 5.0f;
			m_bReverse = true;
		}
		//m_Motion.ChangeMotion(MOTION_DAMAGE);
	}
	return true;
}