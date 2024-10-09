#include "hpp/ScreenSettings.hpp"

namespace See3DLine {
	namespace Screens {
		ScreenSettings::ScreenSettings() : Screen("Settings"), name(new char[10] {'F', 'i', 'l', 'e', ' ', 'n', 'a', 'm', 'e', '\0'}) {}

		ScreenSettings::~ScreenSettings() {
			delete name;
		}

		void ScreenSettings::draw(Rectangle rec) {
			if (timer_error <= 0.5)
				DrawRectangleRec(rec, { 255, 0, 0, 255 });

			GuiTextBox({ rec.x + rec.width / 3 + 5, rec.y + 5, rec.width / 3 - 10, 40 }, name, 50, true);
			if (GuiButton({ rec.x + 5, rec.y + 5, rec.width / 3 - 10, 40 }, "Load")) {
				load();
			}
			if (GuiButton({ rec.x + rec.width * 2 / 3 + 5, rec.y + 5, rec.width / 3 - 10, 40 }, "Save")) {
				save();
			}

			rec.y += 50;
			rec.height -= 50;
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