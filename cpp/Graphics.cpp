#ifdef INCLUDE_UP
	#include "../hpp/Graphics.hpp"
#else
	#include "hpp/Graphics.hpp"
#endif

namespace See3DLine::Graphics {
	// Point
	Point::Point(Math::Vector3 vec = Math::Vector3(), std::string name = new char[0] {}) : vec(vec), name(name) {}

	Point::~Point() { }

	Point Point::copy() {
		return { vec, name };
	}

	void Point::delete_line() {
		for (std::list<Line*>::iterator i = lines.begin(); i != lines.end(); ++i) {
			if ((*i)->points.first == this)
				(*i)->points.first = nullptr;
			else
				(*i)->points.second = nullptr;
		}
		lines.clear();
	}

	void Point::add_me(std::vector<Line*>& arr) {
		for (int i = 0; i < arr.size(); ++i)
			if (arr[i]->points.first == nullptr && arr[i]->name_0 == name) {
				arr[i]->points.first = this;
				lines.push_front(arr[i]);
			}
			else if (arr[i]->points.second == nullptr && arr[i]->name_1 == name) {
				arr[i]->points.second = this;
				Points::GetLines();
				lines.push_front(arr[i]);
			}
	}

	void Point::delete_line(Line* line) {
		for (std::list<Line*>::iterator i = lines.begin(); i != lines.end(); ++i) {
			if ((*i) == line) {
				lines.erase(i);
				return;
			}
		}
	}

	void Point::draw_name(Color color, Rectangle rec, Vector2 size) {
		Vector2 pos = { (new_pos.x / size.x + 0.5) * rec.width + rec.x, (0.5 - new_pos.y / size.y) * rec.height + rec.y };
		DrawText(name.c_str(), pos.x - MeasureText(name.c_str(), 20), pos.y - MeasureTextEx(GetFontDefault(), name.c_str(), 20, 0).y, 20, { (unsigned char)(255 - color.r), (unsigned char)(255 - color.g), (unsigned char)(255 - color.b), 255 });
	}

	// Line
	Line::Line(std::string name_0, std::string name_1, Color color) : name_0(name_0), name_1(name_1), points({nullptr, nullptr}), color(color) {}

	Line::~Line() { }

	void Line::updata_0(std::vector<Point*>& arr) {
		for (int i = 0; i < arr.size(); ++i) {
			if (name_0 == arr[i]->name) {
				points.first = arr[i];
				arr[i]->lines.push_front(this);
				return;
			}
		}
	}

	void Line::updata_1(std::vector<Point*>& arr) {
		for (int i = 0; i < arr.size(); ++i) {
			if (name_1 == arr[i]->name) {
				points.second = arr[i];
				arr[i]->lines.push_front(this);
				return;
			}
		}
	}

	void Line::delete_0() {
		if (points.first != nullptr) {
			points.first->delete_line(this);
			points.first = nullptr;
		}
	}

	void Line::delete_1() {
		if (points.second != nullptr) {
			points.second->delete_line(this);
			points.second = nullptr;
		}
	}

	namespace Points {
		std::vector<Point*> points;
		std::vector<Line*> lines;

		Math::Matrix* ang_xz, * ang_xy;
		Math::Vector3 pos;
		Math::Matrix see_rev = Math::Matrix({ {0, 0, -1}, {0, 1, 0}, {1, 0, 0} });

		Color color_fon = { 255, 255, 255, 255 };

		bool show_name_points = true;

		bool init(std::vector<Point*>& ps, std::vector<Line*>& ls) {
			if (ps.size() > 255 || ls.size() > 255)
				return false;

			//! It is bad and slow (fix it in the future)
			for (int i = 0; i < ls.size(); ++i) {
				for (int j = 0; j < ps.size(); ++j)
					if (ls[i]->name_0 == ps[j]->name) {
						ls[i]->points.first = ps[j];
						ps[j]->lines.push_front(ls[i]);
					}
					else if (ls[i]->name_1 == ps[j]->name) {
						ls[i]->points.second = ps[j];
						ps[j]->lines.push_front(ls[i]);
					}
				if (ls[i]->points.first == nullptr || ls[i]->points.second == nullptr)
					return false;
			}

			for (int i = 0; i < points.size(); ++i)
				delete points[i];
			points.clear();
			for (int i = 0; i < lines.size(); ++i)
				delete lines[i];
			lines.clear();

			points = ps;
			lines = ls;

			return true;
		}

		void close() {
			for (int i = 0; i < points.size(); ++i)
				delete points[i];
			lines.clear();
			delete ang_xy, ang_xz;
		}

		void updata() {
			Math::Matrix rotate = *ang_xz * see_rev * *ang_xy;

			for (int i = 0; i < points.size(); ++i)
				points[i]->new_pos = rotate.run(points[i]->vec - pos);
		}

		void reset_camera() {
			delete ang_xz, ang_xy;
			ang_xy = new Math::Matrix({ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });
			ang_xz = new Math::Matrix({ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });

			float x_min = 1;
			for (int i = 0; i < points.size(); ++i)
				if (x_min > points[i]->vec.x)
					x_min = points[i]->vec.x;
			
			pos = { 0, 0, 0 };
		}

		void draw(Rectangle rec, Vector2 size) {
			updata();

			for (int i = 0; i < lines.size(); ++i)
				DrawLine((lines[i]->points.first->new_pos.x / size.x + 0.5) * rec.width + rec.x, (0.5 - lines[i]->points.first->new_pos.y / size.y) * rec.height + rec.y,
					(lines[i]->points.second->new_pos.x / size.x + 0.5) * rec.width + rec.x, (0.5 - lines[i]->points.second->new_pos.y / size.y) * rec.height + rec.y,
					lines[i]->color);

			if (show_name_points) {
				for (int i = 0; i < points.size(); ++i)
					points[i]->draw_name(color_fon, rec, size);
			}
		}

		int CountPoints(std::string what) {
			int ans = 0;
			for (int i = 0; i < points.size(); ++i)
				if (points[i]->name == what)
					++ans;
			return ans;
		}

		Math::Matrix*& GetAngXZ() { return ang_xz; }

		Math::Matrix*& GetAngXY() { return ang_xy; }

		Math::Vector3& GetPos() { return pos; }

		Math::Matrix GetAng() { return *ang_xz * *ang_xy; }

		std::vector<Point*>& GetPoints() { return points; }

		std::vector<Line*>& GetLines() { return lines; }

		Color& GetColorFon() { return color_fon; }

		bool& GetShowNamePoints() { return show_name_points; }
	}
}
