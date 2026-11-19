
void S3D_DrawLineX(S3D_Renderer* renderer, int row, int x0, int x1, Color color)
{
	//x0 should always be lower than x1. Thats a handy function
	if (x0 > x1) std::swap(x0, x1);

	//and this checks that all pixels are inbound
	S3D_Rectangle bounds;
	bounds.min.x = x0;
	bounds.max.x = x1;
	bounds.min.y = row;
	bounds.max.y = row;
	assert(S3D_CheckScreenContainsRec(renderer, bounds));

	// for x in x0 to x1:
	//		set pixel at x, row
	for (int lineX = x0; lineX <= x1; lineX++) {
		S3D_SetPixelColor(renderer->color_buffer, lineX, row, color);
	}
}

void S3D_DrawLineY(S3D_Renderer* renderer, int col, int y0, int y1, Color color)
{
	if (y0 > y1) std::swap(y0, y1);

	S3D_Rectangle bounds;
	bounds.min.y = y0;
	bounds.max.y = y1;
	bounds.min.x = col;
	bounds.max.x = col;
	assert(S3D_CheckScreenContainsRec(renderer, bounds));

	// for y in y0 to y1:
	//		set pixel at col, y

	for (int lineY = y0; lineY <= y1; lineY++) {
		S3D_SetPixelColor(renderer->color_buffer, col, lineY, color);
	}
}

void S3D_DrawLine(S3D_Renderer* renderer, int x0, int y0, int x1, int y1, Color color0, Color color1 = BLANK)
{
	int dx = x1 - x0;
	int dy = y1 - y0;

	S3D_Rectangle bounds;
	bounds.min.x = x0 < x1 ? x0 : x1;
	bounds.min.y = y0 < y1 ? y0 : y1;
	bounds.max.x = bounds.min.x + abs(dx);
	bounds.max.y = bounds.min.y + abs(dy);
	if (!S3D_CheckScreenContainsRec(renderer, bounds)) return;

	// let steps = abs dx if abs dx > abs dy, else abs dy
	// abs = "absolute value"
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	// let xStep = dx / steps as float
	// let yStep = dy / steps as float
	float xStep = (float)dx / steps;
	float yStep = (float)dy / steps;

	// x = x0
	// y = y0
	float x = x0;
	float y = y0;

	// set pixel at x, y
	S3D_SetPixelColor(renderer->color_buffer, x, y, color0);

	// for i in steps:
	//		x += xStep
	//		y += yStep
	//		set pixel at x, y
	for (int i = 0;i < steps;i++) {
		x += xStep;
		y += yStep;
		S3D_SetPixelColor(renderer->color_buffer, x, y, color0);
	}
}
