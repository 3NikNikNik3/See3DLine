#pragma once

#include "Screen.hpp"

namespace See3DLine {
	namespace Screens {
		class ScreenSettings : public Screen {
			char* name;

			float timer_error = 1;

		public:
			ScreenSettings();

			~ScreenSettings();

			void draw(Rectangle rec);

			void logic(float delta);

			void load();

			void save();

			void error();

			bool can_quit();
		};
	}
}