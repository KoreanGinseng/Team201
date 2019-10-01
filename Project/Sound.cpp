#include		"Sound.h"

CSound::CSound() {



}

CSound::~CSound() {


}

void CSound::Initialize() {
	//ループフラグの初期化
	m_bLoop = false;
	//プレイフラグの初期化
	m_bPlay = false;
	//ストップフラグの初期化
	m_bStop = false;
	//ボリュームの初期化
	m_Volume = 1.0f;

}

void CSound::Start(bool loop) {

	//メンバの設定
	m_bLoop = loop;
	m_bPlay = true;

	//ループ設定
	m_pSound->SetLoop(m_bLoop);
}

void CSound::Stop(int stopType) {

	switch (stopType)
	{
	//急停止
	case STOP_SUDDEN:

		if (m_pSound->IsPlay()) {

			m_pSound->Stop();

		}
		break;
	//徐々に停止
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

	//プレイフラグが立っていて、サウンドが再生されていない場合再生する
	if (!m_pSound->IsPlay()&&m_bPlay) {

		m_pSound->Play();

		m_bPlay = false;

	}

	//徐々に停止する
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
