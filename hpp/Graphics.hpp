#pragma once

#include <vector>
#include <list>
#include <string>

#ifdef INCLUDE_UP
	#include "../../raylib/src/raylib.h"
#else
	#include "raylib.h"
#endif

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

			void draw_name(Color color, Rectangle rec, Vector2 size);
		};

		struct Line
		{
			std::pair<Point*, Point*> points;

			Color color;

			std::string name_0, name_1;

			Line(std::string name_0, std::string name_1, Color color = {0, 0, 0, 255});

			~Line();

			void updata_0(std::vector<Point*>& arr);

			void updata_1(std::vector<Point*>& arr);

			void delete_0();

			void delete_1();
		};

		namespace Points {
			bool init(std::vector<Point*>& ps, std::vector<Line*>& ls);

			void reset_camera();

			void close();

			void updata();

			void draw(Rectangle rec, Vector2 size);

			void get_bord(Math::Vector3& min_, Math::Vector3& max_);

			bool add_cor();

			bool dif_cor();

			bool mul_cor();

			bool div_cor();

			Math::Matrix*& GetAngXZ();

			Math::Matrix*& GetAngXY();

			Math::Vector3& GetPos();

			Math::Matrix GetAng();

			std::vector<Point*>& GetPoints();

			std::vector<Line*>& GetLines();

			int CountPoints(std::string what);

			Color& GetColorFon();

			bool& GetShowNamePoints();
		}
	}
}
