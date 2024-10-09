#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "hpp/ScreenLines.hpp"
#include "hpp/ScreenSettings.hpp"

using namespace See3DLine;


int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(500, 500, "See3DLine");
	SetTargetFPS(60);
	SetExitKey(KeyboardKey::KEY_TAB);

	Font font = GetFontDefault();
	font.baseSize = 8;
	GuiSetFont(font);

	std::vector<Screens::Screen*> screens = { new Screens::ScreenLine({ 2, 2 }), new Screens::ScreenSettings() };
	int id_screen = 0;

	while (!WindowShouldClose()) {
		for (int i = 0; i < screens.size(); ++i) {
			if (IsKeyPressed(KeyboardKey::KEY_ONE + i) && screens[id_screen]->can_quit()) {
				id_screen = i;
			}
		}

		screens[id_screen]->logic(GetFrameTime());

		BeginDrawing();
		ClearBackground(Graphics::Points::GetColorFon());

		screens[id_screen]->draw({ 0, (float)GetScreenHeight() / Screens::y_button, (float)GetScreenWidth(), (float)GetScreenHeight() * (1 - 1.0f / Screens::y_button)});
		
		for (int i = 0; i < screens.size(); ++i) {
			if (GuiButton({ i * GetScreenWidth() / (float)screens.size(), 0, GetScreenWidth() / (float)screens.size(), (float)GetScreenHeight() / Screens::y_button }, screens[i]->name.c_str())) {
				id_screen = i;
			}
		}

		EndDrawing();
	}

	for (int i = 0; i < screens.size(); ++i)
		delete screens[i];
	return 0;
}