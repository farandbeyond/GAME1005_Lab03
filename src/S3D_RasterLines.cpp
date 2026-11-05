
void S3D_DrawLineX(S3D_Renderer* renderer, int row, int x0, int x1, Color color)
{
	if (x0 > x1) std::swap(x0, x1);

	S3D_Rectangle bounds;
	bounds.min.x = x0;
	bounds.max.x = x1;
	bounds.min.y = row;
	bounds.max.y = row;
	assert(S3D_CheckScreenContainsRec(renderer, bounds));
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
}

void S3D_DrawLine(S3D_Renderer* renderer, int x0, int y0, int x1, int y1, Color color0, Color color1 = BLANK)
{
	
}
