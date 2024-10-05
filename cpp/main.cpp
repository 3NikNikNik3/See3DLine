#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "hpp/Graphics.hpp"
#include <iostream>

using namespace See3DLine;


int main() {
	Graphics::Points::init(std::vector<Graphics::Point*>{
		new Graphics::Point(Math::Vector3{ 0, 0, 0 }, new char[1] {'A'}),
		new Graphics::Point({ 0, 0, 0.5 }, new char[1] {'B'}),
		new Graphics::Point({ 0.5, 0.5, 0.5 }, new char[1] {'C'})
	}, std::vector<Graphics::Line*>{
		new Graphics::Line(new char[1] {'A'}, new char[1] {'B'}),
			new Graphics::Line(new char[1] {'B'}, new char[1] {'C'}),
			new Graphics::Line(new char[1] {'C'}, new char[1] {'A'})
	});
	Graphics::Points::reset_camera();

	InitWindow(500, 500, "See3DLine");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		*Graphics::Points::GetAng() *= Math::Matrix({ {cos(PI / 100), 0, sin(PI / 100)}, {0, 1, 0}, {-sin(PI / 100), 0, cos(PI / 100)}});

		BeginDrawing();
		ClearBackground({ 255, 255, 255, 255 });
		Graphics::Points::draw({ 0, 0, 500, 500 }, { 2, 2 });
		EndDrawing();
	}


	Graphics::Points::close();
	return 0;
}