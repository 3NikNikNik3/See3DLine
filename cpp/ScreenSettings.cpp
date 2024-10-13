#include "hpp/ScreenSettings.hpp"

#include <iostream>

using namespace See3DLine::Graphics;

namespace See3DLine {
	namespace Screens {
		ScreenSettings::ScreenSettings() : Screen("Settings"), name("File's name"), scroll_points(new Vector2{0, 0}), view_points(new Rectangle()), scroll_lines(new Vector2{0, 0}), view_lines(new Rectangle()){
			points_edit.resize(Points::GetPoints().size(), {false, false, false, false});
			lines_edit.resize(Points::GetLines().size(), { false, false });

			if (!std::filesystem::exists("shapes"))
				std::filesystem::create_directory("shapes");
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

			// Clear all points and lines
			if (GuiButton({ rec.x + 5, rec.y + 5, rec.width - 10, 35 }, "Delete all")) {
				for (int i = 0; i < Points::GetPoints().size(); ++i)
					delete Points::GetPoints()[i];
				Points::GetPoints().clear();

				for (int i = 0; i < Points::GetLines().size(); ++i)
					delete Points::GetLines()[i];
				Points::GetLines().clear();

				points_edit.clear();
				lines_edit.clear();
			}

			rec.y += 45;

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
				delete Points::GetPoints()[delete_point];
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

			DrawText("FROM", view_lines->x + view_lines->width / 4 - MeasureText("FROM", font_size) / 2, view_lines->y + 5, font_size, BLACK);
			DrawText("TO", view_lines->x + 3 * view_lines->width / 4 - MeasureText("TO", font_size) / 2, view_lines->y + 5, font_size, BLACK);

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
						Points::GetLines()[i]->delete_0();
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
						Points::GetLines()[i]->delete_1();
						Points::GetLines()[i]->updata_1(Points::GetPoints());
					}

					// Delete
					if (GuiButton({ view_lines->x + view_lines->width + 5, view_lines->y + scroll_lines->y + y_up_text + 40 * i + 5, 25, 25 }, "-"))
						delete_line = i;
				}
			}

			if (delete_line != -1) {
				Points::GetLines()[delete_line]->delete_0();
				Points::GetLines()[delete_line]->delete_1();

				delete Points::GetLines()[delete_line];
				Points::GetLines().erase(Points::GetLines().begin() + delete_line);
				lines_edit.erase(lines_edit.begin() + delete_line);
			}

			delete val;

			// Error
			if (timer_error <= 0.5)
				DrawRectangleRec({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {255, 0, 0, 100});
		}

		void ScreenSettings::logic(float delta) {
			if (timer_error <= 0.5)
				timer_error += delta;
		}

		void ScreenSettings::load() {
			if (std::filesystem::exists("shapes/" + name + ".shape")) {
				// load file

				std::ifstream fin("shapes/" + name + ".shape");

				std::vector<Point*> points;
				std::vector<Line*> lines;

				// points
				unsigned char n = fin.get();

				points.resize(n);
				for (int i = 0; i < n; ++i) {
					unsigned char x = fin.get(), y = fin.get(), z = fin.get();
					std::string name;

					fin >> name; fin.get();

					points[i] = new Point({ (float)x, (float)y, (float)z }, name);
				}

				// lines
				n = fin.get();
				lines.resize(n);
				for (int i = 0; i < n; ++i) {
					std::string name_0, name_1;

					fin >> name_0 >> name_1; fin.get();

					lines[i] = new Line(name_0, name_1);
				}

				if (Points::init(points, lines)) {
					// elso
					points_edit.resize(points.size(), { false, false, false, false });
					lines_edit.resize(lines.size(), { false, false });
				}
				else
					error();

				fin.close();
			}
			else {
				error();
			}
		}

		void ScreenSettings::save() {
			if (can_quit()) {
				// save file

				std::ofstream fout("shapes/" + name + ".shape");

				// points
				fout << (unsigned char)Points::GetPoints().size();
				for (int i = 0; i < Points::GetPoints().size(); ++i) {
					fout << (unsigned char)Points::GetPoints()[i]->vec.x;
					fout << (unsigned char)Points::GetPoints()[i]->vec.y;
					fout << (unsigned char)Points::GetPoints()[i]->vec.z;
					fout << Points::GetPoints()[i]->name << "\n";
				}

				// lines
				fout << (unsigned char)Points::GetLines().size();
				for (int i = 0; i < Points::GetLines().size(); ++i) {
					fout << Points::GetLines()[i]->name_0 << "\n";
					fout << Points::GetLines()[i]->name_1 << "\n";
				}

				fout.close();
			}
		}

		void ScreenSettings::error() {
			timer_error = 0;
		}

		bool ScreenSettings::can_quit() {
			for (int i = 0; i < Points::GetLines().size(); ++i) {
				if (Points::GetLines()[i]->points.first == nullptr || Points::GetLines()[i]->points.second == nullptr) {
					error();
					return false;
				}
			}
			return true;
		}
	}
}