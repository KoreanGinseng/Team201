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
m_bClime(false),
m_HP(0)
{
}

//デストラクタ
CPlayer::~CPlayer(void)
{
}

//初期化
void CPlayer::Initialize(void)
{
	//
	m_pTexture = g_pTextureManager->GetResource(FileName[TEXTURE_PLAYER]);
	CreateMove(0);
	m_MvCntrl.Initialize();
	m_Anim.Initialize();
	CreateAnim(FileName[ANIMATION_PLAYER]);
	m_MvCntrl.SetSpd(PLAYER_SPEED, PLAYER_JUMPPOW);
	//
	m_bDead = false;
	//
	m_bReverse = false;
	//座標の初期化
	m_Pos = Vector2(960, 768);
	m_Pos = Vector2(9600, 768);
	//m_Pos = Vector2(4000, 192);
	//HPの初期化
	m_HP = PLAYER_MAXHP;
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
	//MOVE
	m_MvCntrl.Update();
	m_Pos += m_MvCntrl.GetMove();

	//スキル
	Skill();

	//アニメーション更新
	Animation();

	//
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

	if (m_HP <= 0)
	{
		m_bDead = true;
	}

	m_bReverse = static_cast<CMovePlayer*>(m_MvCntrl.GetInstance())->GetReverse();
}

//描画
void CPlayer::Render(Vector2 screenPos)
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

	RenderDebug(screenPos);
}

//デバッグ描画
void CPlayer::RenderDebug(Vector2 screenPos)
{
	CGraphicsUtilities::RenderCircle(screenPos.x + GetSrcRect().GetWidth() / 2, screenPos.y + GetSrcRect().GetHeight() / 2, m_Skillrang, MOF_COLOR_RED);
	CGraphicsUtilities::RenderRect(screenPos.x + PLAYER_RECTDIS, screenPos.y + PLAYER_RECTDIS,
		screenPos.x + GetSrcRect().GetWidth() - PLAYER_RECTDIS, screenPos.y + GetSrcRect().GetHeight(), MOF_COLOR_RED);
}

//解放
void CPlayer::Release(void)
{
	CCharacter::Release();
	m_SkillTarget.clear();
	m_pTexture = nullptr;
}

//アニメーション処理
void CPlayer::Animation(void)
{
	if (m_MvCntrl.GetMotionNo() != m_Anim.GetMotionNo())
	{
		m_Anim.ChangeAnim(m_MvCntrl.GetMotionNo());
	}

	m_Anim.Update();
}

//当たり判定
void CPlayer::CollisionStage(const Vector2& over)
{
	m_Pos += over;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化
	if (over.y < 0 && m_MvCntrl.GetMove().y > 0)
	{
		m_MvCntrl.SetMove(m_MvCntrl.GetMove().x, 0);
		static_cast<CMovePlayer*>(m_MvCntrl.GetInstance())->ResetJump();
	}
	else if (over.y > 0 && m_MvCntrl.GetMove().y < 0)
	{
		m_MvCntrl.SetMove(m_MvCntrl.GetMove().x, 0);
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する
	if ((over.x < 0 && m_MvCntrl.GetMove().x > 0) || (over.x > 0 && m_MvCntrl.GetMove().x < 0))
	{
		m_MvCntrl.SetMove(0, m_MvCntrl.GetMove().y);
	}
}

void CPlayer::Skill()
{
	//LTボタンを押した場合、スキルが発動
	if (g_pGamePad->IsKeyHold(XINPUT_L_TRIGGER) || g_pInput->IsKeyHold(MOFKEY_SPACE))
	{
		m_bTrigger = true;
		if (!m_SkillTarget.empty())
		{
			//LBまたはRBでターゲットを変更
			if (g_pGamePad->IsKeyPush(XINPUT_L_BTN) || g_pInput->IsKeyPush(MOFKEY_Z))
			{
				if (--m_Target < 0)
				{
					m_Target = m_SkillTarget.size() - 1;
				}
			}
			else if (g_pGamePad->IsKeyPush(XINPUT_R_BTN) || g_pInput->IsKeyPush(MOFKEY_X))
			{
				if (++m_Target >= m_SkillTarget.size())
				{
					m_Target = 0;
				}
			}

			//スキルの番号
			int skillNo = -1;

			//戻る
			if (g_pGamePad->IsKeyPush(XINPUT_X) || g_pInput->IsKeyPush(MOFKEY_A))
			{
				skillNo = XINPUT_X;
			}
			//止める
			else if (g_pGamePad->IsKeyPush(XINPUT_Y) || g_pInput->IsKeyPush(MOFKEY_S))
			{
				skillNo = XINPUT_Y;
			}
			//飛ばす
			else if (g_pGamePad->IsKeyPush(XINPUT_B) || g_pInput->IsKeyPush(MOFKEY_D))
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
					m_SkillTarget[m_Target]->SetSkill();

					//スキル番号のスキルをセットする
					switch (skillNo)
					{
					case XINPUT_X:
						m_SkillTarget[m_Target]->SetBack();
						break;
					case XINPUT_Y:
						m_SkillTarget[m_Target]->SetStop();
						break;
					case XINPUT_B:
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
	else if (g_pGamePad->IsKeyPull(XINPUT_L_TRIGGER) || g_pInput->IsKeyPull(MOFKEY_SPACE))
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
		if (!(*peneArray)[i]->IsShow())
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
		if (!(*pobjArray)[i]->IsShow())
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
		if (!(*pItemArray)[i]->IsShow())
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
			m_MvCntrl.SetMove(-5.0f, m_MvCntrl.GetMove().y);
			m_bReverse = false;
		}
		else
		{
			m_MvCntrl.SetMove(5.0f, m_MvCntrl.GetMove().y);
			m_bReverse = true;
		}
		//m_Motion.ChangeMotion(MOTION_DAMAGE);
	}
	return true;
}