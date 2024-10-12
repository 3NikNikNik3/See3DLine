#pragma once

#include <vector>
#include <list>
#include <string>
#include "raylib.h"

#include "Math.hpp"

using namespace See3DLine::Math;

namespace See3DLine {
	namespace Graphics {
		struct Line;

		struct Point
		{
			Math::Vector3 vec, new_pos;
			std::string name;

			std::list<Line*> lines;

			Point(Math::Vector3 vec, std::string name);

			~Point();

			Point copy();

			void delete_line();

			void add_me(std::vector<Line*>& arr);

			void delete_line(Line* line);
		};

		struct Line
		{
			std::pair<Point*, Point*> points;

			std::string name_0, name_1;

			Line(std::string name_0, std::string name_1);

			~Line();

			void updata_0(std::vector<Point*>& arr);

			void updata_1(std::vector<Point*>& arr);
		};

		namespace Points {
			bool init(std::vector<Point*>& ps, std::vector<Line*>& ls);

			void reset_camera();

			void close();

			void updata();

			void draw(Rectangle rec, Vector2 size);

			Math::Matrix*& GetAngXZ();

			Math::Matrix*& GetAngXY();

			Math::Vector3& GetPos();

			Math::Matrix GetAng();

			std::vector<Point*>& GetPoints();

			std::vector<Line*>& GetLines();

			int CountPoints(std::string what);

			Color& GetColorFon();
		}
	}
}