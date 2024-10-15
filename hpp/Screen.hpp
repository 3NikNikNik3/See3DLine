#pragma once

#ifdef INCLUDE_UP
	#include "../../raylib/src/raylib.h"
	#include "../../raylib/src/raygui.h"
#else
	#include "raylib.h"
	#include "raygui.h"
#endif

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

			virtual bool can_quit() { return true; };
		};
	}
}
