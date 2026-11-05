class Demo
{
public:
	virtual void Load(S3D_Renderer* renderer) {}
	virtual void Unload(S3D_Renderer* renderer) {}

	virtual void Update(S3D_Renderer* renderer) {}
	virtual void Draw(S3D_Renderer* renderer) {}
};

// Screen-space gradient, https://www.shadertoy.com/view/4XcfWl
class Demo1 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		// Hint: you'll need to write a nested for-loop that runs width * height amount of pixels!
		Vector2 uv = Vector2{};
		Color color = ColorFromNormalized({ 0.0f, 1.0f, 0.5f, 1.0f });
		for (int x = 0; x < renderer->width; x++) {
			for (int y = 0;y < renderer->height;y++) {
				uv.x = (float)x / renderer->width;
				uv.y = (float)y / renderer->height;

				color = ColorFromNormalized({ uv.x, uv.y, 0.0f, 1.0f });

				S3D_SetPixel(renderer, x, y, color);
			}
		}
		//Color color = ColorFromNormalized({ 0.0f, 1.0f, 0.5f, 1.0f });
		//S3D_ClearColor(renderer, color);
	}
};

// NDC circle, https://www.shadertoy.com/view/fcfXWj
class Demo2 : public Demo
{
public:
	void Update(S3D_Renderer* renderer) final
	{
		// Hint: you'll need to write a nested for-loop that runs width * height amount of pixels!

		Vector2 uv = Vector2{};
		Color color = ColorFromNormalized({ 0.0f, 1.0f, 0.5f, 1.0f });

		float aspectRation = renderer->width / renderer->height;
		float dCircle = 0.0f;

		//SDCircle
		Vector2 position = Vector2{ (float)renderer->width / 2, (float)renderer->height / 2 };
		float radius = 80.0f;

		for (int x = 0; x < renderer->width; x++) {
			for (int y = 0;y < renderer->height;y++) {
				uv.x = (float)x / renderer->width;
				uv.y = (float)y / renderer->height;


				uv *= 2.0f;
				uv.x -= 1.0f;
				uv.y -= 1.0f;

				dCircle = Vector2Length(uv) - radius;
				
				uv.x = Clamp(uv.x, 0.0f, 1.0f);
				uv.y = Clamp(uv.y, 0.0f, 1.0f);
				//dCircle = Clamp(dCircle, 0.0f, 1.0f);
				color = ColorFromNormalized({ dCircle, dCircle, dCircle, 1.0f });

				S3D_SetPixel(renderer, x, y, color);
			}
		}

		//S3D_ClearColor(renderer, GREEN);
	}
};
