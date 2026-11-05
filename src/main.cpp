#include "S3D.cpp"

enum DemoType
{
	DEMO_01_GRADIENT,
	DEMO_02_CIRCLE,
	DEMO_TYPE_COUNT
};

struct App
{
	Demo* demos[DEMO_TYPE_COUNT];
	int demo_index;

	S3D_Renderer renderer;
	Texture framebuffer;
};

void AppInit(App* app);
void AppQuit(App* app);

void AppDrawDemosList(App* app);

const char* GetDemoName(int demo_index);
const char* GetDemoNames();

int main()
{
	App app{};
	AppInit(&app);

	while (!WindowShouldClose())
	{
		Demo* demo = app.demos[app.demo_index];
		demo->Update(&app.renderer);
		ImageFlipVertical(&app.renderer.color_buffer);

		BeginDrawing();
			UpdateTexture(app.framebuffer, app.renderer.color_buffer.data);
			DrawTexture(app.framebuffer, 0, 0, WHITE);
			demo->Draw(&app.renderer);
			AppDrawDemosList(&app);
			DrawFPS(680, 10);
		EndDrawing();
	}

	AppQuit(&app);
	return 0;
}

void AppInit(App* app)
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(768, 768, "s3d-lite");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

	{
		S3D_Renderer& renderer = app->renderer;
		renderer.width = GetScreenWidth();
		renderer.height = GetScreenHeight();

		renderer.color_buffer = GenImageColor(renderer.width, renderer.height, BLACK);
		app->framebuffer = LoadTextureFromImage(renderer.color_buffer);
	}

	{
		Demo** demos = app->demos;
		demos[DEMO_01_GRADIENT] = new Demo1;
		demos[DEMO_02_CIRCLE] = new Demo2;
	}

	app->demo_index = 0;
	app->demos[app->demo_index]->Load(&app->renderer);
	SetWindowTitle(GetDemoName(app->demo_index));
}

void AppQuit(App* app)
{
	app->demos[app->demo_index]->Unload(&app->renderer);
	for (int i = 0; i < DEMO_TYPE_COUNT; i++)
	{
		delete app->demos[i];
	}

	UnloadTexture(app->framebuffer);
	UnloadImage(app->renderer.color_buffer);
	CloseWindow();
}

void AppDrawDemosList(App* app)
{
	static bool demo_select = false;
	if (IsKeyPressed(KEY_GRAVE)) demo_select = !demo_select;

	if (demo_select)
	{
		static int scroll = 0;
		int demo_index = app->demo_index;

		Rectangle rec;
		rec.width = 160.0f;
		rec.height = 100.0f;
		rec.x = 10.0f;
		rec.y = GetScreenHeight() - rec.height;
		GuiListView(rec, GetDemoNames(), &scroll, &demo_index);

		if (demo_index != -1 && demo_index != app->demo_index)
		{
			SetWindowTitle(GetDemoName(demo_index));

			app->demos[demo_index]->Unload(&app->renderer);
			app->demo_index = demo_index;
			app->demos[demo_index]->Load(&app->renderer);

			demo_select = false;
		}
	}
}

const char* GetDemoName(int demo_index)
{
	static int count = 0;
	static char** demo_names_split = TextSplit(GetDemoNames(), ';', &count);
	assert(count == DEMO_TYPE_COUNT);

	char* demo_name = demo_names_split[demo_index];
	return demo_name;
}

const char* GetDemoNames()
{
	static const char* demo_names =
		"01: Gradient;"
		"02: Circle";
	
	return demo_names;
}
