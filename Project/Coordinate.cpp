#include	"Coordinate.h"

Vector2 WorldTransration(Vector2 cp, Vector2 sp) {
	return Vector2((sp.x - g_pGraphics->GetTargetWidth() / 2) + cp.x, -((sp.y - g_pGraphics->GetTargetHeight() / 2) + cp.y));
}

Vector2 ScreenTransration(Vector2 cp, Vector2 wp) {
	return Vector2((wp.x + g_pGraphics->GetTargetWidth() / 2) - cp.x, -((wp.y - g_pGraphics->GetTargetHeight() / 2) - cp.y));
}