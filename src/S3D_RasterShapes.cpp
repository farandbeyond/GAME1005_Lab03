
void S3D_DrawRectangle(S3D_Renderer* renderer, S3D_Rectangle rec, Color color)
{
	assert(S3D_CheckScreenContainsRec(renderer, rec));
	for (int y = rec.min.y; y <= rec.max.y; y++)
	{
		for (int x = rec.min.x; x <= rec.max.x; x++)
		{
			S3D_SetPixel(renderer, x, y, color);
		}
	}
}

void S3D_DrawRectangleLines(S3D_Renderer* renderer, S3D_Rectangle rec, Color color)
{
	assert(S3D_CheckScreenContainsRec(renderer, rec));
	S3D_DrawLineX(renderer, rec.min.y, rec.min.x, rec.max.x, color);
	S3D_DrawLineX(renderer, rec.max.y, rec.min.x, rec.max.x, color);
	S3D_DrawLineY(renderer, rec.min.x, rec.min.y, rec.max.y, color);
	S3D_DrawLineY(renderer, rec.max.x, rec.min.y, rec.max.y, color);
}

void S3D_DrawCircle(S3D_Renderer* renderer, int cx, int cy, int cr, Color color)
{
	assert(S3D_CheckScreenContainsCircle(renderer, cx, cy, cr));

	int x = 0;
	int y = cr;
	int d = 3 - 2 * cr;

	auto line = [&](int lx, int ly, int l)
	{
		for (int dx = -l; dx <= l; dx++)
			S3D_SetPixel(renderer, lx + dx, ly, color);
	};

	while (y >= x)
	{
		line(cx, cy + y, x);
		line(cx, cy - y, x);
		line(cx, cy + x, y);
		line(cx, cy - x, y);

		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
		{
			d = d + 4 * x + 6;
		}
	}
}

void S3D_DrawCircleLines(S3D_Renderer* renderer, int cx, int cy, int cr, Color color)
{
	assert(S3D_CheckScreenContainsCircle(renderer, cx, cy, cr));

	int x = 0;
	int y = cr;
	int d = 3 - 2 * cr;

	while (y >= x)
	{
		S3D_SetPixel(renderer, cx + x, cy + y, color);
		S3D_SetPixel(renderer, cx - x, cy + y, color);
		S3D_SetPixel(renderer, cx + x, cy - y, color);
		S3D_SetPixel(renderer, cx - x, cy - y, color);
		S3D_SetPixel(renderer, cx + y, cy + x, color);
		S3D_SetPixel(renderer, cx - y, cy + x, color);
		S3D_SetPixel(renderer, cx + y, cy - x, color);
		S3D_SetPixel(renderer, cx - y, cy - x, color);

		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
		{
			d = d + 4 * x + 6;
		}
	}
}
