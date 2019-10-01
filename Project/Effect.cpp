#include "Effect.h"



Effect::Effect()
{
}


Effect::~Effect()
{
}

void Effect::Initialize(int type)
{
	m_Posx = 0.0f;
	m_Posy = 0.0f;
	m_bshow = false;
//	switch (type)
//	{
//		case EFC_01:
//		{
//			//アニメーションの作成
//			SpriteAnimationCreate anim[] = {
//				{
//					"仮設定０１",
//					0,0,
//					0,0,
//					FALSE,{{2,0,0},{2,1,0},{2,2,0}}
//}
//			},
//		}
//	}

}

void Effect::Update(void)
{
}

void Effect::Render(void)
{
}

void Effect::RenderDebug(void)
{
}

void Effect::Release(void)
{
}
