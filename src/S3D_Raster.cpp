
inline Color S3D_GetPixelColor(Image image, int x, int y)
{
	Color* pixels = (Color*)image.data;
	Color color = pixels[y * image.width + x];
	return color;
}

inline float S3D_GetPixelDepth(Image image, int x, int y)
{
	float* pixels = (float*)image.data;
	float depth = pixels[y * image.width + x];
	return depth;
}

inline void S3D_SetPixelColor(Image image, int x, int y, Color color)
{
	Color* pixels = (Color*)image.data;
	pixels[y * image.width + x] = color;
}

inline void S3D_SetPixelDepth(Image image, int x, int y, float depth)
{
	float* pixels = (float*)image.data;
	pixels[y * image.width + x] = depth;
}

inline void S3D_ClearColor(S3D_Renderer* renderer, Color color)
{
	for (int x = 0; x < renderer->color_buffer.width; x++)
	{
		for (int y = 0; y < renderer->color_buffer.height; y++)
		{
			S3D_SetPixelColor(renderer->color_buffer, x, y, color);
		}
	}
}

inline void S3D_ClearDepth(S3D_Renderer* renderer, float depth)
{
	for (int x = 0; x < renderer->depth_buffer.width; x++)
	{
		for (int y = 0; y < renderer->depth_buffer.height; y++)
		{
			S3D_SetPixelDepth(renderer->depth_buffer, x, y, depth);
		}
	}
}

inline Color S3D_SampleImage(Image image, float u, float v)
{
	int x = (image.width - 1) * u;
	int y = (image.height - 1) * v;
	Color color = S3D_GetPixelColor(image, x, y);
	return color;
}
