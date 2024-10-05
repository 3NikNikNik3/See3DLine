#include <hpp/ScreenLines.hpp>

using namespace See3DLine::Graphics;

namespace See3DLine {
	namespace Screens {
		ScreenLine::ScreenLine(Math::Vector2 size_see) : size_see(size_see), move_now(false), timer(2) {
			Graphics::Points::init(std::vector<Graphics::Point*>{
					new Graphics::Point({ 0, 0, 0 }, new char[1] {'A'}),
					new Graphics::Point({ 0, 0, 0.5 }, new char[1] {'B'}),
					new Graphics::Point({ 0.5, 0, 0.5 }, new char[1] {'C'}),
					new Graphics::Point({ 0.5, 0, 0 }, new char[1] {'D'}),
					new Graphics::Point({ 0, 0.5, 0 }, new char[2] {'A', '1'}),
					new Graphics::Point({ 0, 0.5, 0.5 }, new char[2] {'B', '1'}),
					new Graphics::Point({ 0.5, 0.5, 0.5 }, new char[2] {'C', '1'}),
					new Graphics::Point({ 0.5, 0.5, 0 }, new char[2] {'D', '1'}),
			}, std::vector<Graphics::Line*>{
					new Graphics::Line(new char[1] {'A'}, new char[1] {'B'}),
					new Graphics::Line(new char[1] {'B'}, new char[1] {'C'}),
					new Graphics::Line(new char[1] {'C'}, new char[1] {'D'}),
					new Graphics::Line(new char[1] {'D'}, new char[1] {'A'}),
					new Graphics::Line(new char[1] {'A'}, new char[2] {'A', '1'}),
					new Graphics::Line(new char[1] {'B'}, new char[2] {'B', '1'}),
					new Graphics::Line(new char[1] {'C'}, new char[2] {'C', '1'}),
					new Graphics::Line(new char[1] {'D'}, new char[2] {'D', '1'}),
			});
			Graphics::Points::reset_camera();
		}

		ScreenLine::~ScreenLine() {
			Points::close();
		}

		void ScreenLine::draw(Rectangle rec) {
			Points::draw(rec, size_see);

			if (move_now) {
				if (timer <= 1) {
					DrawText("To quit, presed ESC", rec.x + 5, rec.y + 5, 20, { (unsigned char)(255 - Points::GetColorFon().r), (unsigned char)(255 - Points::GetColorFon().g), (unsigned char)(255 - Points::GetColorFon().b), 255 });
				}
				else if (timer < 2) {
					DrawText("To quit, presed ESC", rec.x + 5, rec.y + 5, 20, { (unsigned char)(255 - Points::GetColorFon().r), (unsigned char)(255 - Points::GetColorFon().g), (unsigned char)(255 - Points::GetColorFon().b), (unsigned char)(255 * (2 - timer))});
				}
			}
		}

		void ScreenLine::logic(float delta) {
			if (move_now) {
				if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT)) {
					Points::GetPos() += Points::GetAng().run({ GetMouseDelta().x / 400, GetMouseDelta().y / 400, 0 });
				}
				else {
					float ang_x = GetMouseDelta().x / 400 * PI, ang_y = GetMouseDelta().y / 400 * PI;
					*Points::GetAngXZ() *= Math::Matrix({
						{cos(ang_x), 0, sin(ang_x)},
						{0, 1, 0},
						{-sin(ang_x), 0, cos(ang_x)}
						});
					*Points::GetAngXY() *= Math::Matrix({
						{1, 0, 0},
						{0, cos(ang_y), -sin(ang_y)},
						{0, sin(ang_y), cos(ang_y)}
						});
				}
				SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);

				if (IsKeyPressed(KeyboardKey::KEY_ESCAPE)) {
					ShowCursor();

					move_now = false;

					timer = 2;
				}

				if (timer < 2)
					timer += delta;
			}
			else {
				if (GuiButton({ GetScreenWidth() - MeasureText("reset", 20) - 5.0f, GetScreenHeight() - 25.0f, (float)MeasureText("reset", 20), 20}, "reset")) {
					Points::reset_camera();
				}

				if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT) && GetMousePosition().y >= GetScreenHeight() / y_button && !CheckCollisionPointRec(GetMousePosition(), { GetScreenWidth() - MeasureText("reset", 20) - 5.0f, GetScreenHeight() - 25.0f, (float)MeasureText("reset", 20), 20 })) {
					SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
					GetMouseDelta();

					HideCursor();

					move_now = true;

					timer = 0;
				}
			}
		}
	}
}