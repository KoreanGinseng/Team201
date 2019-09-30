#include	"Coordinate.h"

Vector2 WorldTransration(Vector2 cp, Vector2 sp) {
	return Vector2(sp.x + cp.x, sp.y + cp.y);
}

Vector2 ScreenTransration(Vector2 cp, Vector2 wp) {
	return Vector2(wp.x - cp.x, wp.y - cp.y);
}

bool CollisionRectCircle(const CRectangle rect, const CCircle cir) {

	if ((cir.x >= rect.Left) &&
		(cir.x <= rect.Right) &&
		(cir.y >= rect.Top - cir.r) &&
		(cir.y <= rect.Bottom + cir.r)) {
		return true;
	}
	if ((cir.x >= rect.Left - cir.r) &&
		(cir.x <= rect.Right + cir.r) &&
		(cir.y >= rect.Top) &&
		(cir.y <= rect.Bottom)) {
		return true;
	}
	float a = rect.Left - cir.x;
	float b = rect.Top - cir.y;
	float c = sqrtf(a * a + b * b);
	if (c <= cir.r) {
		return true;
	}
	float d = rect.Right - cir.x;
	float e = rect.Top - cir.y;
	float f = sqrtf(d * d + e * e);
	if (f <= cir.r) {
		return true;
	}
	float g = rect.Left - cir.x;
	float h = rect.Bottom - cir.y;
	float i = sqrtf(g * g + h * h);
	if (i <= cir.r) {
		return true;
	}
	float j = rect.Right - cir.x;
	float k = rect.Bottom - cir.y;
	float l = sqrtf(j * j + k * k);
	if (l <= cir.r) {
		return true;
	}

	return false;
}
