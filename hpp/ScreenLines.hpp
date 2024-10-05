#pragma once

#include "Screen.hpp"

#include "Graphics.hpp"

namespace See3DLine {
	namespace Screens {
		class ScreenLine : public Screen {
			Math::Vector2 size_see;
			bool move_now;

		public:
			ScreenLine(Math::Vector2 size_see);

			~ScreenLine();

			void draw(Rectangle rec);

			void logic(float delta);
		};
	}
}