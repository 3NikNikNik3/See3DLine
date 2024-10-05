#pragma once

#include "raylib.h"

#include "raygui.h"

namespace See3DLine {
	namespace Screens {
		const int y_button = 10;

		class Screen {
		public:
			virtual void draw(Rectangle rec) = 0;

			virtual void logic(float delta) = 0;
		};
	}
}