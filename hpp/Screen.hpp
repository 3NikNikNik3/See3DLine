#pragma once

#include "raylib.h"

#include "raygui.h"

#include <string>

namespace See3DLine {
	namespace Screens {
		const int y_button = 20;

		class Screen {
		public:
			std::string name;

			Screen(std::string name) : name(name) {}

			virtual void draw(Rectangle rec) = 0;

			virtual void logic(float delta) = 0;
		};
	}
}