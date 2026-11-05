
inline void S3D_SetPixel(S3D_Renderer* renderer, int x, int y, Color color)
{
	Image& image = renderer->color_buffer;
	Color* pixels = (Color*)image.data;
	pixels[y * image.width + x] = color;
}

inline void S3D_ClearColor(S3D_Renderer* renderer, Color color)
{
	for (int y = 0; y < renderer->color_buffer.height; y++)
	{
		for (int x = 0; x < renderer->color_buffer.width; x++)
		{
			S3D_SetPixel(renderer, x, y, color);
		}
	}
}
