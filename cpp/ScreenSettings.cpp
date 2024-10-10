#include "hpp/ScreenSettings.hpp"

using namespace See3DLine::Graphics;

namespace See3DLine {
	namespace Screens {
		ScreenSettings::ScreenSettings() : Screen("Settings"), name(new char[10] {'F', 'i', 'l', 'e', ' ', 'n', 'a', 'm', 'e', '\0'}), scroll_points(new Vector2{ 0, 0 }), view_points(new Rectangle()) {
			points_edit.resize(Points::GetPoints().size(), {false, false, false, false});
		}

		ScreenSettings::~ScreenSettings() {
			delete name, scroll_points, view_points;
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

			if (GuiTextBox({ rec.x + rec.width / 3 + 5, rec.y + 5, rec.width / 3 - 10, 40 }, name, 50, name_file_edit)) {
				name_file_edit = !name_file_edit;
			}
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

			// +
			int size_add = 24;
			if (GuiButton({ rec.x + rec.width / 2 - size_add, rec.y, (float)size_add, (float)size_add }, "+")) {
				Points::GetPoints().push_back(new Point{ Math::Vector3(0, 0, 0), new char[2] {'A', '\0'} });
				points_edit.push_back({false, false, false, false});
				Points::GetPoints()[Points::GetPoints().size() - 1]->add_me(Points::GetLines());
			}

			view_points->width -= 35;

			DrawText("X", view_points->x + view_points->width / 8 - MeasureText("X", font_size) / 2, view_points->y + 5, font_size, BLACK);
			DrawText("Y", view_points->x + 3 * view_points->width / 8 - MeasureText("Y", font_size) / 2, view_points->y + 5, font_size, BLACK);
			DrawText("Z", view_points->x + 5 * view_points->width / 8 - MeasureText("Z", font_size) / 2, view_points->y + 5, font_size, BLACK);
			DrawText("NAME", view_points->x + 7 * view_points->width / 8 - MeasureText("NAME", font_size) / 2, view_points->y + 5, font_size, BLACK);

			// points
			int delete_point = -1;
			for (int i = 0; i < Points::GetPoints().size(); ++i) {
				if (scroll_points->y + i * 40 >= 0 && scroll_points->y + (i + 1) * 40 <= + view_points->height) {
					// detele point
					if (GuiButton({ view_points->x + view_points->width + 5, scroll_points->y + view_points->y + 40 * i + 5 + y_up_text, 25, 25 }, "-")) {
						delete_point = i;
					}

					// X
					*val = (int)Points::GetPoints()[i]->vec.x;
					if (GuiValueBox({ 5 + view_points->x, scroll_points->y + view_points->y + 40 * i + 5 + y_up_text, view_points->width / 4 + 5, 30 }, "", val, 0, 254, points_edit[i][0]))
						points_edit[i][0] = !points_edit[i][0];
					Points::GetPoints()[i]->vec.x = *val;

					// Y
					*val = (int)Points::GetPoints()[i]->vec.y;
					if (GuiValueBox({ 5 + view_points->x + view_points->width / 4, scroll_points->y + view_points->y + 40 * i + 5 + y_up_text, view_points->width / 4 + 5, 30 }, "", val, 0, 254, points_edit[i][1]))
						points_edit[i][1] = !points_edit[i][1];
					Points::GetPoints()[i]->vec.y = *val;

					// Z
					*val = (int)Points::GetPoints()[i]->vec.z;
					if (GuiValueBox({ 5 + view_points->x + view_points->width / 2, scroll_points->y + view_points->y + 40 * i + 5 + y_up_text, view_points->width / 4 + 5, 30 }, "", val, 0, 254, points_edit[i][2]))
						points_edit[i][2] = !points_edit[i][2];
					Points::GetPoints()[i]->vec.z = *val;
				}
			}

			if (delete_point != -1) {
				Points::GetPoints()[delete_point]->delete_line();
				Points::GetPoints().erase(Points::GetPoints().begin() + delete_point);
				points_edit.pop_back();
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