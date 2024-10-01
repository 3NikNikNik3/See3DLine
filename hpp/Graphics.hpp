#pragma once

#include <vector>

#include "Math.hpp"

using namespace See3DLine::Math;

namespace See3DLine {
	namespace Graphics {
		struct Point
		{
			Math::Vector3 vec;
			char* name;

			Point(Math::Vector3 vec, char* name);

			~Point();

			Point copy();
		};

		struct Line
		{
			int first, second;

			char* name_0, * name_1;

			Line(char* name_0, char* name_1);

			~Line();
		};

		namespace Points {
			bool init(std::vector<Point*>& ps, std::vector<Line*>& ls);

			void reset_camera();

			void close();

			void apply(std::vector<Point*>& res);

			bool is_equally(char* a, char* b);

			char* copy(char* arr);
		}
	}
}