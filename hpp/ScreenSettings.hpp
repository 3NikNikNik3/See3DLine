#pragma once

#include "Screen.hpp"

#include "Graphics.hpp"

#include <filesystem>
#include <fstream>

namespace See3DLine {
	namespace Screens {
		class ScreenSettings : public Screen {
			std::string name;

			float timer_error = 1;

			Vector2* scroll_points, *scroll_lines;
			Rectangle* view_points, *view_lines;

			bool name_file_edit = false;

			std::vector<std::vector<bool>> points_edit, lines_edit;

			int count_color_line = 0;

			std::vector<std::vector<bool>> color_line_edit;

			std::vector<bool> color_fon_edit;

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