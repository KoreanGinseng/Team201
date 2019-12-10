/**
 * @file Atack_TESTBOS3.cpp
 * @brief テストボス3の攻撃
 * @author 大西永遠
 * @date 更新日（12/3）
 */

#include	"Atack_TESTBOS3.h"


CAtack_TESTBOS3::CAtack_TESTBOS3() :
	CEnemyAtack() {

	//形態
	m_Form = 1;

}
CAtack_TESTBOS3::~CAtack_TESTBOS3() {

}

void CAtack_TESTBOS3::PtnInitialize() {

	for (int i = 0; i < m_Ptn[m_Form];)  {

		m_AttackPtn.Add(rand()%m_Ptn[m_Form]);

		bool test = false;

		for (int j = 0; j < m_AttackPtn.GetArrayCount()-1; j++) {

			if (m_AttackPtn[j] == m_AttackPtn[i]) {

				test = true;

			}
		}

		if (test) {

			m_AttackPtn.DeleteLast();
			continue;

		}

		i++;
	}

}

void CAtack_TESTBOS3::Initialize() {
	m_bShow = false;
	m_fAtackTimer = 0;
	m_fCooltime = 0;

	//攻撃パターンの初期化
	PtnInitialize();

	//分身剣
	for (int i = 0; i < CloningCount; i++) {
		m_ClonArry[i] = new CCloningSword();
		m_ClonArry[i]->Initialize();

	}

	//瞬間移動する剣
	m_ShotArry = new CTeleportationSword();
	m_ShotArry->Initialize();

	//分身する敵
	for (m_EneCount = 0; m_EneCount < CloningCount;m_EneCount++) {
		m_KURIBO.ClonInitialize(m_EneCount);
	}
	m_EneCount = 0;

	m_ScaleMagnification = 0;
	//m_TleTime = TLeTime;

	m_Counting = 1;
}

void CAtack_TESTBOS3::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {
	//X座標の攻撃範囲
	if (EnemyPosX - BosAtackRange < PlayerPosX&&EnemyPosX + BosAtackRange > PlayerPosX) {
		if (m_fAtackTimer >= 0 && m_fCooltime <= 0) {
			m_fAtackTimer -= 1 * CUtilities::GetFrameSecond();
			if (m_fAtackTimer <= 0) {

				m_fAtackTimer = 0;
				m_fCooltime = CoolTime;
				//m_bShow = false;
			}
		}
		if (m_fCooltime >= 0 && m_fAtackTimer <= 0) {
			m_fCooltime -= 1 * CUtilities::GetFrameSecond();
			if (m_fCooltime <= 0) {
				m_fCooltime = 0;
				
			}
		}

	//	m_bShow = true;

	}


	//分身剣
	/*for (int i = 0; i < CloningCount; i++) {
		m_ClonArry[i]->Update();
	}*/
	


	

	m_TestInfo = {Vector2(EnemyPosX,EnemyPosY),Vector2(PlayerPosX,PlayerPosY)};


	BossBehavior();


	//瞬間移動
	m_ShotArry->Update();
	
	
	if (g_pInput->IsKeyPush(MOFKEY_G) && m_Form != 0) {

		m_Form--;
		PtnInitialize();

	}
	else if (g_pInput->IsKeyPush(MOFKEY_H) && m_Form < 4) {

		m_Form++;
		PtnInitialize();
	}

	

	

	


	


	
}

