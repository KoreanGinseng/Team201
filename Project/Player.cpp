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
CCharacter(),
m_bKey(true),
m_bJump(false),
m_SkillTarget(),
m_bTrigger(false),
m_bClime(false),
m_Target(0),
m_Skillrang(0),
m_SkillCircle()
{
	CCordinate::SetPlayerPos(&m_Pos);
}

//デストラクタ
CPlayer::~CPlayer(void)
{
	Release();
}

//初期化
void CPlayer::Initialize(void)
{
	//画像のセット
	m_pTexture = g_pTextureManager->GetResource(FileName[TEXTURE_PLAYER]);
	SpriteAnimationCreate* pAnim;
	pAnim = g_pAnimManager->GetResource(FileName[ANIMATION_PLAYER])->GetAnim();
	m_Motion.Create(pAnim, ANIM_COUNT);
	m_SrcRectArray.Add(GetSrcRect());
	m_bDead = false;
	m_bReverse = false;
	//座標の初期化
	m_Pos = Vector2(9600, 768);
	m_Pos = Vector2(4000, 192);
	m_Pos = Vector2(960, 768);
	m_Pos = Vector2(200, 768);
	//HPの初期化
	m_HP = PLAYER_MAXHP;
	m_bClime = false;
	//スキルの範囲を初期化
	m_Skillrang = 0.0f;
	m_Target = 0;
	m_bTrigger = false;
	m_DamageWait = 0;
	if (g_pInput->GetGamePadCount())
	{
		m_bKey = false;
	}
}

//更新
void CPlayer::Update(void)
{
	//スキル
	Skill();

	//MOVE
	Move();
	m_Pos += m_Move;

	//アニメーション更新
	Animation();

	//
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

	if (GetRect().Left < CCordinate::GetStageRect().Left)
	{
		m_Pos.x = CCordinate::GetStageRect().Left;
	}
	else if (GetRect().Right > CCordinate::GetStageRect().Right)
	{
		m_Pos.x = CCordinate::GetStageRect().Right - GetRect().GetWidth();
	}
	if (GetRect().Top > CCordinate::GetStageRect().Bottom)
	{
		m_DamageWait = 60;
		m_HP--;
		m_Pos = CCordinate::GetSavePoint();
	}

	if (m_HP <= 0)
	{
		m_bDead = true;
	}
}

//描画
void CPlayer::Render(const Vector2& screenPos)
{
	//
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	CRectangle dr = GetSrcRect();
	//反転フラグが立っているとき描画矩形を反転
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	m_pTexture->Render(screenPos.x, screenPos.y, dr);
#ifdef _DEBUG
	Vector2 scroll = CCamera2D::GetSScroll();
	CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
	CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
	for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
	{
		CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
			screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
	}
#endif // _DEBUG
}

//解放
void CPlayer::Release(void)
{
	CCharacter::Release();
	m_SkillTarget.clear();
	m_pTexture = nullptr;
}

void CPlayer::Move(void)
{
	m_KeyConfig.moveRight   = m_bKey ? g_pInput->IsKeyHold(MOFKEY_RIGHT)  : (g_pGamePad->GetStickHorizontal() > 0.8f);
	m_KeyConfig.moveLeft    = m_bKey ? g_pInput->IsKeyHold(MOFKEY_LEFT)   : (g_pGamePad->GetStickHorizontal() < -0.8f);
	m_KeyConfig.jump        = m_bKey ? g_pInput->IsKeyHold(MOFKEY_UP)     : (g_pGamePad->IsKeyPush(XINPUT_A));
	m_KeyConfig.clime       = m_bKey ? g_pInput->IsKeyHold(MOFKEY_UP)     : (g_pGamePad->GetStickVertical() > 0.8f);
	m_KeyConfig.fall        = m_bKey ? g_pInput->IsKeyHold(MOFKEY_DOWN)   : (g_pGamePad->GetStickVertical() < -0.8f);

	if (m_KeyConfig.skillStance && !m_bMove && !m_bJump && !m_bClime)
	{
		return;
	}

	//右スティックを倒した場合、倒した方向に移動
	if (m_KeyConfig.moveRight)
	{
		m_Move.x += PLAYER_SPEED;
		m_bMove = true;
		m_bReverse = false;
		if (m_Move.x > PLAYER_MAXSPEED)
		{
			m_Move.x = PLAYER_MAXSPEED;
		}
	}
	else if (m_KeyConfig.moveLeft)
	{
		m_Move.x -= PLAYER_SPEED;
		m_bMove = true;
		m_bReverse = true;
		if (m_Move.x < -PLAYER_MAXSPEED)
		{
			m_Move.x = -PLAYER_MAXSPEED;
		}
	}
	//スティックを離した場合（移動の操作をしていない場合）
	else
	{
		//移動量が0なら処理に入らない
		//移動量が存在する場合、徐々に移動量を0にする
		if (m_Move.x < 0)
		{
			m_Move.x += (PLAYER_SPEED - 0.1f);
			if (m_Move.x > 0)
			{
				m_Move.x = 0;
			}
		}
		else if (m_Move.x > 0)
		{
			m_Move.x -= (PLAYER_SPEED - 0.1f);
			if (m_Move.x < 0)
			{
				m_Move.x = 0;
			}
		}
		else
		{
			m_bMove = false;
		}
	}

	//Aボタンを押下かつジャンプフラグがたっていない場合ジャンプする
	if (m_KeyConfig.jump && !m_bJump && !m_bClime)
	{
		m_bJump = true;
		m_Move.y = PLAYER_JUMPPOW;
	}
	else if (m_KeyConfig.clime && m_bClime)
	{
		m_Move.y = -3.0f;
	}
	else if (m_KeyConfig.fall && m_bClime)
	{
		m_Move.y = 3.0f;
	}
	else if (m_bClime)
	{
		m_Move.y = 0;
	}

	if (m_bClime)
	{
		m_Move.y -= GRAVITY;
	}
	m_Move.y += GRAVITY;
	if (m_Move.y > 20.0f)
	{
		m_Move.y = 20.0f;
	}
}

