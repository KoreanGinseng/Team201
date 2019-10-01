#include		"Sound.h"

CSound::CSound() {



}

CSound::~CSound() {


}

void CSound::Initialize() {
	//���[�v�t���O�̏�����
	m_bLoop = false;
	//�v���C�t���O�̏�����
	m_bPlay = false;
	//�X�g�b�v�t���O�̏�����
	m_bStop = false;
	//�{�����[���̏�����
	m_Volume = 1.0f;

}

void CSound::Start(bool loop) {

	//�����o�̐ݒ�
	m_bLoop = loop;
	m_bPlay = true;

	//���[�v�ݒ�
	m_pSound->SetLoop(m_bLoop);
}

void CSound::Stop(int stopType) {

	switch (stopType)
	{
	//�}��~
	case STOP_SUDDEN:

		if (m_pSound->IsPlay()) {

			m_pSound->Stop();

		}
		break;
	//���X�ɒ�~
	case STOP_GRADUALLY:

		if (m_pSound->IsPlay()) {

			m_bStop = true;

		}
		

		break;
	}

	
}

float CSound::RenderDebug() {

	return m_Volume;

}
void CSound::Update() {

	//�v���C�t���O�������Ă��āA�T�E���h���Đ�����Ă��Ȃ��ꍇ�Đ�����
	if (!m_pSound->IsPlay()&&m_bPlay) {

		m_pSound->Play();

		m_bPlay = false;

	}

	//���X�ɒ�~����
	if (m_bStop) {

		if (m_pSound->IsPlay()) {

			m_Volume -= 0.1f;
			m_pSound->SetVolume(m_Volume);
			if (m_Volume <= 0) {

				m_Volume = 1.0f;
				m_pSound->SetVolume(m_Volume);
				m_bStop = false;
				m_pSound->Stop();

			}
		}

	}
	
}
