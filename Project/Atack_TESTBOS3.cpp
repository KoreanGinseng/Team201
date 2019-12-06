/**
 * @file Atack_TESTBOS3.cpp
 * @brief �e�X�g�{�X3�̍U��
 * @author �吼�i��
 * @date �X�V���i12/3�j
 */

#include	"Atack_TESTBOS3.h"


CAtack_TESTBOS3::CAtack_TESTBOS3() :
	CEnemyAtack() {

}
CAtack_TESTBOS3::~CAtack_TESTBOS3() {

}
void CAtack_TESTBOS3::Initialize() {
	m_bShow = false;
	m_fAtackTimer = 0;
	m_fCooltime = 0;
	//���g���錕
	/*for (int i = 0; i < CloningCount; i++) {
		m_ClonArry[i] = new CCloningSword();
		m_ClonArry[i]->Initialize();

	}*/

	//�u�Ԉړ����錕
	for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i] = new CTeleportationSword();
		m_ShotArry[i]->Initialize();

	}
	m_TleCount = 0;

	//���g����G
	/*for (m_EneCount = 0; m_EneCount < CloningCount;m_EneCount++) {
		m_KURIBO.ClonInitialize(m_EneCount);
	}
	m_EneCount = 0;

	m_ScaleMagnification = 0;
	m_TleTime = TLeTime;

	m_Counting = 1;*/
}

void CAtack_TESTBOS3::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {
	//X���W�̍U���͈�
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
				//�u�Ԉړ����錕
				//���g��
				//ClonSwordUpdate(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);
			}
		}

	//	m_bShow = true;

	}

				TLSwordUpdate(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);

	//���g��
	/*for (int i = 0; i < CloningCount; i++) {
		m_ClonArry[i]->Update();
	}*/
	


	//���g�G
	/*m_KURIBO.ClonUpdate(m_EneCount); 
	m_KURIBO.CollisionStage(m_EneCount);
	m_EneCount++;
	if (m_EneCount==CloningCount) {
		m_EneCount = 0;
	}*/
	/*m_EneCount += m_Counting;
	if (m_EneCount == CloningCount) {
		m_Counting = -1 ;
		m_EneCount == CloningCount - 1;
	}
	else if (m_EneCount == 0) {
		m_Counting = 1 ;
	}*/



	//�u�Ԉړ�
	for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i]->Update();
	}
	if (m_ShotArry[m_TleCount]->GetTleEnd()) {
		return;
	}
	//�����_���ɐU�蕪����
	m_TleTime -= 1 * CUtilities::GetFrameSecond();
	if (m_TleTime <= 0) {
		m_TleCount = rand() % 5;
		m_TleTime = TLeTime;
	}


	////�E��
	//if (!m_Hand.GetMoveFlag()) {
	//	m_Hand.Initialize();
	//  m_AtackHand.Initialize();
	//	m_Hand.Start(PlayerPosX);
	//}
	//m_Hand.Update(PlayerPosX, PlayerPosY);
	//m_Hand.CollisionStage();


	//�E��ŏI�`��
	/*if (!m_Hand.GetMoveFlag()) {
		m_Hand.Initialize();
		m_Hand.SetLimit(true);
		m_Hand.Start(EnemyPosX);
	}
	if (m_Hand.GetFire()) {
		m_AtackHand.Initialize(m_Hand.GetXpos(),m_Hand.GetYpos());
		m_AtackHand.SetLimit(true);
		m_Hand.SetFire(false);
	}
	m_Hand.Update(PlayerPosX, PlayerPosY);
	m_AtackHand.Update();
	m_Hand.CollisionStage();*/
}

void CAtack_TESTBOS3::Render() {

	//���g��
	/*for (int i = 0; i < CloningCount; i++) {
		m_ClonArry[i]->Render();

	}*/
	
	//�E��
	//m_Hand.Render(m_fAtackPosX,m_fAtackPosY);

	////�E��Ռ��g
	//m_AtackHand.Render();

	//�u�Ԉړ�
	/*for (int i = 0; i < CloningCount; i++) {
		
	m_ShotArry[i]->Render();
	}*/
	m_ShotArry[m_TleCount]->Render();

	//���g����G
	/*m_KURIBO.ClonRender(m_EneCount);*/

}
void CAtack_TESTBOS3::Release() {
	//�u�Ԉړ�
	for (int i = 0; i < CloningCount; i++) {
		if (m_ShotArry) {
			m_ShotArry[i]->Release();
			delete[] m_ShotArry[i];
			m_ShotArry[i] = NULL;
		}
	}
	
	//���g��
	/*for (int i = 0; i < CloningCount; i++) {
		if (m_ClonArry) {
			m_ClonArry[i]->Release();
			delete[] m_ClonArry[i];
			m_ClonArry[i] = NULL;
		}
	}*/
}

void CAtack_TESTBOS3::TLSwordUpdate(float EnemyPosX, float EnemyPosY, float PlayerPosX, float PlayerPosY) {
	m_fAtackTimer = AtackTimer;
	float rd = m_ShotArry[2]->GetRadian(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);
	float ddx = m_ShotArry[2]->Getddx(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);
	float ddy = m_ShotArry[2]->Getddy(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);

	int rnd = rand() % 5;

	for (int i = 0; i < CloningCount; i++) {
		if (m_ShotArry[i]->GetShow()) {
			continue;
		}
		
		m_ShotArry[i]->Initialize();
		
		if (i == 2) {
			m_ShotArry[i]->Fire(EnemyPosX, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY);
		}
		else
		{
			m_ShotArry[i]->CloningFire(EnemyPosX + i * CloningDistance - CloningDistance * 2, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY, rd, ddx, ddy);
		}



	}
	m_fAtackPosX = EnemyPosX;
	m_fAtackPosY = EnemyPosY;
}

void CAtack_TESTBOS3::ClonSwordUpdate(float EnemyPosX, float EnemyPosY, float PlayerPosX, float PlayerPosY) {
	m_fAtackTimer = AtackTimer;
	float rd = m_ClonArry[2]->GetRadian(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);
	float ddx = m_ClonArry[2]->Getddx(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);
	float ddy = m_ClonArry[2]->Getddy(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);

	int rnd = rand() % 5;

	for (int i = 0; i < CloningCount; i++) {

		m_ClonArry[i]->Initialize();
		if (i == 2) {
			m_ClonArry[i]->Fire(EnemyPosX, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY);
		}
		else
		{
			m_ClonArry[i]->CloningFire(EnemyPosX + i * CloningDistance - CloningDistance * 2, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY, rd, ddx, ddy);
		}



	}
	m_ClonArry[rnd]->SetFrag(true);


	m_fAtackPosX = EnemyPosX;
	m_fAtackPosY = EnemyPosY;
}