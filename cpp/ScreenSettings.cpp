#include "hpp/ScreenSettings.hpp"

using namespace See3DLine::Graphics;

namespace See3DLine {
	namespace Screens {
		ScreenSettings::ScreenSettings() : Screen("Settings"), name("File's name"), scroll_points(new Vector2{0, 0}), view_points(new Rectangle()), scroll_lines(new Vector2{0, 0}), view_lines(new Rectangle()){
			points_edit.resize(Points::GetPoints().size(), {false, false, false, false});
			lines_edit.resize(Points::GetLines().size(), { false, false });
		}

		ScreenSettings::~ScreenSettings() {
			delete scroll_points, view_points;
			delete scroll_lines, view_lines;
		}

		int get_size_font(const char* text, int max_size) {
			int ans = 20;
			while (ans > 5 && MeasureText(text, ans) > max_size) --ans;
			return ans;
		}

		void ScreenSettings::draw(Rectangle rec) {
			if (timer_error <= 0.5)
				DrawRectangleRec(rec, { 255, 0, 0, 255 });

			// file load/save

			char* name_file = name.data();
			if (GuiTextBox({ rec.x + rec.width / 3 + 5, rec.y + 5, rec.width / 3 - 10, 40 }, name_file, 50, name_file_edit)) {
				name_file_edit = !name_file_edit;
			}
			if (strlen(name_file) != name.size())
				name = std::string(name_file);

			if (GuiButton({ rec.x + 5, rec.y + 5, rec.width / 3 - 10, 40 }, "Load")) {
				load();
			}
			if (GuiButton({ rec.x + rec.width * 2 / 3 + 5, rec.y + 5, rec.width / 3 - 10, 40 }, "Save")) {
				save();
			}

			rec.y += 50;
			rec.height -= 50;

			// points

			int font_size = get_size_font("NAME", (view_points->width - 35) / 4);
			int y_up_text = MeasureTextEx(GetFontDefault(), "NAME", font_size, 0).y;
			int* val = new int();

			GuiScrollPanel({rec.x, rec.y, rec.width / 2, rec.height}, "Points", {0, 0, rec.width / 2 - 15, (float)y_up_text + 40 * Points::GetPoints().size() }, scroll_points, view_points);

			// Add new point
			int size_add = 24;
			if (GuiButton({ rec.x + rec.width / 2 - size_add, rec.y, (float)size_add, (float)size_add }, "+")) {
				std::string new_name = "S";
				while (Points::CountPoints(new_name) != 0) {
					new_name += '\'';
				}

				Points::GetPoints().push_back(new Point{ Math::Vector3(0, 0, 0), new_name });
				points_edit.push_back({false, false, false, false});
				Points::GetPoints()[Points::GetPoints().size() - 1]->add_me(Points::GetLines());
			}

			view_points->width -= 35;

			DrawText("X", view_points->x + view_points->width / 8 - MeasureText("X", font_size) / 2, view_points->y + 5, font_size, BLACK);
			DrawText("Y", view_points->x + 3 * view_points->width / 8 - MeasureText("Y", font_size) / 2, view_points->y + 5, font_size, BLACK);
			DrawText("Z", view_points->x + 5 * view_points->width / 8 - MeasureText("Z", font_size) / 2, view_points->y + 5, font_size, BLACK);
			DrawText("NAME", view_points->x + 7 * view_points->width / 8 - MeasureText("NAME", font_size) / 2, view_points->y + 5, font_size, BLACK);

			// point's list
			int delete_point = -1;
			for (int i = 0; i < Points::GetPoints().size(); ++i) {
				if (scroll_points->y + i * 40 >= 0 && scroll_points->y + (i + 1) * 40 <= + view_points->height) {
					// detele point
					if (GuiButton({ view_points->x + view_points->width + 5, scroll_points->y + view_points->y + 40 * i + 5 + y_up_text, 25, 25 }, "-")) {
						delete_point = i;
					}

					// X
					*val = (int)Points::GetPoints()[i]->vec.x;
					if (GuiValueBox({ 5 + view_points->x, scroll_points->y + view_points->y + 40 * i + 5 + y_up_text, view_points->width / 4 - 5, 30 }, "", val, 0, 254, points_edit[i][0]))
						points_edit[i][0] = !points_edit[i][0];
					Points::GetPoints()[i]->vec.x = *val;

					// Y
					*val = (int)Points::GetPoints()[i]->vec.y;
					if (GuiValueBox({ 5 + view_points->x + view_points->width / 4, scroll_points->y + view_points->y + 40 * i + 5 + y_up_text, view_points->width / 4 - 5, 30 }, "", val, 0, 254, points_edit[i][1]))
						points_edit[i][1] = !points_edit[i][1];
					Points::GetPoints()[i]->vec.y = *val;

					// Z
					*val = (int)Points::GetPoints()[i]->vec.z;
					if (GuiValueBox({ 5 + view_points->x + view_points->width / 2, scroll_points->y + view_points->y + 40 * i + 5 + y_up_text, view_points->width / 4 - 5, 30 }, "", val, 0, 254, points_edit[i][2]))
						points_edit[i][2] = !points_edit[i][2];
					Points::GetPoints()[i]->vec.z = *val;

					// Name
					char* old_name = Points::GetPoints()[i]->name.data();
					if (GuiTextBox({ 5 + view_points->x + 3 * view_points->width / 4, scroll_points->y + view_points->y + 40 * i + 5 + y_up_text, view_points->width / 4 - 5, 30 }, old_name, 5, points_edit[i][3]))
						points_edit[i][3] = !points_edit[i][3];
					if (Points::GetPoints()[i]->name.size() != strlen(old_name)) {
						// Change point's name
						Points::GetPoints()[i]->name = std::string(old_name);
						while (Points::CountPoints(Points::GetPoints()[i]->name) != 1) {
							Points::GetPoints()[i]->name += '\'';
						}

						Points::GetPoints()[i]->delete_line();
						Points::GetPoints()[i]->add_me(Points::GetLines());
					}
				}
			}

			if (delete_point != -1) {
				Points::GetPoints()[delete_point]->delete_line();
				Points::GetPoints().erase(Points::GetPoints().begin() + delete_point);
				points_edit.pop_back();
			}

			// lines
			font_size = get_size_font("FROM", (view_points->width - 35) / 4);
			y_up_text = MeasureTextEx(GetFontDefault(), "FROM", font_size, 0).y;

			GuiScrollPanel({ rec.x + rec.width / 2, rec.y, rec.width / 2, rec.height }, "Lines", { 0, 0, rec.width / 2 - 15, 40.0f * Points::GetLines().size() }, scroll_lines, view_lines);

			view_lines->width -= 35;

			// Add new line
			if (GuiButton({ rec.x + rec.width - size_add, rec.y, (float)size_add, (float)size_add }, "+")) {
				Points::GetLines().push_back(new Line("S", "E"));
				lines_edit.push_back({ false, false });

				Points::GetLines()[Points::GetLines().size() - 1]->updata_0(Points::GetPoints());
				Points::GetLines()[Points::GetLines().size() - 1]->updata_1(Points::GetPoints());
			}

			DrawText("FROM", view_lines->x + view_lines->width / 4 - MeasureText("FROM", font_size), view_lines->y + 5, font_size, BLACK);
			DrawText("TO", view_lines->x + 3 * view_lines->width / 4 - MeasureText("TO", font_size), view_lines->y + 5, font_size, BLACK);

			// line's list
			int delete_line = -1;

			for (int i = 0; i < Points::GetLines().size(); ++i) {
				if (scroll_lines->y + i * 40 >= 0 && scroll_lines->y + (i + 1) * 40 <= +view_lines->height) {
					// Name 0
					char* old_name = Points::GetLines()[i]->name_0.data();
					if (GuiTextBox({ view_lines->x + 5, view_lines->y + scroll_lines->y + y_up_text + 40 * i + 5, view_lines->width / 2 - 10, 30 }, old_name, 5, lines_edit[i][0])) {
						lines_edit[i][0] = !lines_edit[i][0];
					}
					if (strlen(old_name) != Points::GetLines()[i]->name_0.size()) {
						Points::GetLines()[i]->name_0 = std::string(old_name);

						// change name 0
						if (Points::GetLines()[i]->points.first != nullptr)
							Points::GetLines()[i]->points.first->delete_line(Points::GetLines()[i]);
						Points::GetLines()[i]->updata_0(Points::GetPoints());
					}

					// Name 1
					old_name = Points::GetLines()[i]->name_1.data();
					if (GuiTextBox({ view_lines->x + view_lines->width / 2 + 5, view_lines->y + scroll_lines->y + y_up_text + 40 * i + 5, view_lines->width / 2 - 10, 30 }, old_name, 5, lines_edit[i][1])) {
						lines_edit[i][1] = !lines_edit[i][1];
					}
					if (strlen(old_name) != Points::GetLines()[i]->name_1.size()) {
						Points::GetLines()[i]->name_1 = std::string(old_name);

						// change name 1
						if (Points::GetLines()[i]->points.second != nullptr)
						Points::GetLines()[i]->points.second->delete_line(Points::GetLines()[i]);
						Points::GetLines()[i]->updata_1(Points::GetPoints());
					}

					// Delete
					if (GuiButton({ view_lines->x + view_lines->width + 5, view_lines->y + scroll_lines->y + y_up_text + 40 * i + 5, 25, 25 }, "-"))
						delete_line = i;
				}
			}

			if (delete_line != -1) {
				if (Points::GetLines()[delete_line]->points.first != nullptr)
					Points::GetLines()[delete_line]->points.first->delete_line(Points::GetLines()[delete_line]);
				if (Points::GetLines()[delete_line]->points.second != nullptr)
				Points::GetLines()[delete_line]->points.second->delete_line(Points::GetLines()[delete_line]);

				Points::GetLines().erase(Points::GetLines().begin() + delete_line);
				lines_edit.erase(lines_edit.begin() + delete_line);
			}

			delete val;

			//DrawRectangleRec({5 + view_points->x, scroll_points->y + view_points->y, 100, 100}, {255, 0, 0, 255});
		}

		void ScreenSettings::logic(float delta) {
			if (timer_error <= 0.5)
				timer_error += delta;
		}

		void ScreenSettings::load() {
			error();
		}

		void ScreenSettings::save() {
			error();
		}

		void ScreenSettings::error() {
			timer_error = 0;
		}

		bool ScreenSettings::can_quit() {
			return true;
		}
	}
}