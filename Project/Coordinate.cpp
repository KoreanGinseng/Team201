#include	"Coordinate.h"

Vector2 WorldTransration(Vector2 cp, Vector2 sp) {
	return Vector2(sp.x + cp.x, sp.y + cp.y);
}

Vector2 ScreenTransration(Vector2 cp, Vector2 wp) {
	return Vector2(wp.x - cp.x, wp.y - cp.y);
}