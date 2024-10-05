#include "hpp/Graphics.hpp"

#include "raylib.h"

namespace See3DLine::Graphics {
	// Point
	Point::Point(Math::Vector3 vec = Math::Vector3(), char* name = new char[0] {}) : vec(vec), name(name) {}

	Point::~Point() {
		delete[] name;
	}

	Point Point::copy() {
		return { vec, Points::copy(name) };
	}

	// Line
	Line::Line(char* name_0, char* name_1) : name_0(name_0), name_1(name_1), first(-1), second(-1) {}

	Line::~Line() {
		delete[] name_0, name_1;
	}

	namespace Points {
		std::vector<Point*> points;
		std::vector<Line*> lines;

		Math::Matrix* ang_xz, * ang_xy;
		Math::Vector3 pos;
		Math::Matrix see_rev = Math::Matrix({ {0, 0, -1}, {0, 1, 0}, {1, 0, 0} });

		Color color_fon = { 255, 255, 255, 255 };

		bool Points::is_equally(char* a, char* b) {
			if (strlen(a) != strlen(b))
				return false;
			for (int i = 0; i < strlen(a); ++i)
				if (a[i] != b[i])
					return false;
			return true;
		}

		bool Points::init(std::vector<Point*>& ps, std::vector<Line*>& ls) {
			if (ps.size() > 255 || ls.size() > 255)
				return false;

			//! It is bad and slow (fix it in the future)
			for (int i = 0; i < ls.size(); ++i) {
				for (int j = 0; j < ps.size(); ++j)
					if (is_equally(ls[i]->name_0, ps[j]->name))
						ls[i]->first = j;
					else if (is_equally(ls[i]->name_1, ps[j]->name))
						ls[i]->second = j;
				if (ls[i]->first == -1 || ls[i]->second == -1)
					return false;
			}

			points.clear();
			lines.clear();

			points = ps;
			lines = ls;

			return true;
		}

		void Points::close() {
			for (int i = 0; i < points.size(); ++i)
				delete points[i];
			lines.clear();
			delete ang_xy, ang_xz;
		}

		void Points::apply(std::vector<Point*>& res) {
			res.resize(points.size());

			Math::Matrix rotate = *ang_xz * see_rev * *ang_xy;

			for (int i = 0; i < res.size(); ++i)
				res[i] = new Point{ rotate.run(points[i]->vec - pos), copy(points[i]->name) };
		}

		void Points::reset_camera() {
			delete ang_xz, ang_xy;
			ang_xy = new Math::Matrix({ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });
			ang_xz = new Math::Matrix({ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} });

			float x_min = 1;
			for (int i = 0; i < points.size(); ++i)
				if (x_min > points[i]->vec.x)
					x_min = points[i]->vec.x;
			
			pos = { 0, 0, 0 };
		}

		char* Points::copy(char* arr) {
			char* ans = new char[sizeof(arr)];
			for (int i = 0; i < sizeof(ans); ++i)
				ans[i] = arr[i];
			return ans;
		}

		void draw(Rectangle rec, Math::Vector2 size) {
			std::vector<Point*> new_points;

			apply(new_points);

			for (int i = 0; i < lines.size(); ++i)
				DrawLine((new_points[lines[i]->first]->vec.x / size.x + 0.5) * rec.width + rec.x, (0.5 - new_points[lines[i]->first]->vec.y / size.y) * rec.height + rec.y,
					(new_points[lines[i]->second]->vec.x / size.x + 0.5) * rec.width + rec.x, (0.5 - new_points[lines[i]->second]->vec.y / size.y) * rec.height + rec.y,
					{ 0, 0, 0, 255 });

			for (int i = 0; i < new_points.size(); ++i)
				delete new_points[i];
		}

		Math::Matrix*& GetAngXZ() { return ang_xz; }

		Math::Matrix*& GetAngXY() { return ang_xy; }

		Math::Vector3& GetPos() { return pos; }

		Math::Matrix GetAng() { return *ang_xz * *ang_xy; }

		Color& GetColorFon() { return color_fon; }
	}
}