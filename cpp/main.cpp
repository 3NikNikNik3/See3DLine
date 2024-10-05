#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "hpp/ScreenLines.hpp"
#include <iostream>

using namespace See3DLine;


int main() {
	InitWindow(500, 500, "See3DLine");
	SetTargetFPS(60);
	SetExitKey(KeyboardKey::KEY_TAB);

	Screens::Screen *screen = new Screens::ScreenLine({ 2, 2 });

	while (!WindowShouldClose()) {
		screen->logic(GetFrameTime());

		BeginDrawing();
		ClearBackground(Graphics::Points::GetColorFon());
		screen->draw({ 0, 0, 500, 500 });
		EndDrawing();
	}


	delete screen;
	return 0;
}