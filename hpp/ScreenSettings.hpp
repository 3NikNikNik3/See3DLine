#pragma once

#include "Screen.hpp"

#include "Graphics.hpp"

namespace See3DLine {
	namespace Screens {
		class ScreenSettings : public Screen {
			std::string name;

			float timer_error = 1;

			Vector2* scroll_points;
			Rectangle* view_points;

			bool name_file_edit = false;

			std::vector<std::vector<bool>> points_edit;

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