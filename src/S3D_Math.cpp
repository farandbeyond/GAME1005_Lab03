
inline Vector2i S3D_NDCToScreen(S3D_Renderer* renderer, Vector3 ndc)
{
	Vector2i screen;
	screen.x = int((ndc.x + 1.0f) * 0.5f * ((float)renderer->width  - 1.0f));
	screen.y = int((ndc.y + 1.0f) * 0.5f * ((float)renderer->height - 1.0f));
	return screen;
}

inline Vector3 S3D_ScreenToNDC(S3D_Renderer* renderer, Vector2i screen)
{
	Vector3 ndc = Vector3Zeros;
	ndc.x = (screen.x / (((float)renderer->width  - 1.0f) * 0.5f)) - 1.0f;
	ndc.y = (screen.y / (((float)renderer->height - 1.0f) * 0.5f)) - 1.0f;
	return ndc;
}

inline Vector2i S3D_ClampToScreen(S3D_Renderer* renderer, Vector2i position)
{
	Vector2i min = { 0, 0 };
	Vector2i max = { renderer->width - 1, renderer->height - 1 };
	position.x = position.x < min.x ? min.x : position.x;
	position.x = position.x > max.x ? max.x : position.x;
	position.y = position.y < min.y ? min.y : position.y;
	position.y = position.y > max.y ? max.y : position.y;
	return position;
}

inline Vector2i S3D_GetMousePosition(S3D_Renderer* renderer)
{
	Vector2i mouse = S3D_ClampToScreen(renderer, { (int)GetMousePosition().x, (int)GetMousePosition().y });
	mouse.y = (renderer->height - 1) - mouse.y;
	return mouse;
}

inline bool S3D_CheckScreenContainsRec(S3D_Renderer* renderer, S3D_Rectangle rec)
{
	bool result =
		rec.min.x >= 0 &&
		rec.min.y >= 0 &&
		rec.max.x < renderer->width &&
		rec.max.y < renderer->height;
	return result;
}

inline bool S3D_CheckScreenContainsCircle(S3D_Renderer* renderer, int cx, int cy, int cr)
{
	S3D_Rectangle rec;
	rec.min = { cx - cr, cy - cr };
	rec.max = { cx + cr, cy + cr };

	bool result = S3D_CheckScreenContainsRec(renderer, rec);
	return result;
}

inline Vector3 MatrixPerspectiveDivide(Vector3 v, Matrix mvp)
{
	Vector4 vp = { v.x, v.y, v.z, 1.0f };
	vp *= mvp;
	vp /= vp.w;
	return { vp.x, vp.y, vp.z };
}

inline Color ColorRandomRGB()
{
	Color color;
	color.r = (unsigned char)GetRandomValue(0, 255);
	color.g = (unsigned char)GetRandomValue(0, 255);
	color.b = (unsigned char)GetRandomValue(0, 255);
	color.a = 255;
	return color;
}

inline Color ColorRandomRGBA()
{
	Color color;
	color.r = (unsigned char)GetRandomValue(0, 255);
	color.g = (unsigned char)GetRandomValue(0, 255);
	color.b = (unsigned char)GetRandomValue(0, 255);
	color.a = (unsigned char)GetRandomValue(0, 255);
	return color;
}
