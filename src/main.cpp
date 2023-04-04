#include "raylib.h"
#include "raylibRmlUi.h"

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1280, 720, "Raylib - RmlUi example");
	SetTargetFPS(500);

	RaylibRmlUi::Initialize(1280, 720);

	while(!WindowShouldClose()) {
		RaylibRmlUi::Update();
		BeginDrawing();

		ClearBackground(RAYWHITE);

		RaylibRmlUi::Draw();

		DrawFPS(10, 10);

		EndDrawing();
	}

	RaylibRmlUi::DeInitialize();

	return 0;
}