//アニメーション処理
void CPlayer::Animation(void)
{
	if (m_bJump && m_Motion.GetMotionNo() != ANIM_JUMPUP && m_Move.y < 0)
	{
		m_Motion.ChangeMotion(ANIM_JUMPUP);
	}
	else if (m_bJump && m_Motion.GetMotionNo() != ANIM_JUMPDOWN && m_Move.y >= 0)
	{
		m_Motion.ChangeMotion(ANIM_JUMPDOWN);
	}
	else if (m_bMove && m_Motion.GetMotionNo() != ANIM_MOVE && !m_bJump)
	{
		m_Motion.ChangeMotion(ANIM_MOVE);
	}
	else if (m_bTrigger && m_Motion.GetMotionNo() != ANIM_SKILLSTANCE && !m_bJump && !m_bMove)
	{
		m_Motion.ChangeMotion(ANIM_SKILLSTANCE);
	}
	else if (m_Motion.GetMotionNo() != ANIM_WAIT && !m_bJump && !m_bMove && !m_bTrigger)
	{
		m_Motion.ChangeMotion(ANIM_WAIT);
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
}

//当たり判定
void CPlayer::CollisionStage(const Vector2& over)
{
	m_Pos += over;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化
	if (over.y < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
		m_bJump = false;
	}
	else if (over.y > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する
	if ((over.x < 0 && m_Move.x > 0) || (over.x > 0 && m_Move.x < 0))
	{
		m_Move.x = 0;
	}
}

CRectangle CPlayer::GetRect(void)
{
	CRectangle r = CCharacter::GetRect();
	r.Expansion(-PLAYER_RECTDIS, 0);
	r.Top += 20;
	r.Bottom -= 30;
	return r;
}

void CPlayer::Skill(void)
{
	m_KeyConfig.skillStance = m_bKey ? g_pInput->IsKeyHold(MOFKEY_SPACE) : g_pGamePad->IsKeyHold(XINPUT_L_TRIGGER);
	m_KeyConfig.selectNext  = m_bKey ? g_pInput->IsKeyPush(MOFKEY_X)     : g_pGamePad->IsKeyPush(XINPUT_R_BTN);
	m_KeyConfig.selectBack  = m_bKey ? g_pInput->IsKeyPush(MOFKEY_Z)     : g_pGamePad->IsKeyPush(XINPUT_L_BTN);
	m_KeyConfig.skillBack   = m_bKey ? g_pInput->IsKeyPush(MOFKEY_A)     : (g_pGamePad->IsKeyPush(XINPUT_X));
	m_KeyConfig.skillStop   = m_bKey ? g_pInput->IsKeyPush(MOFKEY_S)     : (g_pGamePad->IsKeyPush(XINPUT_Y));
	m_KeyConfig.skillSkip   = m_bKey ? g_pInput->IsKeyPush(MOFKEY_D)     : (g_pGamePad->IsKeyPush(XINPUT_B));
	m_KeyConfig.skillStancePull = m_bKey ? g_pInput->IsKeyPull(MOFKEY_SPACE) : g_pGamePad->IsKeyPull(XINPUT_L_TRIGGER);
	//LTボタンを押した場合、スキルが発動
	if (m_KeyConfig.skillStance && !m_bMove && !m_bJump && !m_bClime)
	{
		m_bTrigger = true;
		if (!m_SkillTarget.empty())
		{
			//LBまたはRBでターゲットを変更
			if (m_KeyConfig.selectBack)
			{
				if (--m_Target < 0)
				{
					m_Target = m_SkillTarget.size() - 1;
				}
			}
			else if (m_KeyConfig.selectNext)
			{
				if (++m_Target >= m_SkillTarget.size())
				{
					m_Target = 0;
				}
			}

			//スキルの番号
			int skillNo = -1;

			//戻る
			if (m_KeyConfig.skillBack)
			{
				skillNo = XINPUT_X;
			}
			//止める
			else if (m_KeyConfig.skillStop)
			{
				skillNo = XINPUT_Y;
			}
			//飛ばす
			else if (m_KeyConfig.skillSkip)
			{
				skillNo = XINPUT_B;
			}

			//X||Y||Bのいずれかを押した場合
			if (skillNo != -1)
			{
				g_pScore->AddSkillCount();
				if (!m_SkillTarget.empty())
				{
					m_bTrigger = false;

					//スキル番号のスキルをセットする
					switch (skillNo)
					{
					case XINPUT_X:
						m_SkillTarget[m_Target]->Back();
						break;
					case XINPUT_Y:
						m_SkillTarget[m_Target]->Stop();
						break;
					case XINPUT_B:
						m_SkillTarget[m_Target]->Trip();
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
	else if (m_KeyConfig.skillStancePull)
	{
		m_bTrigger = false;
	}

	//スキルの円に座標や半径を代入
	m_SkillCircle.x = m_Pos.x + GetSrcRect().GetWidth() / 2;
	m_SkillCircle.y = m_Pos.y + GetSrcRect().GetHeight() / 2;
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


void CPlayer::TargetSelect(CDynamicArray<CEnemy*>* peneArray, CDynamicArray<CTargetObj*>* pobjArray, CDynamicArray<CItem*>* pItemArray) {

	std::list<CSubstance*> element;
	//ベクトルに入っていたSubstanceのターゲットの初期化
	for (int i = 0; i < m_SkillTarget.size(); i++)
	{
		m_SkillTarget[i]->SetTarget(false);
	}
	//ベクトルの要素をクリア
	m_SkillTarget.clear();


	for (int i = 0; i < peneArray->GetArrayCount(); i++)
	{
		if (!(*peneArray)[i]->IsShow() || !(*peneArray)[i]->IsSelectTarget())
		{
			continue;
		}

		//表示されていてスキルの円に敵が当たっている場合、その敵の要素を入れる
		if (CollisionRectCircle((*peneArray)[i]->GetRect(), m_SkillCircle))
		{
			element.push_back(static_cast<CSubstance*>((*peneArray)[i]));
		}
	}

	for (int i = 0; i < pobjArray->GetArrayCount(); i++)
	{
		if (!(*pobjArray)[i]->IsShow() || !(*pobjArray)[i]->IsSelectTarget())
		{
			continue;
		}

		//表示されていてスキルの円に敵が当たっている場合、その敵の要素を入れる
		if (CollisionRectCircle((*pobjArray)[i]->GetRect(), m_SkillCircle))
		{
			element.push_back(static_cast<CSubstance*>((*pobjArray)[i]));
		}
	}

	for (int i = 0; i < pItemArray->GetArrayCount(); i++)
	{
		if (!(*pItemArray)[i]->IsShow() || !(*pItemArray)[i]->IsSelectTarget())
		{
			continue;
		}

		//表示されていてスキルの円に敵が当たっている場合、その敵の要素を入れる
		if (CollisionRectCircle((*pItemArray)[i]->GetRect(), m_SkillCircle))
		{
			element.push_back(static_cast<CSubstance*>((*pItemArray)[i]));
		}
	}

	//Listが空の場合、処理をしない
	if (element.empty())
	{
		return;
	}

	//プレイヤーの位置
	float stx = m_Pos.x + GetSrcRect().GetWidth() * 0.5f;
	float sty = m_Pos.y + GetSrcRect().GetHeight();

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

	
	if (m_Target > m_SkillTarget.size()-1)
	{
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
		g_pScore->AddDamageCount();
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