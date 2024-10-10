#pragma once

#include "Screen.hpp"

#include "Graphics.hpp"


namespace See3DLine {
	namespace Screens {
		class ScreenLine : public Screen {
			Vector2 size_see, start_size_see;
			bool move_now;
			float timer;

		public:
			ScreenLine(Vector2 size_see);

			~ScreenLine();

			void draw(Rectangle rec);

			void logic(float delta);
		};
	}
}