void CAtack_TESTBOS3::Render() {

	for(int i = 0;i<m_AttackPtn.GetArrayCount();i++)
	CGraphicsUtilities::RenderString(0, 200*i+50, "%d", m_AttackPtn[i]);

	//分身剣
	/*for (int i = 0; i < CloningCount; i++) {
		m_ClonArry[i]->Render();

	}*/
	
	//右手
	m_Hand.Render(m_fAtackPosX,m_fAtackPosY);

	////右手衝撃波
	m_AtackHand.Render();

	//瞬間移動
	m_ShotArry->Render();

	
	//分身する敵
	/*m_KURIBO.ClonRender(m_EneCount);*/

}
void CAtack_TESTBOS3::Release() {
	//瞬間移動
	for (int i = 0; i < CloningCount; i++) {
		if (m_ShotArry) {
			m_ShotArry->Release();
			delete[] m_ShotArry;
			m_ShotArry = NULL;
		}
	}
	
	//分身剣
	for (int i = 0; i < CloningCount; i++) {
		if (m_ClonArry) {
			m_ClonArry[i]->Release();
			delete[] m_ClonArry[i];
			m_ClonArry[i] = NULL;
		}
	}
}

void CAtack_TESTBOS3::TLSwordUpdate(float EnemyPosX, float EnemyPosY, float PlayerPosX, float PlayerPosY) {

}

void CAtack_TESTBOS3::ClonSwordUpdate(float EnemyPosX, float EnemyPosY, float PlayerPosX, float PlayerPosY) {

}

void CAtack_TESTBOS3::BossBehavior() {


	switch (m_Form)
	{
	case 0:
		Form1Ptn();
		break;
	case 1:
		Form2Ptn();
		break;
	case 2:
		Form3Ptn();
		break;
	case 3:
		Form4Ptn();
		break;
	}

	if (!m_AttackPtn.GetArrayCount()) {

		PtnInitialize();

	}

}

void CAtack_TESTBOS3::Form1Ptn() {

	bool end = false;
	switch (m_AttackPtn[0])
	{
	case 0:
		end = CrushHand();
		break;
	case 1:
		end = AcidBless();
		break;

	}

	if (end) {

		m_AttackPtn.DeleteFast();
	}
}

void CAtack_TESTBOS3::Form2Ptn() {

	bool end = false;

	switch (m_AttackPtn[0])
	{
	case 0:
		end = CrushHand();
		break;
	case 1:
		end = ShadowSwordAttack();
		break;
	case 2:
		end = CrushWave();
		break;

	}

	if (end) {

		m_AttackPtn.DeleteFast();
	}

}

void CAtack_TESTBOS3::Form3Ptn() {

	bool end = false;
	switch (m_AttackPtn[0])
	{
	case 0:
		CrushHand();
		break;
	case 1:
		end = TeleportSword();
		break;
	case 2:
		end = TeleportEnemy();
		break;

	}

	if (end) {

		m_AttackPtn.DeleteFast();
	}
}

void CAtack_TESTBOS3::Form4Ptn() {

	bool end = false;
	switch (m_AttackPtn[0])
	{
	case 0:
		end = CrushHand();
		break;
	case 1:
		end = AcidBless();
		break;
	case 2:
		end = ShadowSwordAttack();
		break;
	case 3:
		end = CrushWave();
		break;
	case 4:
		end = TeleportEnemy();
		break;
		

	}
	if (end) {

		m_AttackPtn.DeleteFast();
	}

}

bool CAtack_TESTBOS3::CrushHand()
{

	//右手
	if (!m_Hand.GetMoveFlag()) {
		m_Hand.Initialize();
		m_AtackHand.Initialize();
		m_Hand.Start(m_TestInfo.playerPos.x);
	}
	m_Hand.Update(m_TestInfo.playerPos);
	m_Hand.CollisionStage();

	return false;

}

bool CAtack_TESTBOS3::AcidBless(void)
{
	return false;
}

