#pragma once

#include <cmath>

namespace See3DLine {
	namespace Math {
		struct Vector3
		{
			float x, y, z;

			Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

			Vector3 operator+(Vector3 vec);

			Vector3 operator-(Vector3 vec);

			Vector3 operator-();

			double len();
		};

		struct Vector2
		{
			float x, y;

			Vector2(float x = 0, float y = 0) : x(x), y(y) {}

			Vector2 operator+(Vector2 vec);

			Vector2 operator-(Vector2 vec);

			Vector2 operator-();

			double len();
		};
	}
}