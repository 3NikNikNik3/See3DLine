#pragma once

#include "Screen.hpp"

namespace See3DLine {
	namespace Screens {
		class ScreenSettings : public Screen {
		public:
			ScreenSettings() : Screen("Settings") {}

			void draw(Rectangle rec);

			void logic(float delta);

			void load(std::string name);

			void save(std::string name);
		};
	}
}