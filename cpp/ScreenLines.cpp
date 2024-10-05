#include <hpp/ScreenLines.hpp>

using namespace See3DLine::Graphics;

namespace See3DLine {
	namespace Screens {
		ScreenLine::ScreenLine(Math::Vector2 size_see) : size_see(size_see), move_now(true) {
			Graphics::Points::init(std::vector<Graphics::Point*>{
				new Graphics::Point(Math::Vector3{ 0, 0, 0 }, new char[1] {'A'}),
					new Graphics::Point({ 0, 0, 0.5 }, new char[1] {'B'}),
					new Graphics::Point({ 0.5, 0.5, 0.5 }, new char[1] {'C'})
			}, std::vector<Graphics::Line*>{
				new Graphics::Line(new char[1] {'A'}, new char[1] {'B'}),
					new Graphics::Line(new char[1] {'B'}, new char[1] {'C'}),
					new Graphics::Line(new char[1] {'C'}, new char[1] {'A'})
			});
			Graphics::Points::reset_camera();
			GetMouseDelta();
		}

		ScreenLine::~ScreenLine() {
			Points::close();
		}

		void ScreenLine::draw(Rectangle rec) {
			Points::draw(rec, size_see);
		}

		void ScreenLine::logic(float delta) {
			if (move_now) {
				if (IsKeyDown(KeyboardKey::KEY_W)) {
					Points::GetPos() += Points::GetAng().run({ delta, 0, 0 });
				}
				if (IsKeyDown(KeyboardKey::KEY_S)) {
					Points::GetPos() += Points::GetAng().run({ -delta, 0, 0 });
				}
				if (IsKeyDown(KeyboardKey::KEY_D)) {
					Points::GetPos() += Points::GetAng().run({ 0, 0, delta });
				}
				if (IsKeyDown(KeyboardKey::KEY_A)) {
					Points::GetPos() += Points::GetAng().run({ 0, 0, -delta });
				}


				float ang_x = GetMouseDelta().x / 400 * PI, ang_y = GetMouseDelta().y / 400 * PI;
				*Points::GetAngXZ() *= Math::Matrix({
					{cos(ang_x), 0, sin(ang_x)},
					{0, 1, 0},
					{-sin(ang_x), 0, cos(ang_x)}
				});
				/**Points::GetAngXY() *= Math::Matrix({
					{cos(ang_y), -sin(ang_y), 0},
					{sin(ang_y), cos(ang_y), 0},
					{0, 0, 1}
				});*/
				*Points::GetAngXY() *= Math::Matrix({
					{1, 0, 0},
					{0, cos(ang_y), -sin(ang_y)},
					{0, sin(ang_y), cos(ang_y)}
				});

				SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
			}
		}
	}
}