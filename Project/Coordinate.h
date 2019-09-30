#pragma once
#include	"Mof.h"
#include	"GameDefine.h"
//関数のプロトタイプ宣言
Vector2 WorldTransration(Vector2 cp, Vector2 sp);
Vector2 ScreenTransration(Vector2 cp, Vector2 wp);
bool CollisionRectCircle(const CRectangle rect, const CCircle cir);