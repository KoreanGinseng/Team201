#pragma once
#include	"Mof.h"
#include	"GameDefine.h"
//�֐��̃v���g�^�C�v�錾
Vector2 WorldTransration(Vector2 cp, Vector2 sp);
Vector2 ScreenTransration(Vector2 cp, Vector2 wp);
bool CollisionRectCircle(const CRectangle rect, const CCircle cir);
void String(int sx, int sy, int fontsize, const char * str);
void String(int sx, int sy, int fontsize, const int& time);
void NewPointerRelease(void* p);