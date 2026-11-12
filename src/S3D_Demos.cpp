class Demo
{
public:
	virtual void Load(S3D_Renderer* renderer) {}
	virtual void Unload(S3D_Renderer* renderer) {}

	virtual void Update(S3D_Renderer* renderer) {}
	virtual void Draw(S3D_Renderer* renderer) {}
};

// Screen-space gradient
class Demo1 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		float t = sinf(GetTime()) * 0.5f + 0.5f;
		//Color color = WHITE;
		//color.g++; // "Overflow"  -- wraps from highest (255) to lowest (0)
		//color.g--; // "Underflow" -- wraps from lowest (0) to 255 (highest)
		// If you pass a value less than 0.0 or greater than 1.0 to ColorFromNormalized, expect problems!
		for (int x = 0; x < renderer->width; x++)
		{
			for (int y = 0; y < renderer->height; y++)
			{
				float u = x / (float)(renderer->width  - 1);
				float v = y / (float)(renderer->height - 1);
				Color color = ColorFromNormalized({ u, v, t, 1.0f });
				S3D_SetPixelColor(renderer->color_buffer, x, y, color);
			}
		}
	}
};

// NDC circle
class Demo2 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		for (int x = 0; x < renderer->width; x++)
		{
			for (int y = 0; y < renderer->height; y++)
			{
				float u = x / (float)(renderer->width - 1);
				float v = y / (float)(renderer->height - 1);
				Vector3 ndc = S3D_ScreenToNDC(renderer, { x, y }); // [-1..1]

				// Visualize how S3D_ScreenToNDC transforms uvs to screen centre
				//ndc = Vector3Clamp(ndc, Vector3Zeros, Vector3Ones);
				//Color color = ColorFromNormalized({ ndc.x, ndc.y, 0.0f, 1.0f });

				// ColorFromNormalized will overflow unless we clamp!
				float d = Vector3Length(ndc);
				d = fminf(d, 1.0f);
				Color color = ColorFromNormalized({ d, d, d, 1.0f });
				S3D_SetPixelColor(renderer->color_buffer, x, y, color);
			}
		}
	}
};

class Demo3 : public Demo
{
public:
	//screen size: 0,0 to 768,768
	int lineXRow = 100;
	int lineYCol = 56;

	int middleRectWidth = 50;
	int middleRectHeight = 25;

	int mouseCircleRadius = 10;
	//S3D_Rectangle fillRect = {Vector2i(50, 50), Vector2i(300, 300)};
	//S3D_Rectangle strokeRect = { Vector2i(500, 500), Vector2i(600, 700) };

	void Update(S3D_Renderer* renderer) final
	{
		S3D_ClearColor(renderer, BLACK);

		//debug code; now for the real lab
		////the -1 is needed to remain inbounds
		//S3D_DrawLineX(renderer, lineXRow, 0, renderer->width - 1, RED);
		//S3D_DrawLineY(renderer, lineYCol, 0, renderer->height - 1, GREEN);

		//S3D_DrawLine(renderer, 0, 0, renderer->width - 1, renderer->height / 2, YELLOW);

		//S3D_DrawRectangle(renderer, fillRect, ORANGE);
		//S3D_DrawRectangleLines(renderer, strokeRect, BLUE);

		//a border around the screen, using DrawRectangleLines
		S3D_DrawRectangleLines(renderer, {Vector2i(0,0), Vector2i(renderer->width-1, renderer->height-1)}, YELLOW);

		//a Horizontal and Vertical line using DrawLine X/Y
		//the -1 is needed to remain inbounds
		S3D_DrawLineX(renderer, lineXRow, 0, renderer->width - 1, RED);
		S3D_DrawLineY(renderer, lineYCol, 0, renderer->height - 1, GREEN);

		//a rectangle in the center of the screen with DrawRectangle
		Vector2 middleRectCenter = { renderer->width / 2, renderer->height / 2 };
		S3D_Rectangle middleRect = { Vector2i(middleRectCenter.x - middleRectWidth, middleRectCenter.y - middleRectHeight), Vector2i(middleRectCenter.x + middleRectWidth, middleRectCenter.y + middleRectHeight) };
		S3D_DrawRectangle(renderer, middleRect, ORANGE);

		//outline the above rectangle with drawrectanglelines
		S3D_DrawRectangleLines(renderer, middleRect, WHITE);

		//a circle at your mousecursor, using drawcircle, and an outline
		Vector2 mousePosition = GetMousePosition();
		//y is inverted from how I first expected; this was explained to me
		mousePosition.y = renderer->height - mousePosition.y;
		if (S3D_CheckScreenContainsCircle(renderer, mousePosition.x, mousePosition.y, mouseCircleRadius)) {
			S3D_DrawCircle(renderer, mousePosition.x, mousePosition.y, mouseCircleRadius, PURPLE);
			S3D_DrawCircleLines(renderer, mousePosition.x, mousePosition.y, mouseCircleRadius, LIGHTGRAY);
		}

		//a line, connecting the circle and the rectangle
		S3D_Rectangle lineCheckRect;// = { Vector2i(middleRectCenter.x, middleRectCenter.y), Vector2i(mousePosition.x, mousePosition.y) };
		lineCheckRect.min.x = (middleRectCenter.x < mousePosition.x) ? middleRectCenter.x : mousePosition.x;
		lineCheckRect.min.y = (middleRectCenter.y < mousePosition.y) ? middleRectCenter.y : mousePosition.y;

		lineCheckRect.max.x = (middleRectCenter.x > mousePosition.x) ? middleRectCenter.x : mousePosition.x;
		lineCheckRect.max.y = (middleRectCenter.y > mousePosition.y) ? middleRectCenter.y : mousePosition.y;
		
		if (S3D_CheckScreenContainsRec(renderer, lineCheckRect)) {
			//uncomment this line for some fun line dancing, courtesy of tan(theta)
			//S3D_DrawLine(renderer, lineCheckRect.min.x, lineCheckRect.min.y, lineCheckRect.max.x, lineCheckRect.max.y, BROWN);
			S3D_DrawLine(renderer, middleRectCenter.x, middleRectCenter.y, mousePosition.x, mousePosition.y, BROWN);
		}
	}
};
