#pragma once

#include "raylib.h"

namespace See3DLine {
	namespace Screens {
		class Screen {
		public:
			virtual void draw(Rectangle rec) = 0;

			virtual void logic(float delta) = 0;
		};
	}
}