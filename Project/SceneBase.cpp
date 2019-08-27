#include		"SceneBase.h"


void CSceneBase::SceneEffect1Update() {


	if (m_NowScene != m_NextScene) {

		m_Effect.Alpha -= 5;

		if (m_Effect.Alpha <= 0) {

			m_NextScene = m_NowScene;
			m_bEnd = true;
		}

	}
	else {

		if (m_Effect.Alpha < 255) {

			m_Effect.Alpha += 5;

		}

	}
}



void CSceneBase::SceneEffect2Update() {

	if (m_NowScene != m_NextScene) {

		float width = 128.0f;
		float height = 128.0f;

		float sw = g_pGraphics->GetTargetWidth();
		float sh = g_pGraphics->GetTargetHeight();





		m_Effect.RectX += width * 2;

		if (m_Effect.RectX >= sw) {

			m_Effect.RectX = 0;

			m_Effect.RectY += height;

			if (m_Effect.RectY > sh) {

				m_NextScene = m_NowScene;
				m_bEnd = true;

			}


		}

	}

}

void CSceneBase::SceneEffect2Render() {

	

		

		if (m_NowScene != m_NextScene) {

		float width = 128.0f;
		float height = 128.0f;

		float sw = g_pGraphics->GetTargetWidth();


		for (float y = 0; y <= m_Effect.RectY; y += height) {

			for (float x = 0; x < m_Effect.RectX; x += width) {

				CGraphicsUtilities::RenderFillRect(x, y, x + width, y + height, MOF_XRGB(0, 0, 0));
			}
		}

		for (float y = 0; y < m_Effect.RectY; y += height) {

			for (float x = 0; x < sw; x += width) {

				CGraphicsUtilities::RenderFillRect(x, y, x + width, y + height, MOF_XRGB(0, 0, 0));
			}
		}

	}
}

void CSceneBase::EffectUpdate(int effectNo) {

	switch (effectNo)
	{

	case EFFECTNO_1:
		SceneEffect1Update();
		break;
	case EFFECTNO_2:
		SceneEffect2Update();
		break;

	}


}
void CSceneBase::EffectRender(int effectNo) {

	switch (effectNo)
	{

	case EFFECTNO_1:
	case EFFECTNO_2:

		SceneEffect2Render();
		break;

	}

}