bool CAtack_TESTBOS3::ShadowSwordAttack(void)
{

	m_fAtackTimer = AtackTimer;
	float rd = m_ClonArry[2]->GetRadian(m_TestInfo.enemyPos.x, m_TestInfo.enemyPos.y, m_TestInfo.playerPos.x, m_TestInfo.playerPos.y);
	float ddx = m_ClonArry[2]->Getddx(m_TestInfo.enemyPos.x, m_TestInfo.enemyPos.y, m_TestInfo.playerPos.x, m_TestInfo.playerPos.y);
	float ddy = m_ClonArry[2]->Getddy(m_TestInfo.enemyPos.x, m_TestInfo.enemyPos.y, m_TestInfo.playerPos.x, m_TestInfo.playerPos.y);

	int rnd = rand() % 5;

	for (int i = 0; i < CloningCount; i++) {

		m_ClonArry[i]->Initialize();
		if (i == 2) {
			m_ClonArry[i]->Fire(m_TestInfo.enemyPos.x, m_TestInfo.enemyPos.y, BulletSpeed, BulletSpeed, m_TestInfo.playerPos.x, m_TestInfo.playerPos.y);
		}
		else
		{
			m_ClonArry[i]->CloningFire(m_TestInfo.enemyPos.x + i * CloningDistance - CloningDistance * 2, m_TestInfo.enemyPos.y, BulletSpeed, BulletSpeed, 
				m_TestInfo.playerPos.x, m_TestInfo.playerPos.y, rd, ddx, ddy);
		}



	}
	m_ClonArry[rnd]->SetFrag(true);


	m_fAtackPosX = m_TestInfo.enemyPos.x;
	m_fAtackPosY = m_TestInfo.enemyPos.y;

	return m_ClonArry[rnd]->GetShow();

}

bool CAtack_TESTBOS3::CrushWave(void)
{

	//右手最終形態
	if (!m_Hand.GetMoveFlag()) {
		m_Hand.Initialize();
		m_Hand.SetLimit(true);
		m_Hand.Start(m_TestInfo.enemyPos.x);
	}
	if (m_Hand.GetFire()) {
		m_AtackHand.Initialize(m_Hand.GetXpos(),m_Hand.GetYpos());
		m_AtackHand.SetLimit(true);
		m_Hand.SetFire(false);
	}
	m_Hand.Update(m_TestInfo.playerPos);
	m_AtackHand.Update();
	m_Hand.CollisionStage();

	return false;

}

bool CAtack_TESTBOS3::TeleportSword(void)
{

	//瞬間移動する剣
	m_fAtackTimer = AtackTimer;
	float rd = m_ShotArry->GetRadian(m_TestInfo.enemyPos.x, m_TestInfo.enemyPos.y, m_TestInfo.playerPos.x, m_TestInfo.playerPos.y);
	float ddx = m_ShotArry->Getddx(m_TestInfo.enemyPos.x, m_TestInfo.enemyPos.y, m_TestInfo.playerPos.x, m_TestInfo.playerPos.y);
	float ddy = m_ShotArry->Getddy(m_TestInfo.enemyPos.x, m_TestInfo.enemyPos.y, m_TestInfo.playerPos.x, m_TestInfo.playerPos.y);

	if (m_ShotArry->GetShow()) {
		return false;
	}
	m_ShotArry->Initialize();

	m_ShotArry->Fire(m_TestInfo.enemyPos.x, m_TestInfo.enemyPos.y, BulletSpeed, BulletSpeed, m_TestInfo.playerPos.x, m_TestInfo.playerPos.y);

	m_fAtackPosX = m_TestInfo.enemyPos.x;
	m_fAtackPosY = m_TestInfo.enemyPos.y;
	
	return false;
}

bool CAtack_TESTBOS3::TeleportEnemy(void)
{

	//分身敵
	m_KURIBO.ClonUpdate(m_EneCount);
	m_KURIBO.CollisionStage(m_EneCount);
	m_EneCount++;
	if (m_EneCount==CloningCount) {
		m_EneCount = 0;
	}
	m_EneCount += m_Counting;
	if (m_EneCount == CloningCount) {
		m_Counting = -1 ;
		m_EneCount == CloningCount - 1;
	}
	else if (m_EneCount == 0) {
		m_Counting = 1 ;
	}

	return false;

}

