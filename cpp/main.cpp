#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "hpp/ScreenLines.hpp"
#include <iostream>

using namespace See3DLine;


int main() {
	InitWindow(500, 500, "See3DLine");

	SetTargetFPS(60);

	Screens::Screen *screen = new Screens::ScreenLine({ 2, 2 });

	//*Graphics::Points::GetAng() *= Math::Matrix({ {cos(PI / 6), 0, sin(PI / 6)}, {0, 1, 0}, {-sin(PI / 6), 0, cos(PI / 6)} });

	while (!WindowShouldClose()) {
		//*Graphics::Points::GetAng() *= Math::Matrix({ {cos(PI / 100), 0, sin(PI / 100)}, {0, 1, 0}, {-sin(PI / 100), 0, cos(PI / 100)}});

		screen->logic(GetFrameTime());

		BeginDrawing();
		ClearBackground({ 255, 255, 255, 255 });
		screen->draw({ 0, 0, 500, 500 });
		EndDrawing();
	}


	delete screen;
	return 0;
}