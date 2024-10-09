#pragma once

#include <vector>
#include <list>
#include "raylib.h"

#include "Math.hpp"

using namespace See3DLine::Math;

namespace See3DLine {
	namespace Graphics {
		struct Line;

		struct Point
		{
			Math::Vector3 vec, new_pos;
			char* name;

			std::list<Line*> lines;

			Point(Math::Vector3 vec, char* name);

			~Point();

			Point copy();
		};

		struct Line
		{
			std::pair<Point*, Point*> points;

			char* name_0, * name_1;

			Line(char* name_0, char* name_1);

			~Line();
		};

		namespace Points {
			bool init(std::vector<Point*>& ps, std::vector<Line*>& ls);

			void reset_camera();

			void close();

			void updata();

			bool is_equally(char* a, char* b);

			char* copy(char* arr);

			void draw(Rectangle rec, Math::Vector2 size);

			Math::Matrix*& GetAngXZ();

			Math::Matrix*& GetAngXY();

			Math::Vector3& GetPos();

			Math::Matrix GetAng();

			Color& GetColorFon();
		}
	}
}