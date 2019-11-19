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

void String(int sx, int sy, int fontsize, const char * str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		float X = str[i] % 16;
		float Y = ((str[i] - 32) / 16);
		CRectangle SRect(X * 64, Y * 64,
			X * 64 + 64, Y * 64 + 64);
		sx += fontsize;
		g_pTextureManager->GetResource(FileName[TEXTURE_FONT])->RenderScale(sx, sy, fontsize / 64.0, SRect);
	}
}

void String(int sx, int sy, int fontsize, const int& time)
{
	std::string str;
	str = std::to_string(time);
	size_t size = str.length() - 1;
	for (int i = 0; str[i] != '\0'; i++)
	{
		float X = str[i] % 16;
		float Y = ((str[i] - 32) / 16);
		CRectangle SRect(X * 64, Y * 64,
			X * 64 + 64, Y * 64 + 64);
		sx += fontsize;
		g_pTextureManager->GetResource(FileName[TEXTURE_FONT])->RenderScale(sx - size * fontsize, sy, fontsize / 64.0, SRect);
	}
}